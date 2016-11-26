
#ifndef __BASE_THREADING_THREAD_POOL_H__
#define __BASE_THREADING_THREAD_POOL_H__

#include <time.h>
#include <list>

#include "base/platform_spec.h"
#include "base/disallow_copy_and_assign.h"
#include "base/threading/thread_handle.h"
#include "base/threading/thread.h"
#include "base/sync/lock.h"
#include "base/sync/signal_event.h"

namespace hlp {
	namespace base {

		class ThreadPool {
		public:
			class Task {
			public:
				virtual ~Task() {}
				virtual void Run() = 0;
			};

		protected:
			class TaskContext {
			public:
				TaskContext(Task* task, bool auto_release);
				~TaskContext();
				void SetAutoRelease(bool auto_release = true);
				void Run();
			private:
				Task* task_;
				bool auto_release_;
			};

			class WorkerThread : public Thread {
			public:
				WorkerThread(const std::string& name, ThreadPool* pool);
				int ThreadMain();
				void Update();
				bool IsBusy() const;
				time_t LastUpdateTime() const;
				void Stop();
			private:
				ThreadPool* pool_;
				time_t last_update_;
				bool busy_;
				bool stop_;
			};

			class MonitorThread : public Thread {
			public:
				MonitorThread(const std::string& name, ThreadPool* pool);
				int ThreadMain();

			private:
				ThreadPool* pool_;
			};

			friend class WorkerThread;
			friend class MonitorThread;

			TaskContext* GetTaskContext();
			bool ThreadShouldBeTerminated(WorkerThread* worker_thread);
			void CheckRunningStatus();
		public:
			ThreadPool();
			ThreadPool(int size, time_t max_lock_time = -1);
			bool Initialize(int size, time_t max_lock_time);
			bool PushTask(Task* task, bool auto_release = true);
			void Destroy(bool gracefully = false);

		private:
			ThreadManager* manager_;
			int size_;
			typedef std::list<TaskContext*> TaskContextList;
			typedef TaskContextList::iterator TaskContextListIter;
			typedef std::list<WorkerThread*> WorkThreadList;
			typedef WorkThreadList::iterator WorkThreadListIter;
			TaskContextList task_context_list_;
			WorkThreadList work_thread_list_;
			LockImpl task_context_list_lock_;
			LockImpl work_thread_list_lock_;
			bool working_;
			time_t max_lock_time_;
			SignalEvent* task_list_notify_;
			bool destroy_gracefully_;
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_THREADING_THREAD_POOL_H__

