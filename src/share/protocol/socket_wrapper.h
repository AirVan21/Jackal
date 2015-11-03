#ifndef __PROTOCOL_SOCKET_WRAPPER_H_
#define __PROTOCOL_SOCKET_WRAPPER_H_

#include <qt5/QtNetwork/QTcpSocket>
#include <memory>

#include "message.h"

namespace share
{

namespace proto
{

class socket_wrapper
{
public:
	explicit socket_wrapper(QTcpSocket * socket);
	~socket_wrapper();

	void send(message const & msg);
	message recv();

private:
	std::unique_ptr<QTcpSocket> socket_;
};

} // proto
} // share

#endif // __PROTOCOL_SOCKET_WRAPPER_H_
