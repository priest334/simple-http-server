
#ifndef __BASE_SYNC_LOCK_H__
#define __BASE_SYNC_LOCK_H__

#include "base/disallow_copy_and_assign.h"
#include "base/sync/lock_handle.h"

namespace hlp {
	namespace base {

		class LockImpl {
		public:
			LockImpl();
			~LockImpl();

			operator LockHandleType() const { return handle_; }
			LockHandleType* HandlePtr() { return &handle_; }
		public:
			bool Try();
			void Lock();
			void Unlock();

		private:
			LockHandleType handle_;
			DISALLOW_COPY_AND_ASSIGN(LockImpl);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_SYNC_LOCK_H__

