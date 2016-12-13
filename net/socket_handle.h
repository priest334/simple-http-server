#ifndef __NET_SOCKET_HANDLE_H__
#define __NET_SOCKET_HANDLE_H__

#include "base/platform_spec.h"

#ifdef OS_WIN
#	include <winsock2.h>
#endif

namespace hlp {
	namespace net {

#if (OS_WIN)
	typedef SOCKET SocketHandle;
	typedef int SockLengthType;
	const int kInvalidSocket = INVALID_SOCKET;
#else
	typedef int SocketHandle;
	typedef socklen_t SockLengthType;
	const int kInvalidSocket = -1;
#endif
	
		SocketHandle CreateSocket(int family, int type, int protocol);
		int CloseSocket(SocketHandle sock);
	} // namespace net
} // namespace hlp

#endif // __NET_SOCKET_HANDLE_H__


