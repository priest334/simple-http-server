#ifndef __LOG_LOGGING_H__
#define __LOG_LOGGING_H__

#include <string>
#include <vector>

#include "log/severity.h"
#include "log/message.h"

namespace hlp {
	namespace log {
		class Writer;
		class Service;

		class Logging {
		public:
			Logging(const char* path, bool all_in_one);
			~Logging();
			Service* Get() const;

		private:
			Service* service_;
			std::string log_path_;
			bool all_in_one_;
			std::vector<Writer*> sinks_;
		};
	} // namespace log
} // namespace hlp


#endif // __LOG_LOGGING_H__

