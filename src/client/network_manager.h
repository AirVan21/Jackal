#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QHostAddress>
#include <QByteArray>

class chunk_receiver
{
public:
    virtual void receive_from_net(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray chunk) = 0;
};

class network_manager
{
public:
    network_manager();
};

#endif // NETWORK_MANAGER_H
