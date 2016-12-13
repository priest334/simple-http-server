
#include "base/time/time.h"


namespace hlp {
	namespace base {

		Time::Time()
			: time_(time(NULL)){
		}

		Time::Time(time_t t)
			: time_(t) {

		}

		std::string Time::ToString() {
			struct tm t;
			char prefix[24] = { 0 };
			LocalTime(&t, &time_);
			strftime(prefix, 24, "%Y-%m-%d %H:%M:%S", &t);
			return std::string(prefix);
		}

	} // namespace base

} // namespace hlp


