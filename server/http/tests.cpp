#include <iostream>

#include "base/platform_spec.h"
#ifdef OS_WIN
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#include "server/http/service.h"

int HelloCallback(
	RequestCommandType cmdtype, 
	const RequestUri& uri, 
	const HttpHeaders& req_hdrs, 
	const HttpQueries& queries,
	ResponseCode& code, 
	ResponseCodeText& code_text, 
	HttpHeaders& resp_hdrs, 
	ResponseContent& content) {
	code = 200;
	code_text = "OK";
	return 0;
}

int AuthServiceMain(int argc, char* argv[]) {
	HttpService* service = new HttpService();
	service->SetServiceCallback("/hello", HelloCallback);
	service->Start("0.0.0.0", 32052);
	while (true) {
		Sleep(1000);
	}
	service->Stop();
	return 0;
}

int main(int argc, char* argv[]) {
#ifdef OS_WIN
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	AuthServiceMain(argc, argv);

#ifdef OS_WIN
	WSACleanup();
#endif

	return 0;
}


