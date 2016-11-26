#include "server/http/service.h"

#include <stdlib.h>
#include <iostream>
#include "event2/util.h"
#include "event2/event.h"
#include "event2/http.h"
#include "event2/http_struct.h"
#include "event2/buffer.h"
#include "event2/keyvalq_struct.h"
#include "base/threading/thread_pool.h"
#include "base/platform_functions.h"

#define STATUS_CODE_BAD_REQUEST 400
#define STATUS_CODE_NOT_FOUND 404

enum ErrorCode {
	NOT_INITIALIZED = -1,
	SERVICE_START_OK = 0,
	INIT_EVENT_BASE_FAILED = 1,
	INIT_EVHTTP_FAILED,
	BIND_SOCKET_FAILED
};

namespace {
	int UnknownCallback(
		RequestCommandType cmdtype, 
		const RequestUri& uri, 
		const HttpHeaders& req_hdrs, 
		const HttpQueries& queries,
		ResponseCode& code, 
		ResponseCodeText& code_text, 
		HttpHeaders& resp_hdrs, 
		ResponseContent& content) {
		return -1;
	}

	void Dispatch(struct evhttp_request* req, void* arg) {
		HttpService::ThreadDispatchLoop* loop = (HttpService::ThreadDispatchLoop*)arg;
		loop->Service()->Dispatch(req);
	}

}

HttpService::HttpService()
	: unknown_callback_(UnknownCallback) {
}

HttpService::~HttpService() {
}

void HttpService::SetServiceCallback(const RequestUri& uri, ServiceCallback cb) {
	if (!cb)
		return;

	if (uri.empty()) {
		unknown_callback_ = cb;
	} else {
		service_callbacks_[uri] = cb;
	}
}

int HttpService::Start(const std::string& node, unsigned short service, int threads/* = 10*/) {
	int retval = NOT_INITIALIZED;
	do {
		base_ = event_base_new();
		if (!base_) {
			retval = INIT_EVENT_BASE_FAILED;
			break;
		}
		http_ = evhttp_new(base_);
		if (!http_) {
			retval = INIT_EVHTTP_FAILED;
			break;
		}

		handle_ = evhttp_bind_socket_with_handle(http_, node.c_str(), service);
		if (!handle_) {
			retval = BIND_SOCKET_FAILED;
			break;
		}

		thread_pool_ = new hlp::base::ThreadPool(threads);
		for (int i = 0; i < threads; i++) {
			thread_pool_->PushTask(new ThreadDispatchLoop(this, handle_));
		}

		retval = SERVICE_START_OK;	
	} while (0);

	return retval;
}

void HttpService::Stop() {
	thread_pool_->Destroy(true);
	if (http_)
		evhttp_free(http_);
	if (base_)
		event_base_free(base_);
}

void HttpService::Dispatch(struct evhttp_request* req) {
	const char* uri_path = evhttp_uri_get_path(req-> uri_elems);
	std::string uri(uri_path ? uri_path : "");

	RequestCommandType cmdtype;
	switch (evhttp_request_get_command(req)) {
	case EVHTTP_REQ_GET: cmdtype = HTTP_REQ_GET; break;
	case EVHTTP_REQ_POST: cmdtype = HTTP_REQ_POST; break;
	default: cmdtype = HTTP_NOT_SUPPORTED; break;
	}

	ServiceCallback cb = unknown_callback_;
	ServiceCallbackSetIter iter = service_callbacks_.begin();
	for (; iter != service_callbacks_.end(); ++iter) {
		if ((*iter).first == uri) {
			cb = (*iter).second;
			break;
		}
	}

	ResponseCode code;
	ResponseCodeText code_text;
	HttpHeaders resp_headers;
	ResponseContent content;
	HttpHeaders req_headers;
	HttpQueries queries;
	struct evkeyvalq* headers;
	struct evkeyval* header;

	headers = evhttp_request_get_input_headers(req);
	for (header = headers->tqh_first; header; header = header->next.tqe_next) {
		req_headers[header->key] = header->value;
	}
	
	const char* q = evhttp_uri_get_query(req->uri_elems);
	struct evkeyvalq qs;
	struct evkeyval* query;
	if (!q && 0 == evhttp_parse_query_str(q, &qs)) {
		 for (query = qs.tqh_first; query; query = query->next.tqe_next) {
			queries[query->key] = query->value;
		}
	}

	if (0 == cb(cmdtype, uri, req_headers, queries, code, code_text, resp_headers, content)) {
		struct evkeyvalq* resp_hdrs = evhttp_request_get_output_headers(req);
		HttpHeadersConstIter iter = resp_headers.begin();
		for (; iter != resp_headers.end(); ++iter) {
			evhttp_add_header(resp_hdrs, (*iter).first.c_str(), (*iter).second.c_str());
		}

		struct evbuffer* buf = evbuffer_new();
		evbuffer_add(buf, content.c_str(), content.length());
		evhttp_send_reply(req, code, code_text.c_str(), buf);
		evbuffer_free(buf);
	} else {
		evhttp_send_error(req, STATUS_CODE_NOT_FOUND, NULL);
	}
}

HttpService::ThreadDispatchLoop::ThreadDispatchLoop(HttpService* service, struct evhttp_bound_socket* handle)
	: service_(service),
	base_(event_base_new()),
	http_(evhttp_new(base_)),
	handle_(handle) {

}

void HttpService::ThreadDispatchLoop::Run() {
	//evhttp_set_timeout(http_, 30);
	evhttp_set_gencb(http_, ::Dispatch, this);
	evhttp_accept_socket(http_, evhttp_bound_socket_get_fd(handle_));
	event_base_dispatch(base_);
}



