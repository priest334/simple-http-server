
#ifndef __BASE_SYNC_SIGNAL_EVENT_HANDLE_H__
#define __BASE_SYNC_SIGNAL_EVENT_HANDLE_H__

#include "base/platform_spec.h"

namespace hlp {
	namespace base {

#if (OS_WIN && !defined(USE_POSIX_PTHREAD))
#include <Windows.h>
#define SignalEventHandleType HANDLE
#else
#include <pthread.h>
#define SignalEventHandleType pthread_cond_t
#endif

	} // namespace base
} // namespace hlp

#endif // __BASE_SYNC_SIGNAL_EVENT_HANDLE_H__

