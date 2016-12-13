#ifndef __BASE_FILES_FILE_PATH_H__
#define __BASE_FILES_FILE_PATH_H__

#include <string>

namespace hlp {
	namespace base {
		using std::string;

		class FilePath {
		public:
			FilePath();
			FilePath(const string& path);

			string Reset(const string& path);
			string FileName();
			string Append(const string& path);

			const char* c_str() const;

		private:
			string file_path_;
		};

	} // namespace base

} // namespace hlp

#endif // __BASE_FILES_FILE_PATH_H__

