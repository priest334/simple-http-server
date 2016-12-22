#include "log/file_writer.h"

#include <stdio.h>
#include <io.h>
#include <sstream>
#include "base/time/time.h"
#include "base/strings/string_helper.h"
#include "base/files/file_utils.h"

namespace hlp {
	namespace log {

		void FileWriter::OpenFile() {
			if (total_size_ > max_size_) {
				if (file_.is_open())
					file_.close();
				base::Time t(base::FileCreateTime(name_.c_str()));
				std::string suffix = t.Format("%Y%m%d%H%M%S");
				base::String name(name_);
				name.AppendFormat(".%s", suffix.c_str());
				while (0 == access(name.c_str(), 00)) {
					name.AppendFormat("%02d", backup_index_++);
				}
				rename(name_.c_str(), name.c_str());
				total_size_ = 0;
			}

			if (!file_.is_open())
				file_.open(name_.c_str(), std::ios::out | std::ios::app);
		}

		FileWriter::FileWriter(const char* name, size_t max_size)
			: name_(name),
			max_size_(max_size),
			total_size_(0),
			backup_index_(0) {
			total_size_ = base::FileSize(name_.c_str());
			OpenFile();
		}


		FileWriter::~FileWriter() {
			file_.close();
		}


		void FileWriter::Send(Severity severity, time_t timestamp, const char* message, size_t length) {
			OpenFile();
			if (!file_.bad()) {
				base::Time t(timestamp);
				std::ostringstream oss;
				oss << "[" << t.ToString() << "] ";
				oss.write(message, length);
				oss << std::endl;
				const std::string& line = oss.str();

				file_ << line;
				//file_ << "[" << t.ToString() << "] ";
				//file_.write(message, length);
				//file_ << "\n";
				file_.flush();
				total_size_ += line.length();
			}
		}
	} // namespace log
} // namespace hlp


