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
	socket * s = new socket(nextPendingConnection(), this);
	connect(s, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
	qDebug() << "New connection from " << s->ip_address() << ":" << s->port();
	connections_sockets_.push_back(s);
}

void server_base::socket_disconnected()
{
	auto s = static_cast<socket *>(sender());
	qDebug() << "Socket" << s->ip_address() << ":" << s->port() << "disconnected.";
	remove_socket(s);
	delete s;
	qDebug() << connections_sockets_.size() << " socket in pool now.";
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
