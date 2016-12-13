#ifndef __BASE_PLATFORM_FUNCTIONS_H__
#define __BASE_PLATFORM_FUNCTIONS_H__

#include "base/platform_spec.h"

namespace hlp {

#if OS_WIN
#	define MsSleep(ms) Sleep(ms)
#else // OS_WIN
#	define MsSleep(ms) usleep((ms)*1000)
#endif

#if OS_WIN
#	define CloseSocket(fd) closesocket(fd)
#else // OS_WIN
#	define CloseSocket(fd) close(fd)
#endif

#if OS_WIN
#	define StringPrintf _vsnprintf
#else // OS_WIN
#	define StringPrintf vsnprintf
#endif

}



#endif // __BASE_PLATFORM_FUNCTIONS_H__

