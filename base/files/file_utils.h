#ifndef __BASE_FILES_FILE_UTILS_H__
#define __BASE_FILES_FILE_UTILS_H__

#include <time.h>
struct stat;

namespace hlp {
	namespace base {
		
		int FileStat(const char* file, struct stat* buf);
		int FileSize(const char* file);
		time_t FileCreateTime(const char* file);

	} // namespace base

} // namespace hlp

#endif // __BASE_FILES_FILE_UTILS_H__

