#ifndef __LOG_LOG_H__
#define __LOG_LOG_H__

#include "log/logging.h"

#define InitLogging(path,all_in_one) \
	hlp::log::Logging* service = new hlp::log::Logging(path, all_in_one)

#define MLOG(severity) \
	hlp::log::Message(service->Get(), severity).stream()

#define Info() \
	MLOG(LOG_INFO)

#define Warning() \
	MLOG(LOG_WARNING)

#define Error() \
	MLOG(LOG_ERROR)

#define Fatal() \
	MLOG(LOG_FATAL)


#endif // __LOG_LOG_H__

