#ifndef __LOG_MESSAGE__
#define __LOG_MESSAGE__

#include <time.h>
#include <string>
#include <sstream>
#include "log/severity.h"

namespace hlp {
	namespace log {
		class Service;

		class Message {
		public:
			Message(Service* service, Severity severity);
			~Message();

			std::ostringstream& stream();

		private:
			Service* service_;
			Severity severity_;
			time_t timestamp_;
			std::ostringstream stream_;
		};
	}
}


#endif // __LOG_MESSAGE__
