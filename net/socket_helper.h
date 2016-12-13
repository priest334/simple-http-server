#ifndef __NET_SOCKET_HELPER_H__
#define __NET_SOCKET_HELPER_H__

#include "net/socket_handle.h"

namespace hlp {
	namespace net {
		int SetNonBlocking(SocketHandle sock, bool nonblocking);
	} // namespace net
} // namespace hlp

#endif // __NET_SOCKET_HELPER_H__


