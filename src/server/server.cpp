#include "server.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>
#include <QtAlgorithms>

using namespace share :: proto;

server::server(quint16 port)
	: port_(port)
{
	if (!listen(QHostAddress::Any, port_))
		qDebug() << "Can't start server: " << errorString();
}

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

void server::receive(QHostAddress const & ip, quint16 port, std::unique_ptr<message> && msg)
{
	switch (msg->get_type()) {
		case message_type::client_server_request: {
//			auto m = static_cast<number_message *>(msg.get());
			auto workers_ip_ports = workers_manager_.get_workers();
			auto response = create_message<ip_port_array_message>(
				message_type::server_client_response, workers_ip_ports);
			auto sock = find_socket(ip, port);
			sock->send(*response);
			break;
		}
		case message_type::worker_server_connect: {
			auto m = static_cast<number_message *>(msg.get());
			workers_manager_.add_new_worker(ip, m->number());
			break;
		}
		case message_type::worker_server_state_changed: {
			auto m = static_cast<number_message *>(msg.get());
			workers_manager_.update_worker_load_factor(ip, port, m->number());
			break;
		}
		default:
			qDebug() << "Unknown message type. Dropping message";
	}
}

socket * server::find_socket(QHostAddress const & ip, quint16 port)
{
	for (auto sock: worker_sockets_)
		if (ip == sock->ip_address() && port == sock->port())
			return sock;
	return nullptr;
}
