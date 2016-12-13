
#include "base/strings/string_helper.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>


namespace hlp {
	namespace base {
		namespace {
			template <typename T>
			T Round(const T& v, const T& m) {
				return (v > m) ? m : v;
			}
		}

		const std::string String::empty_ = "";

		String::String()
			: value_("") {
		}

		String::String(const char* s)
			: value_(!s ? "" : s) {
		}

		String::String(const std::string& s)
			: value_(s) {
		}


		String::~String() {
		}

		String::String(const String& s) {
			value_.assign(s.value_);
		}

		String& String::operator=(const char* s) {
			value_.assign(s ? s : "");
			return *this;
		}

		String& String::operator=(const std::string& s) {
			value_.assign(s);
			return *this;
		}

		String& String::operator=(const String& s) {
			value_.assign(s.value_);
			return *this;
		}

		String String::operator+(const char* s) {
			return String(value_ + (s ? s : ""));
		}

		String String::operator+(const std::string& s) {
			return String(value_ + s);
		}

		String String::operator+(const String& s) {
			return String(value_ + s.value_);
		}

		String& String::operator+=(const char* s) {
			value_ += s ? s : "";
			return *this;
		}

		String& String::operator+=(const std::string& s) {
			value_ += s;
			return *this;
		}

		String& String::operator+=(const String& s) {
			value_ += s.value_;
			return *this;
		}


		bool String::operator==(const char* s) {
			return (value_ == s);
		}

		bool String::operator==(const std::string& s) {
			return (value_ == s);
		}

		bool String::operator==(const String& s) {
			return (value_ == s.value_);
		}

		bool operator==(const char* s1, const String& s2) {
			return (s2.value_ == s1);
		}

		bool operator==(const std::string& s1, const String& s2) {
			return (s2.value_ == s1);
		}

		bool String::operator!=(const char* s) {
			return !(value_ == s);
		}

		bool String::operator!=(const std::string& s) {
			return !(value_ == s);
		}

		bool String::operator!=(const String& s) {
			return !(value_ == s.value_);
		}

		bool operator!=(const char* s1, const String& s2) {
			return !(s2.value_ == s1);
		}

		bool operator!=(const std::string& s1, const String& s2) {
			return !(s2.value_ == s1);
		}

		String& String::FormatV(const char* fmt, va_list args) {
			const int max_buf_len = 102400;
			value_.resize(max_buf_len);
			int wr = StringPrintf(&value_[0], value_.length(), fmt, args);
			if (wr > 0)
				value_.resize(Round(wr, max_buf_len));
			else
				value_.resize(0);
			return *this;
		}

		String& String::Format(const char* fmt, ...) {
			va_list args;
			va_start(args, fmt);
			(*this).FormatV(fmt, args);
			va_end(args);
			return *this;
		}

		String& String::AppendFormatV(const char* fmt, va_list args) {
			String append;
			append.FormatV(fmt, args);
			value_ += append.c_str();
			return *this;
		}

		String& String::AppendFormat(const char* fmt, ...) {
			va_list args;
			va_start(args, fmt);
			(*this).AppendFormatV(fmt, args);
			va_end(args);
			return *this;
		}

		String& String::Append(const char* s) {
			return Append(std::string(s ? s : ""));
		}

		String& String::Append(const std::string& s) {
			value_ += s;
			return *this;
		}

		String& String::Append(const String& s) {
			return Append(s.value_);
		}

		String String::Left(const std::string& start, MatchType type/* = MAX_MATCHED*/) {
			if (start.empty())
				return *this;

			std::string::size_type fpos = std::string::npos;
			switch (type)
			{
			case MIN_MATCHED:
				fpos = value_.find(start, 0);
				break;
			default:
				fpos = value_.rfind(start, value_.length());
				break;
			}

			if (fpos == std::string::npos)
				return String();

			return String(value_.substr(0, fpos));
		}

		String String::Right(const std::string& start, MatchType type/* = MAX_MATCHED*/) {
			if (start.empty())
				return *this;

			std::string::size_type fpos = std::string::npos;
			switch (type)
			{
			case MIN_MATCHED:
				fpos = value_.rfind(start, value_.length());
				break;
			default:
				fpos = value_.find(start);
				break;
			}

			if (fpos == std::string::npos)
				return String();

			return String(value_.substr(fpos + start.length()));
		}

		String String::SubStr(const std::string& start, const std::string& end, MatchType type/* = MAX_MATCHED*/) {
			String empty;
			std::string::size_type spos, epos;
			spos = epos = std::string::npos;
			if (start.empty())
				return Left(end, type);

			if (end.empty())
				return Right(start, type);

			spos = value_.find(start);
			epos = value_.rfind(end, value_.length());
			if (spos == std::string::npos ||
				epos == std::string::npos ||
				epos <= (spos + start.length()))
				return empty;

			switch (type){
			case MIN_MATCHED: {
				std::vector<std::string::size_type> vs, ve;
				spos = value_.find(start);
				while (spos != std::string::npos) {
					vs.push_back(spos);
					spos = value_.find(start, spos + start.length());
				}
				epos = value_.find(end);
				while (epos != std::string::npos) {
					ve.push_back(epos);
					epos = value_.find(end, epos + end.length());
				}
				
				size_t m = vs.size(), n = ve.size(), i , j;

				size_t len = 0, mlen = 0;
				bool first = true;
				for (i = 0; i < m; i++) {
					for (j = 0; j < n; j++) {
						if (vs[i] >= ve[j])
							continue;
						len = ve[j] - vs[i] - start.length();
						if (first || len < mlen) {
							first = false;
							mlen = len;
							spos = vs[i];
							epos = ve[j];
							break;
						}	
					}
				}
				return String(value_.substr(spos + start.length(), mlen));
				}
			default: {
				return String(value_.substr(spos + start.length(), epos - spos - start.length()));
				}
			}

			spos = value_.find(start);
			if (spos == std::string::npos)
				return String();
			epos = value_.find(end, spos + start.length());
			if (epos == std::string::npos)
				return String();
			return String(value_.substr(spos + start.length(), epos - spos - start.length()));
		}

		String& String::Replace(const char* old, const char* repl, bool all/* = true*/) {
			return Replace(std::string(old ? old : ""), std::string(repl ? repl : ""), all);
		}

		String& String::Replace(const std::string& old, const std::string& repl, bool all/* = true*/) {
			size_t olen = 0;
			if (old.empty())
				return *this;

			std::string::size_type fpos = std::string::npos, offset = 0;
			std::string rep = repl;

			fpos = value_.find(old, offset);

			while (fpos != std::string::npos) {
				offset = fpos + rep.length();
				value_.replace(fpos, olen, rep);
				if (!all)
					break;
				fpos = value_.find(old, offset);
			}

			return *this;
		}

		String& String::TrimLeft(const char* s) {
			return TrimLeft(std::string(s ? s : ""));
		}

		String& String::TrimLeft(const std::string& s) {
			std::string::size_type len = s.length();
			std::string::size_type fpos = std::string::npos;

			fpos = value_.find(s);
			if (fpos == std::string::npos || fpos != 0) {
				return *this;
			}
			else {
				value_ = value_.substr(fpos + len);
				TrimLeft(s);
				return *this;
			}
		}

		String& String::TrimLeft(const String& s) {
			return TrimLeft(s.value_);
		}

		String& String::TrimRight(const char* s) {
			return TrimRight(std::string(s ? s : ""));
		}

		String& String::TrimRight(const std::string& s) {
			if (s.empty())
				return *this;
			std::string::size_type len = s.length();
			std::string::size_type total = value_.length(), fpos = std::string::npos;

			fpos = value_.rfind(s, total);
			if (fpos == std::string::npos || (total - fpos) != len) {
				return *this;
			}
			else {
				value_ = value_.substr(0, fpos);
				TrimRight(s);
				return *this;
			}
		}

		String& String::TrimRight(const String& s) {
			return TrimRight(s.value_);
		}

		String& String::Trim(const char* s) {
			return Trim(std::string(s ? s : ""));
		}

		String& String::Trim(const std::string& s) {
			TrimLeft(s);
			TrimRight(s);
			return *this;
		}

		String& String::Trim(const String& s) {
			return Trim(s.value_);
		}

		bool String::IsDigit() const {
			if (value_.empty())
				return false;

			std::string::size_type len = value_.length();

			for (std::string::size_type index = 0; index < len; index++) {
				if (value_[index] < '0' || value_[index] > '9')
					return false;
			}
			return true;
		}

		bool String::IsHex() const {
			if (value_.empty())
				return false;

			std::string::size_type len = value_.length();

			for (std::string::size_type index = 0; index < len; index++) {
				if ((value_[index] >= '0' && value_[index] <= '9')
					|| (value_[index] >= 'a' && value_[index] <= 'f')
					|| (value_[index] >= 'A' && value_[index] <= 'F'))
					continue;
				return false;
			}
			return true;
		}

		bool String::IsEmpty() const {
			return value_.empty();
		}

		bool String::Exist(const std::string& sub, bool ignore_case/* = false*/) const {
			if (sub.empty())
				return false;

			std::string::size_type i = 0, j = 0, len = value_.length(), sublen = sub.length();
			if (value_.length() < sub.length())
				return false;

			bool eq = false;
			for (; i < len; i++) {
				if (ignore_case) {
					eq = (tolower(value_[i]) == tolower(sub[j]));
				}
				else {
					eq = (value_[i] == sub[j]);
				}
				if (eq && (++j == sublen)) {
					return true;
				}
			}
			return false;
		}

		size_t String::Hash() const {
			size_t seed = 131;
			size_t hash = 0;

			std::string::size_type index = 0, len = value_.length();
			for (; index < len; index++) {
				hash = hash * seed + value_[index];
			}
			return hash;
		}

		String& String::ToLower() {
			std::string::size_type index = 0, len = value_.length();
			for (; index < len; index++)
				value_[index] = tolower(value_[index]);
			return *this;
		}

		String& String::ToUpper() {
			std::string::size_type index = 0, len = value_.length();
			for (; index < len; index++)
				value_[index] = toupper(value_[index]);
			return *this;
		}

		const std::string& String::str() const {
			return value_;
		}

		const char* String::c_str() const {
			return value_.c_str();
		}

		size_t String::length() const {
			return value_.length();
		}

		// StringVector
		StringVector::StringVector() {
		}

		StringVector::StringVector(const std::vector<std::string>& vt) {
			value_ = vt;
		}

		StringVector::StringVector(const char* s, const char* sp) {
			Split(std::string(s ? s : ""), std::string(sp ? sp : ""));
		}

		StringVector::StringVector(const std::string& s, const std::string& sp) {
			Split(s, sp);
		}

		StringVector::~StringVector() {
			value_.clear();
		}

		StringVector& StringVector::Split(const char* s, const char* sp) {
			return Split(std::string(s ? s : ""), std::string(sp ? sp : ""));
		}

		StringVector& StringVector::Split(const std::string& s, const std::string& sp) {
			value_.clear();
			if (s.empty() || sp.empty())
				return *this;

			std::string::size_type fpos, offset = 0, splen = sp.length();

			for (;(offset + splen) < s.length();) {
				fpos = s.find(sp, offset);
				if (fpos == std::string::npos) {
					value_.push_back(s.substr(offset));
					break;
				} else {
					value_.push_back(s.substr(offset, fpos - offset));
					offset = fpos + splen;
				}
			}

			return *this;
		}

		StringVector& StringVector::Append(const char* s) {
			return Append(std::string(s ? s : ""));
		}

		StringVector& StringVector::Append(const std::string& s) {
			value_.push_back(s);
			return *this;
		}

		StringVector& StringVector::Append(const std::vector<std::string>& vt) {
			value_.insert(value_.end(), vt.begin(), vt.end());
			return *this;
		}

		StringVector& StringVector::Append(const StringVector& s) {
			return Append(s.value_);
		}

		StringVector& StringVector::Append(const char* s, const char* sp) {
			StringVector vt(s, sp);
			return Append(vt);
		}

		StringVector& StringVector::Append(const std::string& s, const std::string& sp) {
			StringVector vt(s, sp);
			return Append(vt);
		}

		int StringVector::Size() const {
			return value_.size();
		}

		void StringVector::SetAt(size_t index, const std::string& s) {
			if (index >= 0 && index <= value_.size())
				value_[index] = s;
			else
				value_.push_back(s);
		}

		const std::string& StringVector::At(size_t index) const {
			if (index < 0 || index >= value_.size())
				return String::empty_;
			return value_[index];
		}

		const std::string& StringVector::operator[](int index) const {
			return At(index);
		}

		std::string StringVector::ToString(const char* sp, bool append_sp/* = false*/) {
			return ToString(std::string(sp ? sp : ""), append_sp);
		}

		std::string StringVector::ToString(const std::string& sp, bool append_sp/* = false*/) {
			std::string s = "";
			vtciter iter = value_.begin();

			for (;;){
				s += *iter;
				if ((++iter) == value_.end()) {
					if (append_sp)
						s += sp;
					break;
				}
				s += sp;
			}
			return s;
		}

		// StringMap
		StringMap::StringMap() {
		}

		StringMap::StringMap(const std::map<std::string, std::string>& m) {
			value_.insert(m.begin(), m.end());
		}

		StringMap::StringMap(const char* values, const char* sp, const char* assign_key) {
			Split(std::string(values ? values : ""), std::string(sp ? sp : ""), std::string(assign_key ? assign_key : ""));
		}

		StringMap::StringMap(const std::string& values, const std::string& sp, const std::string& assign_key) {
			Split(values, sp, assign_key);
		}

		StringMap::~StringMap() {
			value_.clear();
		}

		StringMap& StringMap::Split(const char* values, const char* sp, const char* assign_key) {
			return Split(std::string(values ? values : ""), std::string(sp ? sp : ""), std::string(assign_key ? assign_key : ""));
		}

		StringMap& StringMap::Split(const std::string& values, const std::string& sp, const std::string& assign_key) {
			value_.clear();
			if (values.empty())
				return *this;

			StringVector vt(values, sp);

			int size = vt.Size();
			for (int i = 0; i < size; i++) {
				std::string::size_type fpos = vt[i].find(assign_key);
				if (fpos == std::string::npos)
					continue;
				std::string key = vt[i].substr(0, fpos);
				std::string value = vt[i].substr(fpos + assign_key.length());
				if (key.empty())
					continue;
				value_[key] = value;
			}
			return *this;
		}

		StringMap& StringMap::Append(const char* key, const char* value) {
			return Append(std::string(key ? key : ""), std::string(value ? value : ""));
		}

		StringMap& StringMap::Append(const std::string& key, const std::string& value) {
			if (key.empty())
				return *this;
			value_[key] = value;
			return *this;
		}

		StringMap& StringMap::Append(const std::map<std::string, std::string>& m) {
			value_.insert(m.begin(), m.end());
			return *this;
		}

		StringMap& StringMap::Append(const StringMap& m) {
			return Append(m.value_);
		}

		StringMap& StringMap::Append(const char* values, const char* sp, const char* assign_key) {
			StringMap m(values, sp, assign_key);
			return Append(m);
		}

		StringMap& StringMap::Append(const std::string& values, const std::string& sp, const std::string& assign_key) {
			StringMap m(values, sp, assign_key);
			return Append(m);
		}

		void StringMap::Set(const char* key, const char* value) {
			Set(std::string(key ? key : ""), std::string(value ? value : ""));
		}

		void StringMap::Set(const std::string& key, const std::string& value) {
			if (key.empty())
				return;
			value_[key] = value;
		}

		std::string StringMap::Find(const char* key) {
			std::string k(key ? key : "");
			return Find(k);
		}

		std::string StringMap::Find(const std::string& key) {
			if (key.empty())
				return key;
			mciter iter = value_.find(key);
			if (iter != value_.end())
				return iter->second;
			return std::string();
		}

		void StringMap::Remove(const char* key) {
			std::string k(key ? key : "");
			return Remove(k);
		}

		void StringMap::Remove(const std::string& key) {
			if (key.empty())
				return;
			miter iter = value_.find(key);
			if (iter != value_.end())
				value_.erase(iter);
		}

		std::string StringMap::ToString(const char* sp, const char* assign_key, bool append_sp/* = false*/) {
			return ToString(std::string(sp ? sp : ""), std::string(assign_key ? assign_key : ""), append_sp);
		}

		std::string StringMap::ToString(const std::string& sp, const std::string& assign_key, bool append_sp/* = false*/) {
			std::string s("");

			mciter iter = value_.begin();
			for (;;) {
				s += (*iter).first;
				s += assign_key;
				s += (*iter).second;
				if ((++iter) == value_.end()) {
					if (append_sp)
						s += sp;
					break;
				}
				s += sp;
			}
			return s;
		}

	} // namespace base

} // namespace hlp


