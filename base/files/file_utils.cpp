#include "base/files/file_utils.h"

#include <sys/types.h>
#include <sys/stat.h>

namespace hlp {
	namespace base {

		int FileStat(const char* file, struct stat* buf) {
			return stat(file, buf);
		}

		int FileSize(const char* file) {
			struct stat buf;
			if (-1 == FileStat(file, &buf))
				return 0;
			return buf.st_size;
		}

		time_t FileCreateTime(const char* file) {
			struct stat buf;
			if (-1 == FileStat(file, &buf))
				return time(NULL);
			return buf.st_ctime;
		}
	} // namespace base

} // namespace hlp