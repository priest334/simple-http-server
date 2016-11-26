
#include "base/sync/try_lock.h"
#include "base/sync/lock.h"

namespace hlp {
	namespace base {

		TryLock::TryLock(LockImpl& lock) : lock_(lock), locked_(false) {
			locked_ = lock_.Try();
		}

		TryLock::~TryLock() {
			if (IsLocked())
				lock_.Unlock();
		}

		bool TryLock::IsLocked() const {
			return locked_;
		}

	} // namespace base
} // namespace hlp


