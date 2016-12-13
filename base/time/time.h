#ifndef __BASE_TIME_TIME_H__
#define __BASE_TIME_TIME_H__

#include <time.h>
#include <string>

#include "base/platform_spec.h"

#if OS_WIN
#	define LocalTime(t, r) localtime_s(t, r)
#else // OS_WIN
#	define LocalTime(t, r) localtime_r(r, t)
#endif


namespace hlp {
	namespace base {
		class Time {
		public:
			Time();
			Time(time_t t);

			std::string ToString();

		private:
			time_t time_;
		};

	} // namespace base

} // namespace hlp

#endif // __BASE_TIME_TIME_H__

