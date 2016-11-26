#ifndef __BASE_FINAL_CLASS_PROVIDER_H__
#define __BASE_FINAL_CLASS_PROVIDER_H__

namespace hlp {
	namespace base {
		template <class TypeName, class Provider>
		class FinalClass {
			friend TypeName;
			friend Provider;
		private:
			FinalClass(){}
			~FinalClass(){}
		};
		
		template <class TypeName>
		class FinalClassProvider
			: virtual public FinalClass < Typename, FinalClassProvider >  {
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_FINAL_CLASS_PROVIDER_H__


