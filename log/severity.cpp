
#include "log/severity.h"

const Severity LOG_INFO = 0, LOG_WARNING = 1, LOG_ERROR = 2, LOG_FATAL = 3, NUM_SEVERITIES = 4;
const char* const SeverityNames[NUM_SEVERITIES] = {
	"INFO", "WARN", "ERROR", "FATAL"
};

const char SeverityPrefix[] = "IWEF";

inline bool IsValidSeverity(Severity severity) {
	return (severity >= 0 && severity < NUM_SEVERITIES);
}

const char* SeverityName(Severity severity) {
	if (!IsValidSeverity(severity))
		return "EXCEPT";
	return SeverityNames[severity];
}

