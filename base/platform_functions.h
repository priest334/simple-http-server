#ifndef __BASE_PLATFORM_FUNCTIONS_H__
#define __BASE_PLATFORM_FUNCTIONS_H__

#include "base/platform_spec.h"

#ifndef MSLEEP
#	if OS_WIN
#		define MSLEEP(ms) Sleep(ms)
#	else // OS_WIN
#	include <unistd.h>
#		define MSLEEP(ms) usleep((ms)*1000)
#	endif
#endif // MSLEEP

#ifndef CLOSE_SOCKET
#	if OS_WIN
#		define CLOSE_SOCKET(fd) closesocket(fd)
#	else // OS_WIN
#		define CLOSE_SOCKET(fd) close(fd)
#	endif
#endif // CLOSE_SOCKET

#ifndef LOCALTIME
#	if OS_WIN
#		define LOCALTIME(t, r) localtime_s(t, r)
#	else // OS_WIN
#		define LOCALTIME(t, r) localtime_r(t, r)
#	endif
#endif // LOCALTIME

#ifndef VSNPRINTF
#	if OS_WIN
#		define VSNPRINTF _vsnprintf
#	else // OS_WIN
#		define VSNPRINTF vsnprintf
#	endif
#endif // VSNPRINTF

#endif // __BASE_PLATFORM_FUNCTIONS_H__

