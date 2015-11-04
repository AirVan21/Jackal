#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>
#include <share/net/socket.h>

#include "network_manager.h"
#include "client_logic.h"

using namespace share::proto;

network_manager::network_manager(client_logic * logic)
	: logic_(logic)
	, socket_(QHostAddress("127.0.0.1"), 8080, nullptr)
{}

void network_manager::receive(QHostAddress const & /*ip*/, quint16 /*port*/, std::unique_ptr<message> && /*msg*/) {
}

void network_manager::send_workers_request(quint32 task_size)
{
	auto msg = create_message<number_message>(client_server_request, task_size);
	socket_.send(*msg);
}

void network_manager::send_chunk(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray const & chunk)
{
	if (logic_)
		logic_->recieve_chunk(ip, port, chunk_id, chunk);
}
