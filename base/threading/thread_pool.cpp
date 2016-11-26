#include "base/threading/thread_pool.h"

#include "base/platform_spec.h"
#include "base/basic_types.h"
#include "base/strings/string_helper.h"
#include "base/threading/thread_manager.h"
#include "base/sync/lock.h"
#include "base/sync/auto_lock.h"

namespace hlp {
	namespace base {

		ThreadPool::TaskContext::TaskContext(Task* task, bool auto_release)
			: task_(task), auto_release_(auto_release) {
		}

		ThreadPool::TaskContext::~TaskContext() {
			if (auto_release_)
				delete task_;
		}

		void ThreadPool::TaskContext::SetAutoRelease(bool auto_release/* = true*/) {
			auto_release_ = auto_release;
		}

		void ThreadPool::TaskContext::Run() {
			if (task_)
				task_->Run();
		}

		ThreadPool::WorkerThread::WorkerThread(const std::string& name, ThreadPool* pool)
			: Thread(name),
			pool_(pool),
			busy_(false),
			stop_(false) {

		}

		int ThreadPool::WorkerThread::ThreadMain() {
			while ((pool_->working_ || pool_->destroy_gracefully_) && !stop_) {
				TaskContext* context = pool_->GetTaskContext();
				if (context) {
					busy_ = true;
					context->Run();
					busy_ = false;
				} else if (pool_->destroy_gracefully_) {
					break;
				}
				Update();
				Switch(0);
			}
			return 0;
		}

		void ThreadPool::WorkerThread::Update() {
			last_update_ = time(NULL);
		}

		bool ThreadPool::WorkerThread::IsBusy() const {
			return busy_;
		}

		time_t ThreadPool::WorkerThread::LastUpdateTime() const {
			return last_update_;
		}

		void ThreadPool::WorkerThread::Stop() {
			stop_ = true;
		}

		ThreadPool::MonitorThread::MonitorThread(const std::string& name, ThreadPool* pool)
			: Thread(name),
			pool_(pool) {
		}

		int ThreadPool::MonitorThread::ThreadMain() {
			while (pool_->working_) {
				time_t now = time(NULL);
				pool_->CheckRunningStatus();
				Switch(1000);
			}
			return 0;
		}

		ThreadPool::ThreadPool()
			: size_(0), working_(false), max_lock_time_(-1),
			task_list_notify_(new SignalEvent()),
			destroy_gracefully_(false) {
		}

		ThreadPool::ThreadPool(int size, time_t max_lock_time/* = -1*/)
			: size_(size), working_(false), max_lock_time_(max_lock_time),
			task_list_notify_(new SignalEvent()),
			destroy_gracefully_(false) {
			Initialize(size_, max_lock_time_);
		}

		ThreadPool::TaskContext* ThreadPool::GetTaskContext() {
			TaskContext* context = NULL;
			{
				AutoLock lock(task_context_list_lock_);
				if (!task_context_list_.empty()) {
					context = task_context_list_.front();
					task_context_list_.erase(task_context_list_.begin());
				} else {
					task_list_notify_->Reset();
				}
			}

			if (!context) {
				task_list_notify_->Wait(1000);
			}

			return context;
		}

		bool ThreadPool::ThreadShouldBeTerminated(WorkerThread* worker_thread) {
			time_t now = time(NULL);
			if ((now - worker_thread->LastUpdateTime()) > max_lock_time_) {
				return true;
			}
			return false;
		}

		void ThreadPool::CheckRunningStatus() {
			AutoLock lock(work_thread_list_lock_);
			WorkThreadListIter iter = work_thread_list_.begin();
			for (; iter != work_thread_list_.end();) {
				if (ThreadShouldBeTerminated(*iter)) {
					(*iter)->Stop();
					iter = work_thread_list_.erase(iter);
				}
				else {
					++iter;
				}
			}
		}

		bool ThreadPool::Initialize(int size, time_t max_lock_time) {
			working_ = true;
			manager_ = new ThreadManager();
			if (!manager_->Create(new MonitorThread("monitor", this))) {
				working_ = false;
				return false;
			}
			
			int i = 0, j = 0;
			for (int i = 0; i < size; i++) {
				String name;
				name.Format("worker_%d", i);
				WorkerThread* worker = new WorkerThread(name.str(), this);
				if (!manager_->Create(worker)) {
					j++;
					AutoLock lock(work_thread_list_lock_);
					work_thread_list_.push_back(worker);
				}
			}

			return  (size == j);
		}

		bool ThreadPool::PushTask(Task* task, bool auto_release/* = true*/) {
			if (!working_)
				return false;

			TaskContext* context = new TaskContext(task, auto_release);
			{
				AutoLock lock(task_context_list_lock_);
				task_context_list_.push_back(context);
			}

			task_list_notify_->Set();

			return true;
		}

		void ThreadPool::Destroy(bool gracefully) {
			destroy_gracefully_ = gracefully;
			working_ = false;

			manager_->JoinNamedThread("monitor");

			for (int i = 0; i < size_; i++) {
				String name;
				name.Format("worker_%d", i);
				manager_->JoinNamedThread(name.str());
			}

			delete manager_;
		}

	} // namespace net
} // namespace hlp


