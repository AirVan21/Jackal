#include "server.h"
#include "../share/protocol/socket_wrapper.h"
#include "../share/protocol/message.h"
#include "../share/protocol/message_factory.hpp"

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
    auto msg = create_message<data_message>(response_ack, nullptr, 0);
    socket.send(msg);
}

//void server :: new_worker(){

//}

//void server :: new_active_worker() {

//}

//void server :: new_incoming_message() {

//}

//void server :: new_outcoming_message() {

//}
