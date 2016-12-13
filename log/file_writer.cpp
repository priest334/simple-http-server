#include "log/file_writer.h"

#include <sstream>
#include "base/time/time.h"
#include "base/strings/string_helper.h"

namespace hlp {
	namespace log {
		FileWriter::FileWriter(const char* name, size_t max_size/* = 10240*/)
			: name_(name),
			max_size_(max_size),
			total_size_(0) {
			file_.open(name_, std::ios::out | std::ios::app);
		}


		FileWriter::~FileWriter() {
			file_.close();
		}


		void FileWriter::Send(Severity severity, time_t timestamp, const char* message, size_t length) {
			if (total_size_ > max_size_) {
				file_.close();
				base::String name(name_);
				name.AppendFormat(".%u", time(NULL));
				file_.open(name.c_str(), std::ios::out | std::ios::app);
			}
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


