#include "server.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>
#include <QtAlgorithms>

using namespace share :: proto;

server::server(quint16 port)
	: server_base(port)
{
	qDebug() << "Starting server on port " << port << " ...";
}

void server::receive(QHostAddress const & ip, quint16 port, message const & msg)
{
	switch (msg.get_type()) {
		case message_type::client_server_request: {
			qDebug() << "New client arrived";
			auto workers_ip_ports = workers_manager_.get_workers();
			auto response = create_message<ip_port_array_message>(
				message_type::server_client_response, workers_ip_ports);
			auto sock = find_socket(ip, port);
			sock->send(*response);
			qDebug() << "Sent him " << workers_ip_ports.size() << " workers.";
			break;
		}
		case message_type::worker_server_connect: {
			auto m = static_cast<number_message const &>(msg);
			workers_manager_.add_new_worker(ip, m.number());
			qDebug() << "New worker arrived";
			break;
		}
		case message_type::worker_server_state_changed: {
			auto m = static_cast<number_message const &>(msg);
			workers_manager_.update_worker_load_factor(ip, port, m.number());
			break;
		}
		default:
			qDebug() << "Unknown message type. Dropping message";
	}
}
