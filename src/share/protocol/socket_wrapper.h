#ifndef __PROTOCOL_SOCKET_WRAPPER_H_
#define __PROTOCOL_SOCKET_WRAPPER_H_

#include <QTcpSocket>
#include <QHostAddress>
#include <memory>

#include "message.h"

namespace share
{

namespace proto
{

class socket_wrapper
{
public:
	socket_wrapper(QHostAddress const & ip_address, quint16 port);
	explicit socket_wrapper(QTcpSocket * socket);
	~socket_wrapper();

	void send(message const & msg);
	std::unique_ptr<message> recv();

	QHostAddress ip_address() const;
	quint16 port() const;

private:
	std::unique_ptr<QTcpSocket> socket_;
};

} // proto
} // share

#endif // __PROTOCOL_SOCKET_WRAPPER_H_
