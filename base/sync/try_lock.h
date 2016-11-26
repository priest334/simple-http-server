
#ifndef __BASE_SYNC_TRYLOCK_H__
#define __BASE_SYNC_TRYLOCK_H__
#include "base/disallow_copy_and_assign.h"
#include "base/sync/lock_handle.h"

namespace hlp {
	namespace base {

		class LockImpl;

		class TryLock {
		public:
			TryLock(LockImpl& lock);
			~TryLock();

			bool IsLocked() const;
		private:
			LockImpl& lock_;
			bool locked_;

			DISALLOW_COPY_AND_ASSIGN(TryLock);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_SYNC_TRYLOCK_H__

