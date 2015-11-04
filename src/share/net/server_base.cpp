#include <QtAlgorithms>

#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>

#include "server_base.h"

namespace share
{

namespace net
{

server_base::server_base(quint16 port)
	: port_(port)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(accept()));
	if (!listen(QHostAddress::Any, port_))
		qDebug() << "Can't start server: " << errorString();
}

server_base::~server_base()
{
	for (auto s: connections_sockets_)
		delete s;
}

void server_base::accept()
{
	qDebug() << "hello from new connection";
	socket * s = new socket(nextPendingConnection(), this);
	connections_sockets_.push_back(s);
}

socket * server_base::find_socket(QHostAddress const & ip, quint16 port)
{
	for (auto sock: connections_sockets_)
		if (ip == sock->ip_address() && port == sock->port())
			return sock;
	return nullptr;
}

} // net
} // share
