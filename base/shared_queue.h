#ifndef __BASE_SHARED_QUEUE_H__
#define __BASE_SHARED_QUEUE_H__

#include <queue>

#include "base/disallow_copy_and_assign.h"
#include "base/sync/lock.h"
#include "base/sync/signal_event.h"

namespace hlp {
	namespace base {
		template <class Context>
		class SharedQueue {

		public:
			SharedQueue() : ready_(&lock_) {}
			~SharedQueue() {}
		public:
			void Push(const Context& ctx) {
				{
					AutoLock locked(lock_);
					queue_.push(ctx);
				}
				ready_.Signal();
			}

			Context Get() {
				Context ctx;

				{
					AutoLock locked(lock_);
					if (queue_.empty())
						ready_.Wait();
					ctx = queue_.front();
					queue_.pop();
				}

				return ctx;
			}

			void Clear() {
				{
					AutoLock locked(lock_);
					while (!queue_.empty())
						queue_.pop();
				}
				ready_.Signal();
			}

		private:
			std::queue<Context> queue_;
			Lock lock_;
			SignalEvent ready_;
			DISALLOW_COPY_AND_ASSIGN(SharedQueue);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_SHARED_QUEUE_H__


