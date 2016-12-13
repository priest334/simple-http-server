#ifndef __LOG_WRITER_H__
#define __LOG_WRITER_H__

#include <time.h>
#include "log/severity.h"
namespace hlp {
	namespace log {
		class Writer {
		public:
			virtual ~Writer();
			virtual void Send(Severity severity, time_t timestamp, const char* message, size_t length) = 0;
		};
	} // namespace hlp
} // namespace log


#endif // __LOG_WRITER_H__