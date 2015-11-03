#ifndef __PROTOCOL_MESSAGE_H__
#define __PROTOCOL_MESSAGE_H__

#include <cstdint>

using std::uint32_t;

namespace share
{

namespace proto
{

enum message_type
{
	response_ack,
	response_err,
	client_server_request,
	server_client_response,
	client_worker_request,
	worker_server_connect,
	worker_client_response
};

class message
{
public:
	virtual ~message() = default;

	virtual message_type get_type() const;

protected:
	explicit message(message_type type);

private:
	message_type type_;
};


class data_message : public message {
public:
	data_message(message_type type, char const * data, uint32_t size);
	~data_message();

	char const * data() const;
	uint32_t size() const;

private:
	char * const data_;
	uint32_t const size_;
};

} // proto
} // share

#endif // __PROTOCOL_MESSAGE_H__
