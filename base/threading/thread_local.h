
#ifndef __BASE_THREADING_THREAD_LOCAL_H__
#define __BASE_THREADING_THREAD_LOCAL_H__

#include <time.h>
#include <list>

#include "base/platform_spec.h"
#include "base/disallow_copy_and_assign.h"
#include "base/threading/thread_handle.h"
#include "base/threading/thread.h"
#include "base/sync/lock.h"

#if defined(OS_WIN) && !defined(USE_POSIX_PTHREAD)
#	define ThreadId DWORD
#	define TlsKey DWORD
#	define TlsCurrentThreadId() GetCurrentThreadId()
#	define TlsIsSameThread(t1,t2) ((t1)==(t2))
#	define TlsCreate(key) key=TlsAlloc()
#	define TlsDestroy(key) TlsFree(key)
#	define TlsSet(key,value) TlsSetValue(key,value)
#	define TlsGet(key) TlsGetValue(key)
#else // USE_POSIX_PTHREAD
#	define TlsKey pthread_key_t
#	define ThreadId pthread_t
#	define TlsCurrentThreadId() pthread_self()
#	define TlsIsSameThread(t1,t2) pthread_equal((t1),(t2))
#	define TlsCreate(key) pthread_key_create(&key, NULL)
#	define TlsDestroy(key) pthread_key_delete(key)
#	define TlsSet(key,value) pthread_setspecific(key,value)
#	define TlsGet(key) pthread_getspecific(key)
#endif

namespace hlp {
	namespace base {

		template <class Type, void (Type::*Init)()>
		class ThreadLocal {
			typedef std::list<ThreadId> Threads;
			typedef Threads::iterator ThreadsIter;
			typedef Threads::const_iterator ThreadsConstIter;
			
		public:
			ThreadLocal() {
				lock_ = new LockImpl();
				TlsCreate(index_);
			}
			~ThreadLocal() {
				TlsDestroy(index_);
			}
			Type* Get() {
				Type* value = NULL;
				ThreadId current_thread_id = TlsCurrentThreadId();
				lock_->lock();
				ThreadsConstIter iter = threads_.begin();
				for (; iter != threads_.end(); ++iter) {
					if (TlsIsSameThread(current_thread_id, (*iter))) {
						value = (Type*)TlsGet(index_);
						break;
					}
				}
				if (!value) {
					value = new Type();
					TlsSet(index_, value);
					(value->*Init)();
					threads_.push_back(current_thread_id);
				}
				lock_->unlock();
				return value;
			}

			void Free() {
				Type* value = NULL;
				ThreadId current_thread_id = TlsGetCurrentThreadId();
				lock_->lock();
				ThreadsConstIter iter = threads_.begin();
				for (; iter != threads_.end(); ++iter) {
					if (TlsIsSameThread(current_thread_id, (*iter))) {
						value = (Type*)TlsGet(index_);
						threads_.erase(iter);
						break;
					}
				}
				if (value) {
					delete value;
				}
				lock_->unlock();
			}

		private:
			Threads threads_;
			LockImpl* lock_;
			TlsKey index_;

			DISALLOW_COPY_AND_ASSIGN(ThreadLocal);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_THREADING_THREAD_LOCAL_H__

