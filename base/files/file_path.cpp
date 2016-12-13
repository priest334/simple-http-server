
#include "base/files/file_path.h"

#include "base/platform_spec.h"

#ifdef OS_WIN
static char PathChar = '\\';
#else
static char PathChar = '/';
#endif

namespace hlp {
	namespace base {

		FilePath::FilePath() {
		}

		FilePath::FilePath(const string& path)
			: file_path_(path) {
		}

		string FilePath::Reset(const string& path) {
			file_path_ = path;
			return file_path_;
		}

		string FilePath::FileName() {
			string file = file_path_;
			string::size_type fpos = file_path_.find_last_of(PathChar);
			if (fpos != std::string::npos)
				file = file_path_.substr(fpos);

			fpos = file.find_last_of('.');
			if (fpos != std::string::npos)
				file = file.substr(0, fpos);
			return file;
		}

		string FilePath::Append(const string& path) {
			if (path.empty())
				return file_path_;

			if (file_path_.empty()) {
				file_path_ = path;
				return file_path_;
			}

			if (file_path_[file_path_.length() - 1] == PathChar) {
				if (path[0] == PathChar)
					return file_path_ += path.substr(1);
				return file_path_ += path;
			}
			else {
				if (path[0] == PathChar)
					return file_path_ += path;
				return file_path_ += PathChar + path;
			}
		}


		const char* FilePath::c_str() const {
			return file_path_.c_str();
		}

	} // namespace base

} // namespace hlp


