#include "base/sync/signal_event.h"

#include <errno.h>
#include <time.h>
#include "base/platform_spec.h"
#include "base/sync/lock.h"
#include "base/sync/auto_lock.h"

namespace hlp {
	namespace base {

#if (OS_WIN && !defined(USE_POSIX_PTHREAD))
		SignalEvent::SignalEvent(bool init_state/* = false*/, bool manual_reset/* = true*/)
			: handle_(NULL),
			signal_is_enabled_(init_state),
			manual_reset_(manual_reset),
			lock_(NULL) {
			handle_ = CreateEvent(NULL, manual_reset_?TRUE:FALSE, init_state?TRUE:FALSE, NULL);
		}

		SignalEvent::~SignalEvent() {
			CloseHandle(handle_);
		}

		int SignalEvent::Wait(unsigned int ms/* = 0xffffffff*/) {
			DWORD retval = WaitForSingleObject(handle_, ms);
			switch (retval) {
			case WAIT_OBJECT_0:
				return OK;
			case WAIT_TIMEOUT:
				return TIMEOUT;
			default:
				return FAILED;
			}
		}

		bool SignalEvent::Set() {
			if (!handle_)
				return false;
			return !SetEvent(handle_) ? false : true;
		}

		bool SignalEvent::Reset() {
			return !ResetEvent(handle_) ? false : true;
		}
#else
		SignalEvent::SignalEvent(bool init_state/* = false*/, bool manual_reset/* = true*/)
			: signal_is_enabled_(init_state),
			manual_reset_(manual_reset),
			lock_(new LockImpl()) {
			pthread_cond_init(&handle_, NULL);
		}

		SignalEvent::~SignalEvent() {
			pthread_cond_destroy(&handle_);
		}

		int SignalEvent::Wait(unsigned int ms/* = 0xffffffff*/) {
			int retval = FAILED;
			AutoLock lock(*lock_);
			if (ms == 0xffffffff) {
				if (!signal_is_enabled_) {
					retval = pthread_cond_wait(&handle_, lock_->HandlePtr());
				}
			} else { 
				//struct timeval now;
				//gettimeofday(&now, NULL);
				//struct timespec ts;
				//ts.tv_sec = now.tv_sec + ms/1000;
				//ts.tv_nsec = (now.tv_usec + ms%1000*1000) & (~1000000);
				//retval = pthread_cond_timedwait(&handle_, lock, ts);

				struct timespec ts;
				clock_gettime(CLOCK_REALTIME, &ts);
				ts.tv_sec += ms/1000;	
				ts.tv_nsec += ms%1000*1000000;
				if (ts.tv_nsec > 1000000000) {
					ts.tv_sec += 1;
					ts.tv_nsec &= ~1000000000;
				}
				if (!signal_is_enabled_) {
					retval = pthread_cond_timedwait(&handle_, lock_->HandlePtr(), &ts);
				}
			}
			switch (retval) {
			case 0: {
				if (!manual_reset_)
					signal_is_enabled_ = false;
				return OK;
			}
			case ETIMEDOUT: {
				return TIMEOUT;
			}
			default:
				return FAILED;
			}
		}

		bool SignalEvent::Set() {
			AutoLock lock(*lock_);
			signal_is_enabled_ = true;
			if (manual_reset_) {
				return (0 == pthread_cond_broadcast(&handle_));
			} else {
				return (0 == pthread_cond_signal(&handle_));
			}
		}

		bool SignalEvent::Reset() {
			AutoLock lock(*lock_);
			signal_is_enabled_ = false;
			return true;
		}

#endif
		
	} // namespace base
} // namespace hlp


