#include "base/threading/thread.h"

#ifdef OS_LINUX
#	include <unistd.h>
#endif
#include "base/platform_spec.h"
#include "base/threading/thread_manager.h"

namespace hlp {
	namespace base {

		Thread::Thread(const std::string& name, bool joinable/*= true*/, ThreadManager* manager/* = NULL*/)
			: name_(name),
#if (OS_WIN && !defined USE_POSIX_PTHREAD)
			handle_(0),
#endif
			joinable_(joinable),
			manager_(manager) {
		}

		Thread::~Thread() {
		}

		const std::string& Thread::Name() const {
			return name_;
		}

		bool Thread::IsJoinable() const {
			return joinable_;
		}

		void Thread::Attach(ThreadHandleType handle) {
			handle_ = handle;
		}

		ThreadHandleType& Thread::Handle() {
			return handle_;
		}

		void Thread::AttachManager(ThreadManager* manager) {
			manager_ = manager;
		}

		ThreadManager* Thread::GetManager() const {
			return manager_;
		}

		bool Thread::IsSameManager(ThreadManager* manager) {
			return manager_ == manager;
		}

		void Thread::Switch(int ms) const {
#if OS_WIN
			SwitchToThread();
			Sleep(ms);
#else
			usleep(ms*1000);
#endif
		}

	} // namespace net
} // namespace hlp


