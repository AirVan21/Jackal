#include "network_manager.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>

using namespace share :: proto;

network_manager::network_manager(client_logic *logic) : logic_(logic), socket_(QHostAddress("127.0.0.1"), 8080, this)
{ }

void network_manager::send_workers_request(quint32 task_size)
{
    auto msg = message_factory<client_server_request>(client_server_request, task_size);
    socket_->send(msg);
}

void network_manager::send_chunk(const QHostAddress &ip, quint16 port, quint32 chunk_id, QByteArray chunk)
{
    logic_->recieve_chunk(ip, port, chunk_id, chunk);
}

