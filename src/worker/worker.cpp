#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>

#include "worker.h"

worker::worker(quint16 port)
	: server_base(port)
	, server_socket_(nullptr, this)
{}

bool worker::connect_to_server(QHostAddress const & ip, quint16 port)
{
	if (!server_socket_.connectToHost(ip, port))
		return false;
	auto msg = create_message<number_message>(message_type::worker_server_connect, port_);
	server_socket_.send(*msg);
	return true;
}

void worker::receive(QHostAddress const & ip, quint16 port, message const & msg)
{
	switch (msg.get_type()) {
		case message_type::client_worker_request: {
			auto m = static_cast<chunk_message const &>(msg);
			QByteArray bytes(m.chunk(), m.size());
			coder.encode(bytes);
			auto response = create_message<chunk_message>(
				message_type::worker_client_response, m.id(), bytes.data(), bytes.size());
			auto sock = find_socket(ip, port);
			sock->send(*response);
			break;
		}
		default:
			qDebug() << "Unknown message type. Dropping message.";
	}
}
