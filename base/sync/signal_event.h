
#ifndef __BASE_SYNC_SIGNAL_EVENT_H__
#define __BASE_SYNC_SIGNAL_EVENT_H__

#include "base/platform_spec.h"
#include "base/disallow_copy_and_assign.h"
#include "base/sync/signal_event_handle.h"

namespace hlp {
	namespace base {
		class LockImpl;

		class SignalEvent {
		public:
			typedef enum {
				FAILED = -1,
				OK,
				TIMEOUT
			}WaitState;
			SignalEvent(bool init_state = false, bool manual_reset = true);
			~SignalEvent();
		public:
			int Wait(unsigned int ms = 0xffffffff);
			bool Set();
			bool Reset();

		private:
			SignalEventHandleType handle_;
			bool signal_is_enabled_;
			bool manual_reset_;
			LockImpl* lock_;
			DISALLOW_COPY_AND_ASSIGN(SignalEvent);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_SYNC_SIGNAL_EVENT_H__

