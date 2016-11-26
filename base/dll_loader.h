#ifndef __BASE_DLL_LOADER_H__
#define __BASE_DLL_LOADER_H__

#include "base/platform_spec.h"
#include "base/disallow_copy_and_assign.h"

namespace hlp {
	namespace base {

#if (OS_WIN)
#include <Windows.h>
#define HLIBRARY HMODULE
#else
#include <dlfcn.h>
#define HLIBRARY void*
#endif
		typedef void(*EntryType)();
		class ExportEntryType {
		public:
			ExportEntryType(EntryType entry) :
				entry_(entry) {
			}
			template<typename Type>
			operator Type() const {
				return reinterpret_cast<Type>(entry_);
			}
		private:
			EntryType entry_;
		};

		class DllLoader
		{
		public:
			DllLoader(const char* name) : library_(NULL) {
#if (OS_WIN)
				library_ = LoadLibraryA(name);
#else
				library_ = dlopen(name, RTLD_LAZY);
#endif
			}
			~DllLoader() {
				if (!library_) {
#if (OS_WIN)
					FreeLibrary(library_);
#else
					dlclose(library_);
#endif
				}
			}
			ExportEntryType Get(const char* name) {
				if (!library_ || !name || *name == '\0')
					return NULL;
#if (OS_WIN)
				return ExportEntryType(reinterpret_cast<EntryType>(GetProcAddress(library_, name)));
#else
				return ExportEntryType(reinterpret_cast<EntryType>(dlsym(library_, name)));
#endif	
			}

		private:
			HLIBRARY library_;
			DISALLOW_COPY_AND_ASSIGN(DllLoader);
		};
	} // namespace base
} // namespace hlp

#endif // __BASE_DLL_LOADER_H__


