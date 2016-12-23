#ifndef __BASE_TIME_TIME_H__
#define __BASE_TIME_TIME_H__


#include <string>

#include "base/platform_spec.h"

#if OS_WIN
#define WIN32_LEAN_AND_MEAN
#include <time.h>
#	define LocalTime(t, r) localtime_s(t, r)
#else // OS_WIN
typedef unsigned long DWORD;
#include <sys/time.h>
#	define LocalTime(t, r) localtime_r(r, t)
#endif


struct timeval;

namespace hlp {
	namespace base {
		class Time {
		public:
			Time();
			Time(time_t t);

		public:
			static Time Now();
			static int GetTimeOfDay(struct timeval* tv, void* tz);
			static DWORD GetTickCount();
			static void Sleep(int ms);

			std::string Format(const char* fmt);
			std::string ToString();
			time_t Float() const;

		private:
			time_t timestamp_;
			time_t ftimestamp_;
		};

	} // namespace base

} // namespace hlp

#endif // __BASE_TIME_TIME_H__

