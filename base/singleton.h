#ifndef __BASE_SINGLETON_H__
#define __BASE_SINGLETON_H__

#include "base/once_init_provider.h"

namespace hlp {
	namespace base {

		template <class TypeName>
		class Singleton
		{
		public:
			friend TypeName* TypeName::GetInstance();
			typedef TypeName* InstancePtr;

			static InstancePtr Get() {
				once_init_provider_->Call();
				return instance_;
			}

			static void Initialize() {
				instance_ = new TypeName();
			}

		private:
			static InstancePtr instance_;
			static OnceInitProvider* once_init_provider_;

		};

		template <class TypeName>
		typename Singleton<TypeName>::InstancePtr Singleton<TypeName>::instance_ = NULL;
		template <class TypeName>
		OnceInitProvider* Singleton<TypeName>::once_init_provider_ = new OnceInitHelper(&Singleton<TypeName>::Initialize);

	} // namespace base
} // namespace hlp

#endif // __BASE_SINGLETON_H__


