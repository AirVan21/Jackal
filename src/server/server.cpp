#include "server.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>
#include <QtAlgorithms>

using namespace share :: proto;

server::server(quint16 port)
	: port_(port)
{}

server::~server()
{
	for (auto s: worker_sockets_)
		delete s;
}

void server::incomingConnection(quintptr descriptor)
{
	auto s = new socket(this);
	s->setSocketDescriptor(descriptor);
	worker_sockets_.push_back(s);
}

void server::receive(std::unique_ptr<message> && msg)
{
	switch (msg->get_type()) {
		case message_type::client_server_request:
			// do client-server stuff
			break;
		case message_type::worker_server_connect:
			// add new worker
			break;
		case message_type::worker_server_state_changed:
			// notify state changed
			break;
		default:
			qDebug() << "Unknown message type. Dropping message";
	}
}
