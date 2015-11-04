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
