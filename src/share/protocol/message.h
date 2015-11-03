#ifndef __PROTOCOL_MESSAGE_H__
#define __PROTOCOL_MESSAGE_H__

namespace share { namespace proto {

enum message_type {
	response_ack,
	response_err,
	client_server_request,
	server_client_response,
	client_worker_request,
	worker_server_connect,
	worker_client_response
};

class message {
public:
	virtual ~message() = default;

	virtual message_type get_type() const {
		return type_;
	}

protected:
	explicit message(message_type type)
		: type_(type)
	{}

private:
	message_type type_;
};

} // share
} // proto

#endif // __PROTOCOL_MESSAGE_H__
