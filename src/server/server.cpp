#include "server.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/socket_wrapper.h>
#include <share/protocol/message.h>
#include <QtAlgorithms>

using namespace share :: proto;

server::server(QObject* parent) : QObject(parent) {
    server_ = new QTcpServer(this);
    connect(server_, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server_->listen(QHostAddress::Any, port_)) {
        qDebug() << "Couldn't start server!";
    } else {
        qDebug() << "Server started!";
    }
}

void server :: add_new_worker(const QHostAddress &ip, quint16 port)
{
    workers_.push_back(worker_descriptor(ip, port, 0));
}

void server :: update_worker_load_factor(const QHostAddress &ip, quint16 port, quint32 load_factor)
{
    for (auto it = workers_.begin(); it != workers_.end(); ++it)
    {

        if (it->get_ip() == ip && it->get_port() == port)
        {
            it->set_load_factor(load_factor);
        }
    }
}

QVector<QPair<QHostAddress, quint16> > server::get_workers()
{
    QVector<QPair<QHostAddress, quint16> > workers;
    qSort(workers_.begin(), workers_.end());
    /*
     * And if there are less than five workers?
     */
    for (quint32 i = 0; i < 5; ++i)
    {
        workers.push_back(QPair<QHostAddress, quint16>(workers_[i].get_ip(), workers_[i].get_port()));
    }
    return workers;
}

void server :: newConnection() {
    socket_wrapper socket(server_->nextPendingConnection());
    message msg = socket.recv();
    switch (msg.get_type()) {
        case client_server_request : {
            /* give 5 free workers
             * their ip adresses and ports
             */

            break;
        }

        case worker_server_connect : {
            /* add new worker_wrapper
             * to free workers
             */

            break;
        }

        default: {
            break;
        }
    }
}
