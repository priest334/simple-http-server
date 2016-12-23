#ifndef __LOG_SEVERITY_H__
#define __LOG_SEVERITY_H__

typedef int Severity;

extern const Severity LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_FATAL, NUM_SEVERITIES;
bool IsValidSeverity(Severity severity);
const char* SeverityName(Severity severity);
extern const char SeverityPrefix[];

#endif // __LOG_SEVERITY_H__