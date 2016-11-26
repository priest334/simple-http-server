
#include "base/threading/thread_manager.h"

#include "base/platform_spec.h"
#include "base/basic_types.h"
#include "base/threading/thread.h"
#include "base/threading/thread_handle.h"
#include "base/sync/lock.h"
#include "base/sync/auto_lock.h"

namespace hlp {
	namespace base {

		ThreadManager::ThreadManager() {
		}

		ThreadManager::~ThreadManager() {
		}

#if (OS_WIN && !defined USE_POSIX_PTHREAD)
		DWORD WINAPI ThreadManager::ThreadProc(LPVOID arg) {
			Thread* thread = reinterpret_cast<Thread*>(arg);
			int retval = thread->ThreadMain();
			ThreadManager* manager = thread->GetManager();
			if (!manager)
				manager->Remove(thread);
			delete thread;
			return retval;
		}

		bool ThreadManager::Create(Thread* thread) {
			thread->Attach(CreateThread(NULL, 0, ThreadProc, thread, 0, NULL));
			Append(thread);
			return (NULL != thread->Handle());
		}

		void ThreadManager::Join(Thread* thread) {
			if (thread && thread->IsSameManager(this)) {
				WaitForSingleObject(thread->Handle(), INFINITE);
			}
		}
#else
		void* ThreadManager::ThreadProc(void* arg) {
			Thread* thread = reinterpret_cast<Thread*>(arg);
			if (!thread->IsJoinable())
				pthread_detach(pthread_self());
			thread->ThreadMain();
			ThreadManager* manager = thread->GetManager();
			if (!manager)
				manager->Remove(thread);
			delete thread;
			return NULL;
		}

		bool ThreadManager::Create(Thread* thread) {
			pthread_t handle;
			unsigned int retval = pthread_create(&handle, NULL, ThreadProc, thread);
			thread->Attach(handle);
			Append(thread);
			return (0 == retval);
		}

		void ThreadManager::Join(Thread* thread) {
			if (thread && thread->IsSameManager(this)) {
				pthread_join(thread->Handle(), NULL);
			}
		}
#endif
		Thread* ThreadManager::GetNamedThread(const std::string& name) {
			AutoLock lock(lock_);
			NamedThreadsIter iter = named_threads_.find(name);
			if (iter != named_threads_.end()) {
				return (*iter).second;
			}
			return NULL;
		}

		void ThreadManager::JoinNamedThread(const std::string& name) {
			Join(GetNamedThread(name));
		}

		void ThreadManager::Append(Thread* thread) {
			AutoLock lock(lock_);
			thread->AttachManager(this);
			if (!thread->Name().empty()) {
				named_threads_[thread->Name()] = thread;
			}
			threads_.push_back(thread);
		}

		void ThreadManager::Remove(Thread* thread) {
			if (!thread)
				return;

			AutoLock lock(lock_);
			if (!thread->IsSameManager(this))
				return;
			thread->AttachManager(NULL);
			if (!thread->Name().empty()) {
				NamedThreadsIter iter = named_threads_.find(thread->Name());
				if (iter != named_threads_.end()) {
					named_threads_.erase(iter);
				}
			}

			ThreadsIter iter = threads_.begin();
			for (; iter != threads_.end(); ++iter) {
				if (*iter == thread) {
					threads_.erase(iter);
					break;
				}
			}
		}

		void ThreadManager::Remove(const std::string& name) {
			if (name.empty())
				return;

			Thread* thread = NULL;
			AutoLock lock(lock_);
			NamedThreadsIter iter = named_threads_.find(name);
			if (iter != named_threads_.end() && thread->IsSameManager(this)) {
				thread = iter->second;
				named_threads_.erase(iter);
			}

			if (!thread) {
				thread->AttachManager(NULL);
				ThreadsIter iter1 = threads_.begin();
				for (; iter1 != threads_.end(); ++iter1) {
					if (*iter1 == thread) {
						threads_.erase(iter1);
						break;
					}
				}
			}
		}

	} // namespace net
} // namespace hlp


