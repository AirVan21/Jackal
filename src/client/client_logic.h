#pragma once

#include <QVector>
#include <QHostAddress>
#include <QPair>

class client_logic
{
public:
    client_logic();
    void recieve_workers(QVector<QPair<QHostAddress, quint16> > ip_ports);
    void recieve_chunk(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray chunk);
};

