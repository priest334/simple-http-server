#include "net/socket_handle.h"

#ifdef OS_WIN
#	include <winsock2.h>
#	include <ws2tcpip.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <unistd.h>
#	include <fcntl.h>
#	include <netdb.h>
#	include <string.h>
#	include <netinet/in.h>
#	include <netinet/tcp.h>
#	include <arpa/inet.h>
#endif

namespace hlp {
	namespace net {
		namespace {
			int SetSockOption(SocketHandle sock, int name, const void* value, int length, int level) {
	#ifdef OS_WIN
				return ::setsockopt(sock, level, name, (const char*)value, (SockLengthType)length);
	#else
				return ::setsockopt(sock, level, name, (const char*)value, (SockLengthType)length);
	#endif
			}

			int GetSockOption(SocketHandle sock, int name, void* value, int* length, int level) {
	#ifdef OS_WIN
				return ::getsockopt(sock, level, name, (char*)value, (SockLengthType*)length);
	#else
				return ::getsockopt(sock, level, name, (char*)value, (SockLengthType*)length);
	#endif
			}
		}


		int SetNonBlocking(SocketHandle sock, bool nonblocking) {
#ifdef OS_WIN
			u_long value = nonblocking ? 1 : 0;
			return ::ioctlsocket(sock, FIONBIO, &value);
#else
			int opts = fcntl(fd, F_GETFL);
			if (opts < 0)
				return -1;
			if (nonblocking)
				opts |= O_NONBLOCK;
			else
				opts &= ~O_NONBLOCK;
			return fcntl(fd, F_SETFL, opts);
#endif
		}
		
	} // namespace net
} // namespace hlp



