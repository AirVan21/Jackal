#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QHostAddress>
#include <QByteArray>
#include <QVector>
#include <share/protocol/socket.h>
#include "client_logic.h"

class network_manager : public message_receiver
{
    Q_OBJECT
public:
    explicit network_manager(client_logic* logic = 0);
    void send_workers_request(quint32 task_size);
    void send_chunk(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray chunk);
private:
    client_logic* logic_;
    socket* socket_;
};

#endif // NETWORK_MANAGER_H
