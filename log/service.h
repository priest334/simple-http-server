#ifndef __LOG_SERVICE_H__
#define __LOG_SERVICE_H__

#include <time.h>
#include <string>
#include "log/severity.h"

namespace hlp {
	namespace log {
		class Writer;
		typedef Writer* WriterPtr;

		class Service
		{
		public:
			Service(const char* path);
			~Service();

			void SetMinSeverity(Severity severity);
			Severity MinSeverity() const;

			Writer* SetWriter(Severity severity, Writer* sink);

			void Send(Severity severity, time_t timestamp, const char* message, size_t length);

		private:
			Severity severity_;
			WriterPtr* sinks_;
			std::string path_;
			Severity min_severity_;
		};
	} // namespace log
} // namespace hlp



#endif // __LOG_SERVICE_H__

