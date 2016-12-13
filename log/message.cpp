#include "log/message.h"

#include "log/service.h"

namespace hlp {
	namespace log {
		Message::Message(Service* service, Severity severity)
			: service_(service), severity_(severity), timestamp_(time(NULL)){
		}

		Message::~Message() {
			const std::string& line = stream_.str();
			service_->Send(severity_, timestamp_, line.c_str(), line.length());
		}

		std::ostringstream& Message::stream() {
			return stream_;
		}
	} // namespace log
} // namespace hlp

