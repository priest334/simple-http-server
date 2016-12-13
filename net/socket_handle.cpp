#include "net/socket_helper.h"

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

		SocketHandle CreateSocket(int family, int type, int protocol) {
#ifdef OS_WIN
			return ::WSASocket(family, type, protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
#else
			return ::socket(family, type, protocol);
#endif
		}

		int CloseSocket(SocketHandle sock) {
#ifdef OS_WIN
			return ::closesocket(sock);
#else
			return ::close(sock);
#endif
		}
		
	} // namespace net
} // namespace hlp



