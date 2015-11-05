#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>

#include "worker.h"

worker::worker(quint16 port)
	: server_base(port)
	, server_socket_(new QTcpSocket(), this)
{}

bool worker::connect_to_server(QHostAddress const & ip, quint16 port)
{
	if (!server_socket_.connectToHost(ip, port)) {
		qDebug() << "Can't connect to server: " << server_socket_.error();
		return false;
	}
	auto msg = create_message<number_message>(message_type::worker_server_connect, port_);
	server_socket_.send(*msg);
	return true;
}

void worker::receive(QHostAddress const & ip, quint16 port, message const & msg)
{
	switch (msg.get_type()) {
		case message_type::client_worker_request: {
			auto m = static_cast<chunk_message const &>(msg);
			QByteArray bytes(m.chunk());
			qDebug() << "Client sent encode reques for " << m.size() << " bytes.";
			qDebug() << "Start encoding...";
			coder.encode(bytes);
			auto response = create_message<chunk_message>(
				message_type::worker_client_response, m.id(), bytes);
			auto sock = find_socket(ip, port);
			qDebug() << "Ready! Sent him response.";
			sock->send(*response);
			break;
		}
		default:
			qDebug() << "Unknown message type. Dropping message.";
	}
}
