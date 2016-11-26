#ifndef __BASE_REFLECTABLE_H__
#define __BASE_REFLECTABLE_H__

#include <string>
#include <map>

#include "base/basic_types.h"
#include "base/disallow_copy_and_assign.h"
#include "base/singleton.h"


#define REGISTER_REFLECTABLE_CLASS(ClassName) \
	hlp::base::ReflectManager::GetInstance()->Register(#ClassName, &ClassName::CreateReflectableObjectByName)

namespace hlp {
	namespace base {
		typedef void* (*ReflectObjectCreator)();
		
		template <class TypeName>
		class ReflectBaseClass {
		public:
			static void* CreateReflectableObjectByName() {
				return new TypeName();
			}
		};

		class ReflectableClassInfo {
		public:
			ReflectableClassInfo()
				: name_(""), creator_(reinterpret_cast<ReflectObjectCreator>(0)) {
			}

			ReflectableClassInfo(const std::string& name, ReflectObjectCreator creator)
				: name_(name), creator_(creator) {
			}

			void* Create() {
				if (creator_)
					return creator_();
				return NULLPTR;
			}
		private:
			std::string name_;
			ReflectObjectCreator creator_;
		};

		template <class TypeName>
		class ReflectClass {
		public:
			ReflectClass() : ptr_(NULLPTR) {}
			ReflectClass(void* ptr) {
				ptr_ = reinterpret_cast<TypeName*>(ptr);
			}

			TypeName* operator()() const{
				return ptr_;
			}

			TypeName* operator->() const {
				return ptr_;
			}

			TypeName* Get() const{
				return ptr_;
			}

		private:
			TypeName* ptr_;
			DISALLOW_COPY_AND_ASSIGN(ReflectClass);
		};

		class ReflectManager {
			typedef std::map<std::string, ReflectableClassInfo*> RegistedClassInfos;
			typedef RegistedClassInfos::iterator RegistedClassInfosIter;
		public:
			ReflectManager() {}
			static ReflectManager* GetInstance() {
				return Singleton<ReflectManager>::Get();
			}

			int Register(const std::string& name, ReflectObjectCreator helper) {
				RegistedClassInfosIter iter = infos_.find(name);
				if (iter != infos_.end())
					return -1;
				infos_[name] = new ReflectableClassInfo(name, helper);
				return 0;
			}

			void* Get(const std::string& name) {
				RegistedClassInfosIter iter = infos_.find(name);
				if (iter != infos_.end())
					return (*iter).second->Create();
				return NULL;
			}

		private:
			RegistedClassInfos infos_;

			DISALLOW_COPY_AND_ASSIGN(ReflectManager);
		};

		class ReflectHelper {
		private:
			ReflectHelper();
		public:
			static void* Get(const std::string& name) {
				return ReflectManager::GetInstance()->Get(name);
			}
			DISALLOW_COPY_AND_ASSIGN(ReflectHelper);
		};
	} // namespace base
} // namespace hlp



#endif // __BASE_REFLECTABLE_H__


