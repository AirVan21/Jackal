#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QDebug>
#include <QVector>
#include <share/protocol/socket_wrapper.h>
#include <share/protocol/message.h>
#include "worker_descriptor.h"

class server : public QObject {
    Q_OBJECT
public:
    explicit server(QObject* parent = 0);

signals:

public slots:
    void newConnection();
private:
    QTcpServer* server_;
    static const int port_ = 8080;
};

#endif // SERVER_H
