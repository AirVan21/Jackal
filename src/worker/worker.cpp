#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>

#include "worker.h"

worker::worker(quint16 port)
	: server_socket_(this)
	, port_(port)
{
	if (!listen(QHostAddress::Any, port_))
		qDebug() << "Can't start server: " << errorString();
}

bool worker::connect_to_server(QHostAddress const & ip, quint16 port)
{
	server_socket_.connectToHost(ip, port);
	if (!server_socket_.waitForConnected())
		return false;
	auto msg = create_message<number_message>(message_type::worker_server_connect, port_);
	server_socket_.send(*msg);
	return true;
}

worker::~worker()
{
	for (auto s: client_sockets_)
		delete s;
}

void worker::incomingConnection(quintptr descriptor)
{
	auto s = new socket(this);
	s->setSocketDescriptor(descriptor);
	client_sockets_.push_back(s);
}

void worker::receive(QHostAddress const & ip, quint16 port, std::unique_ptr<message> && msg)
{
	switch (msg->get_type()) {
		case message_type::client_worker_request: {
			auto m = static_cast<chunk_message *>(msg.get());
			QByteArray bytes(m->chunk(), m->size());
			coder.encode(bytes);
			auto response = create_message<chunk_message>(
				message_type::worker_client_response, m->id(), bytes.data(), bytes.size());
			auto sock = find_socket(ip, port);
			sock->send(*response);
			break;
		}
		default:
			qDebug() << "Unknown message type. Dropping message";
	}
}

socket * worker::find_socket(QHostAddress const & ip, quint16 port)
{
	for (auto sock: client_sockets_)
		if (ip == sock->ip_address() && port == sock->port())
			return sock;
	return nullptr;
}
