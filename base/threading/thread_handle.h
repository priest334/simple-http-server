
#ifndef __BASE_THREADING_THREAD_HANDLE_H__
#define __BASE_THREADING_THREAD_HANDLE_H__

#include "base/platform_spec.h"

#if defined(OS_WIN) && !defined(USE_POSIX_PTHREAD)
#include <Windows.h>
#define ThreadHandleType HANDLE
#else
#include <pthread.h>
#define ThreadHandleType pthread_t
#endif


#endif // __BASE_THREADING_THREAD_HANDLE_H__

