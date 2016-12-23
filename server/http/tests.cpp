#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "base/platform_spec.h"
#include "base/platform_functions.h"
#ifdef OS_WIN
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#endif

#include "base/time/time.h"
#include "server/http/service.h"
#include "log/log.h"

using namespace hlp::base;

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
	content = "welcome";
	return 0;
}

int AuthServiceMain(int argc, char* argv[]) {
	HttpService* service = new HttpService();
	service->SetServiceCallback("/hello", HelloCallback);
	service->Start("0.0.0.0", 32052);
	while (true) {
		Time::Sleep(1000);
	}
	service->Stop();
	return 0;
}

int main(int argc, char* argv[]) {
	
#ifdef OS_WIN
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	InitLogging("./", true);

	DWORD dwBegin = Time::GetTickCount(), dwEnd;
	for (int i = 0; i < 100000; i++) {
		Info() << "info: " << std::setfill(' ') << std::setw(8) << std::hex << i;
	}
	dwEnd = Time::GetTickCount();
	Info() << "total: " << dwEnd - dwBegin;

	dwBegin = Time::GetTickCount();
	for (int i = 0; i < 100000; i++) {
		Warning() << "warn: " << std::setfill(' ') << std::setw(8) << std::hex << i;
	}
	dwEnd = Time::GetTickCount();
	Warning() << "total: " << dwEnd - dwBegin;

	dwBegin = Time::GetTickCount();
	for (int i = 0; i < 100000; i++) {
		Error() << "error: " << std::setfill(' ') << std::setw(8) << std::hex << i;
	}
	dwEnd = Time::GetTickCount();
	Error() << "total: " << dwEnd - dwBegin;

	dwBegin = Time::GetTickCount();
	for (int i = 0; i < 100000; i++) {
		Fatal() << "fatal: " << std::setfill(' ') << std::setw(8) << std::hex << i;
	}
	dwEnd = Time::GetTickCount();
	Fatal() << "total: " << dwEnd - dwBegin;


	//FILE* file = fopen("./DIRECT", "a+");
	std::ofstream file_;
	file_.open("./DIRECT", std::ios::out | std::ios::app);
	if (file_.is_open()) {
		dwBegin = Time::GetTickCount();
		char line[100] = { 0 };
		for (int i = 0; i < 100000; i++) {
			struct tm t;
			char prefix[24] = { 0 };
			time_t timestamp = time(NULL);
			LocalTime(&t, &timestamp);
			//strftime(prefix, 24, "[%Y-%m-%d %H:%M:%S]", &t);

			file_ << std::dec <<std::setw(4) << t.tm_year+1900 << "-"
				<< std::setw(2) << t.tm_mon+1 << "-"
				<< std::setw(2) << t.tm_mday << " "
				<< std::setw(2) << t.tm_hour << ":"
				<< std::setw(2) << t.tm_min << ":"
				<< std::setw(2) << t.tm_sec << " "
				<< "line: "
				<< std::setw(8) << std::hex << i
				<< std::endl;

			file_.flush();
		}
		dwEnd = Time::GetTickCount();
		file_ << "total: " << std::dec <<(dwEnd - dwBegin) << std::endl;
		file_.close();
	}


	AuthServiceMain(argc, argv);

#ifdef OS_WIN
	WSACleanup();
#endif

	return 0;
}


