#ifndef __BASE_ONCE_INIT_PROVIDER_H__
#define __BASE_ONCE_INIT_PROVIDER_H__

#include "base/platform_spec.h"

namespace hlp {
	namespace base {

		typedef void(*InitCallback)();

		class OnceInitProvider {
		public:
			explicit OnceInitProvider(InitCallback callback)
				: callback_(callback) {
			}
			virtual ~OnceInitProvider() {}
			virtual bool Call() = 0;

		protected:
			InitCallback callback_;
		};

#if (OS_WIN && !defined USE_POSIX_PTHREAD)
#include <Windows.h>
		class OnceInitHelper : public OnceInitProvider {
		public:
			explicit OnceInitHelper(InitCallback callback)
				: OnceInitProvider(callback) {
				finished_ = false;
				InitializeCriticalSection(&critical_section_);
			}

			~OnceInitHelper() {
				DeleteCriticalSection(&critical_section_);
			}
			
			bool Call() {
				if (finished_)
					return true;
				EnterCriticalSection(&critical_section_);
				if (!finished_) {
					callback_();
					finished_ = true;
				}
				LeaveCriticalSection(&critical_section_);
				return finished_;
			}

		private:
			CRITICAL_SECTION critical_section_;
			bool finished_;
		};
#else
#include <pthread.h>
		class OnceInitHelper : public OnceInitProvider {
		public:
			explicit OnceInitHelper(InitCallback callback)
				: OnceInitProvider(callback) {
				once_control_ = PTHREAD_ONCE_INIT;
			}
			bool Call() {
				pthread_once(&once_control_, callback_);
				return true;
			}

		private:
			pthread_once_t once_control_;
		};
#endif
		
	} // namespace base
} // namespace hlp

#endif // __BASE_ONCE_INIT_PROVIDER_H__


