#pragma once

#include "network_manager.h"
#include <QVector>
#include <QHostAddress>
#include <QPair>
#include <QString>
#include <QMap>

class client_logic
{
public:
    client_logic();

    void encode_file(QString const & filename);

    void recieve_workers(QVector<QPair<QHostAddress, quint16> > ip_ports);
    void recieve_chunk(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray chunk);

private:
    network_manager manager_;
    QString filename_;
    QMap<quint32, QString> map_;
    quint32 chunk_amount_;
};

