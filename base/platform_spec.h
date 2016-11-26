#ifndef __BASE_PLATFORM_SPEC_H__
#define __BASE_PLATFORM_SPEC_H__

#if defined(_WIN32)
#define OS_WIN 1
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(__linux__)
#define OS_LINUX 1
#else
#error "Unknown Operating System!"
#endif

#endif // __BASE_PLATFORM_SPEC_H__

