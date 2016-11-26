#pragma once
#include "base/platform_spec.h"

#include <string>
#include <map>

#ifdef OS_WIN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

#include "base/threading/thread_pool.h"

struct event_base;
struct evhttp;
struct evhttp_bound_socket;
struct evhttp_connection;
struct evhttp_request;

typedef enum enumRequestCommandType {
	HTTP_NOT_SUPPORTED = -1,
	HTTP_REQ_GET = 0,
	HTTP_REQ_POST
}RequestCommandType;

typedef std::string RequestUri;
typedef int ResponseCode;
typedef std::string ResponseCodeText;
typedef std::string ResponseContent;

typedef std::map<std::string, std::string> HttpHeaders;
typedef HttpHeaders::iterator HttpHeadersIter;
typedef HttpHeaders::const_iterator HttpHeadersConstIter;
typedef std::map<std::string, std::string> HttpQueries;
typedef HttpQueries::iterator HttpQueriesIter;
typedef HttpQueries::const_iterator HttpQueriesConstIter;

typedef int(*ServiceCallback)(
	RequestCommandType, 
	const RequestUri&, 
	const HttpHeaders&, 
	const HttpQueries&,
	ResponseCode&, 
	ResponseCodeText&, 
	HttpHeaders&, 
	ResponseContent&);

class HttpService
{
public:
	HttpService();
	~HttpService();

	void SetServiceCallback(const RequestUri& uri, ServiceCallback cb);
	
	int Start(const std::string& node, unsigned short service, int threads = 10);
	void Stop();
	void Dispatch(struct evhttp_request* req);

	class ThreadDispatchLoop : public hlp::base::ThreadPool::Task {
	public:
		ThreadDispatchLoop(HttpService* service, struct evhttp_bound_socket* handle);
		void Run();
		HttpService* Service() const {
			return service_;
		}

	private:
		HttpService* service_;
		struct event_base* base_;
		struct evhttp* http_;
		struct evhttp_bound_socket* handle_;
	};

private:
	struct event_base* base_;
	struct evhttp* http_;
	struct evhttp_bound_socket* handle_;
	hlp::base::ThreadPool* thread_pool_;
	typedef std::map<RequestUri, ServiceCallback> ServiceCallbackSet;
	typedef ServiceCallbackSet::const_iterator ServiceCallbackSetIter;
	ServiceCallbackSet service_callbacks_;
	ServiceCallback unknown_callback_;
};

