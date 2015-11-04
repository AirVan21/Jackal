#pragma once

#include <QVector>
#include <QHostAddress>
#include <QPair>
#include <QString>
#include <QMap>

class client_logic
{
public:
    client_logic(QString filename);
    void recieve_workers(QVector<QPair<QHostAddress, quint16> > ip_ports);
    void recieve_chunk(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray chunk);
    void run();
private:
    QString filename_;
    QMap<quint32, QString> map_;
};

