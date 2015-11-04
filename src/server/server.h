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
    void add_new_worker(QHostAddress const & ip, quint16 port);
    void update_worker_load_factor(QHostAddress const & ip, quint16 port, quint32 load_factor);
    QVector<QPair<QHostAddress, quint16> > get_workers();
signals:

public slots:
    void newConnection();
private:
    QTcpServer* server_;
    static const int port_ = 8080;
    QVector<worker_descriptor> workers_;
};

#endif // SERVER_H
