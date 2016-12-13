#include "log/service.h"

#include "log/writer.h"

namespace hlp {
	namespace log {
		Service::Service(const char* path)
			: sinks_(new WriterPtr[NUM_SEVERITIES]),
			min_severity_(LOG_INFO) {
			for (Severity i = LOG_INFO; i < NUM_SEVERITIES; i++) {
				sinks_[i] = NULL;
			}
		}

		Service::~Service() {
		}

		void Service::SetMinSeverity(Severity severity) {
			min_severity_ = severity;
		}

		Severity Service::MinSeverity() const {
			return min_severity_;
		}

		Writer* Service::SetWriter(Severity severity, Writer* sink) {
			Writer* old_sink = NULL;
			if (!IsValidSeverity(severity))
				return old_sink;
			old_sink = sinks_[severity];
			sinks_[severity] = sink;
			return old_sink;
		}

		void Service::Send(Severity severity, time_t timestamp, const char* message, size_t length) {
			if (!IsValidSeverity(severity))
				return;
			if (severity >= MinSeverity() && sinks_[severity])
				sinks_[severity]->Send(severity, timestamp, message, length);
		}
	} // namespace log
} // namespace hlp


