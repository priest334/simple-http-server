
#ifndef __BASE_THREADING_THREAD_MANAGER_H__
#define __BASE_THREADING_THREAD_MANAGER_H__

#include <vector>
#include <map>
#include <string>

#include "base/platform_spec.h"
#include "base/disallow_copy_and_assign.h"
#include "base/threading/thread_handle.h"
#include "base/sync/lock.h"

namespace hlp {
	namespace base {

		class Thread;

		class ThreadManager {
		public:
			ThreadManager();
			~ThreadManager();
			bool Create(Thread* thread);
			Thread* GetNamedThread(const std::string& name);
			void Join(Thread* thread);
			void JoinNamedThread(const std::string& name);

		protected:
			void Append(Thread* thread);
			void Remove(Thread* thread);
			void Remove(const std::string& name);

#if (OS_WIN && !defined USE_POSIX_PTHREAD)
			static DWORD WINAPI ThreadProc(LPVOID arg);
#else
			static void* ThreadProc(void* arg);
#endif

		private:
			typedef std::map<std::string, Thread*> NamedThreads;
			typedef NamedThreads::iterator NamedThreadsIter;
			typedef NamedThreads::const_iterator NamedThreadsCIter;
			typedef std::vector<Thread*> Threads;
			typedef Threads::iterator ThreadsIter;
			typedef Threads::const_iterator ThreadsCIter;

			NamedThreads named_threads_;
			Threads threads_;
			LockImpl lock_;

			DISALLOW_COPY_AND_ASSIGN(ThreadManager);
		};
	} // namespace base
} // namespace hlp

#endif // __BASE_THREADING_THREAD_MANAGER_H__

