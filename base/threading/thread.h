
#ifndef __BASE_THREADING_THREAD_H__
#define __BASE_THREADING_THREAD_H__

#include <string>

#include "base/disallow_copy_and_assign.h"
#include "base/threading/thread_handle.h"


namespace hlp {
	namespace base {

		class ThreadManager;

		class Thread {
		public:
			Thread(const std::string& name, bool joinable = true, ThreadManager* manager = NULL);
			virtual ~Thread();
			virtual int ThreadMain() = 0;

			const std::string& Name() const;
			bool IsJoinable() const;

			void Attach(ThreadHandleType handle);
			ThreadHandleType& Handle();

			void AttachManager(ThreadManager* manager);
			ThreadManager* GetManager() const;
			bool IsSameManager(ThreadManager* manager);

			void Switch(int ms) const;

		private:
			std::string name_;
			ThreadHandleType handle_;
			bool joinable_;
			ThreadManager* manager_;

			DISALLOW_COPY_AND_ASSIGN(Thread);
		};

	} // namespace base
} // namespace hlp

#endif // __BASE_THREADING_THREAD_H__

