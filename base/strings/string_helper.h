#ifndef __BASE_STRINGS_STRING_HELPER_H__
#define __BASE_STRINGS_STRING_HELPER_H__

#include <cstdarg>
#include <string>
#include <vector>
#include <map>

#include "base/platform_functions.h"

namespace hlp {
	namespace base {
		class String {
		public:
			typedef enum {
				MIN_MATCHED,
				MAX_MATCHED
			}MatchType;

			static const std::string empty_;

			String();
			String(const char* s);
			String(const std::string& s);
			~String();

			String(const String& s);
			String& operator=(const char* s);
			String& operator=(const std::string& s);
			String& operator=(const String& s);

			String operator+(const char* s);
			String operator+(const std::string& s);
			String operator+(const String& s);

			String& operator+=(const char* s);
			String& operator+=(const std::string& s);
			String& operator+=(const String& s);

			bool operator==(const char* s);
			bool operator==(const std::string& s);
			bool operator==(const String& s);
			friend bool operator==(const char* s1, const String& s2);
			friend bool operator==(const std::string& s1, const String& s2);

			bool operator!=(const char* s);
			bool operator!=(const std::string& s);
			bool operator!=(const String& s);
			friend bool operator!=(const char* s1, const String& s2);
			friend bool operator!=(const std::string& s1, const String& s2);

		public:
			String& FormatV(const char* fmt, va_list args);
			String& Format(const char* fmt, ...);
			String& AppendFormatV(const char* fmt, va_list args);
			String& AppendFormat(const char* fmt, ...);
			String& Append(const char* s);
			String& Append(const std::string& s);
			String& Append(const String& s);
			
			String Left(const std::string& start, MatchType type = MAX_MATCHED);
			String Right(const std::string& start, MatchType type = MAX_MATCHED);
			String SubStr(const std::string& start, const std::string& end, MatchType type = MAX_MATCHED);

			String& Replace(const char* old, const char* repl, bool all = true);
			String& Replace(const std::string& old, const std::string& repl, bool all = true);

			String& TrimLeft(const char* s);
			String& TrimLeft(const std::string& s);
			String& TrimLeft(const String& s);
			String& TrimRight(const char* s);
			String& TrimRight(const std::string& s);
			String& TrimRight(const String& s);
			String& Trim(const char* s);
			String& Trim(const std::string& s);
			String& Trim(const String& s);

			bool IsDigit() const;
			bool IsHex() const;
			bool IsEmpty() const;
			bool Exist(const std::string& sub, bool ignore_case = false) const;

			size_t Hash() const;

			String& ToLower();
			String& ToUpper();

			const std::string& str() const;
			const char* c_str() const;
			size_t length() const;
			
		private:
			std::string value_;
		};

		class StringVector {
		public:
			StringVector();
			explicit StringVector(const std::vector<std::string>& vt);
			StringVector(const char* s, const char* sp);
			StringVector(const std::string& s, const std::string& sp);
			~StringVector();

			StringVector& Split(const char* s, const char* sp);
			StringVector& Split(const std::string& s, const std::string& sp);

			StringVector& Append(const char* s);
			StringVector& Append(const std::string& s);
			StringVector& Append(const std::vector<std::string>& vt);
			StringVector& Append(const StringVector& s);
			StringVector& Append(const char* s, const char* sp);
			StringVector& Append(const std::string& s, const std::string& sp);

			int Size() const;
			void SetAt(size_t index, const std::string& s);
			const std::string& At(size_t index) const;
			const std::string& operator[](int index) const;

			std::string ToString(const char* sp, bool append_sp = false);
			std::string ToString(const std::string& sp, bool append_sp = false);

		private:
			typedef std::vector<std::string>::const_iterator vtciter;
			std::vector<std::string> value_;
		};

		class StringMap {
		public:
			StringMap();
			explicit StringMap(const std::map<std::string, std::string>& m);
			StringMap(const char* values, const char* sp, const char* assign_key);
			StringMap(const std::string& values, const std::string& sp, const std::string& assign_key);
			~StringMap();

			StringMap& Split(const char* values, const char* sp, const char* assign_key);
			StringMap& Split(const std::string& values, const std::string& sp, const std::string& assign_key);

			StringMap& Append(const char* key, const char* value);
			StringMap& Append(const std::string& key, const std::string& value);
			StringMap& Append(const std::map<std::string, std::string>& m);
			StringMap& Append(const StringMap& m);
			StringMap& Append(const char* values, const char* sp, const char* assign_key);
			StringMap& Append(const std::string& values, const std::string& sp, const std::string& assign_key);

			void Set(const char* key, const char* value);
			void Set(const std::string& key, const std::string& value);
			std::string Find(const char* key);
			std::string Find(const std::string& key);
			void Remove(const char* key);
			void Remove(const std::string& key);

			std::string ToString(const char* sp, const char* assign_key, bool append_sp = false);
			std::string ToString(const std::string& sp, const std::string& assign_key, bool append_sp = false);

		private:
			typedef std::map<std::string, std::string>::const_iterator mciter;
			typedef std::map<std::string, std::string>::iterator miter;
			std::map<std::string, std::string> value_;
		};

	} // namespace base

} // namespace hlp

#endif // __BASE_STRINGS_STRING_HELPER_H__

