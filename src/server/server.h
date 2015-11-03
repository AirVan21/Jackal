#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "../share/protocol/socket_wrapper.h"
#include "../share/protocol/message.h"

class server : public QObject {
    Q_OBJECT
public:
    explicit server(QObject* parent = 0);
signals:
//    void new_outcoming_message();
public slots:
//    void new_worker();
//    void new_active_worker();
//    void new_incoming_message();
    void newConnection();
private:
    QTcpServer* server_;
    static const int port_ = 8080;
    //all workers
    //static QQueue<worker> workers_;
    //worker -> ip + port
    //static QMap<worker, QString> active_workers_;

};

#endif // SERVER_H
