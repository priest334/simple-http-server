#include "log/logging.h"

#include "base/files/file_path.h"
#include "log/service.h"
#include "log/file_writer.h"

namespace hlp {
	namespace log {
		Logging::Logging(const char* path, bool all_in_one)
			: service_(new Service(path)),
			log_path_(path),
			all_in_one_(all_in_one) {
			if (all_in_one_) {
				base::FilePath fpath(log_path_);
				fpath.Append("all.log");
				Writer* all = new FileWriter(fpath.c_str());
				service_->SetWriter(LOG_INFO, all);
				service_->SetWriter(LOG_WARNING, all);
				service_->SetWriter(LOG_ERROR, all);
				service_->SetWriter(LOG_FATAL, all);
				sinks_.push_back(all);
			} else {
				base::FilePath ipath(log_path_), wpath(log_path_), epath(log_path_), fpath(log_path_);
				ipath.Append("info.log");
				wpath.Append("warning.log");
				epath.Append("error.log");
				fpath.Append("fatal.log");

				Writer* info = new FileWriter(ipath.c_str());
				Writer* warn = new FileWriter(wpath.c_str());
				Writer* error = new FileWriter(epath.c_str());
				Writer* fatal = new FileWriter(fpath.c_str());

				service_->SetWriter(LOG_INFO, info);
				service_->SetWriter(LOG_WARNING, warn);
				service_->SetWriter(LOG_ERROR, error);
				service_->SetWriter(LOG_FATAL, fatal);

				sinks_.push_back(info);
				sinks_.push_back(warn);
				sinks_.push_back(error);
				sinks_.push_back(fatal);
			}
		}

		Logging::~Logging() {
			delete service_;
			std::vector<Writer*>::size_type size = sinks_.size(), index = 0;
			for (; index < size; index++) {
				delete sinks_[index];
			}
		}

		Service* Logging::Get() const {
			return service_;
		}
	} // namespace log
} // namespace hlp

