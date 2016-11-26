
#ifndef __BASE_SYNC_LOCK_HANDLE_H__
#define __BASE_SYNC_LOCK_HANDLE_H__

#include "base/platform_spec.h"

namespace hlp {
	namespace base {

#if (OS_WIN && !defined USE_POSIX_PTHREAD)
#include <Windows.h>
#define LockHandleType CRITICAL_SECTION
#else
#include <pthread.h>
#define LockHandleType pthread_mutex_t
#endif

	} // namespace base
} // namespace hlp

#endif // __BASE_SYNC_LOCK_HANDLE_H__

