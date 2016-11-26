
#ifndef __BASE_SYNC_AUTOLOCK_H__
#define __BASE_SYNC_AUTOLOCK_H__
#include "base/disallow_copy_and_assign.h"
#include "base/sync/lock_handle.h"

namespace hlp {
	namespace base {

		class LockImpl;

		class AutoLock {
		public:
			AutoLock(LockImpl& lock);
			~AutoLock();
		private:
			LockImpl& lock_;

			DISALLOW_COPY_AND_ASSIGN(AutoLock);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_SYNC_AUTOLOCK_H__

