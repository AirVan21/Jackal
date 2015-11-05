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
	connect(this, SIGNAL(newConnection()), this, SLOT(accept_slot()));
	if (!listen(QHostAddress::Any, port_))
		qDebug() << "Can't start server: " << errorString();
}

server_base::~server_base()
{
	for (auto s: connections_sockets_)
		delete s;
}

void server_base::accept_slot()
{
	socket * s = new socket(nextPendingConnection(), this);
	connect(s, SIGNAL(disconnected()), this, SLOT(disconnected_slot()));
	qDebug() << s->ip_address() << ":" << s->port() << "connected.";
	connections_sockets_.push_back(s);
}

void server_base::disconnected_slot()
{
	auto s = static_cast<socket *>(sender());
	socket_disconnected(s);
	qDebug() << s->ip_address() << ":" << s->port() << "disconnected.";
	remove_socket(s);
	delete s;
}

socket * server_base::find_socket(QHostAddress const & ip, quint16 port)
{
	for (auto sock: connections_sockets_)
		if (ip == sock->ip_address() && port == sock->port())
			return sock;
	return nullptr;
}

void server_base::remove_socket(socket * sock)
{
	for (auto it = connections_sockets_.begin(); connections_sockets_.end() != it; ++it)
	{
		if (*it == sock)
		{
			connections_sockets_.erase(it);
			break;
		}
	}
}

} // net
} // share
