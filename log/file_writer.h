#ifndef __LOG_FILE_WRITER_H__
#define __LOG_FILE_WRITER_H__

#include <fstream>
#include "log/writer.h"

namespace hlp {
	namespace log {
		class FileWriter : public Writer
		{
			friend class Service;
			friend class Logging;
		private:
			void OpenFile();
			FileWriter(const char* name, size_t max_size = 1024*1024*256);
			~FileWriter();

			void Send(Severity severity, time_t timestamp, const char* message, size_t length);

		private:
			std::ofstream file_;
			std::string name_;
			size_t max_size_;
			size_t total_size_;
			int backup_index_;
		};
	} // namespace log
} // namespace hlp


#endif // __LOG_FILE_WRITER_H__

