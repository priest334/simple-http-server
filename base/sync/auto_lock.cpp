
#include "base/sync/auto_lock.h"
#include "base/sync/lock.h"

namespace hlp {
	namespace base {

		AutoLock::AutoLock(LockImpl& lock) : lock_(lock) {
			lock_.Lock();
		}

		AutoLock::~AutoLock() {
			lock_.Unlock();
		}

	} // namespace base
} // namespace hlp


