
#include "base/sync/lock.h"

#include "base/platform_spec.h"


namespace hlp {
	namespace base {

#if (OS_WIN && !defined USE_POSIX_PTHREAD)
		LockImpl::LockImpl() {
			InitializeCriticalSection(&handle_);
		}

		LockImpl::~LockImpl() {
			DeleteCriticalSection(&handle_);
		}

		bool LockImpl::Try() {
			return TryEnterCriticalSection(&handle_) ? true : false;
		}

		void LockImpl::Lock() {
			EnterCriticalSection(&handle_);
		}

		void LockImpl::Unlock() {
			LeaveCriticalSection(&handle_);
		}
#else 
		LockImpl::LockImpl() {
			pthread_mutex_init(&handle_, NULL);
		}

		LockImpl::~LockImpl() {
			pthread_mutex_destroy(&handle_);
		}

		bool LockImpl::Try() {
			return (0 == pthread_mutex_trylock(&handle_));
		}

		void LockImpl::Lock() {
			pthread_mutex_lock(&handle_);
		}

		void LockImpl::Unlock() {
			pthread_mutex_unlock(&handle_);
		}
#endif

	} // namespace base
} // namespace hlp


