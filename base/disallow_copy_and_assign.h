
#ifndef __BASE_DISALLOW_COPY_AND_ASSIGN_H__
#define __BASE_DISALLOW_COPY_AND_ASSIGN_H__

namespace hlp {
	namespace base {

		template <typename TypeName>
		class DisallowCopyAndAssign {
		private:
			DisallowCopyAndAssign(const DisallowCopyAndAssign&);
			DisallowCopyAndAssign& operator=(const DisallowCopyAndAssign&);
		};

	} // namespace base
} // namespace hlp

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	TypeName& operator=(const TypeName&)

#endif // __BASE_DISALLOW_COPY_AND_ASSIGN_H__

