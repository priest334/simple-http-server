#ifndef __BASE_CONFIG_H__
#define __BASE_CONFIG_H__

#include <fstream>
#include <string>
#include <map>

namespace hlp {
	namespace base {

		class Config
		{
		public:

		private:
			std::string file_;
			std::map<std::string, std::string> items_;

		};
	} // namespace base
} // namespace hlp

#endif // __BASE_CONFIG_H__


