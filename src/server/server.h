#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QDebug>
#include <QVector>
#include <memory>
#include <share/protocol/message.h>
#include <share/net/socket.h>

#include "worker_manager.h"

using namespace share::proto;
using namespace share::net;

class server : public QTcpServer, public message_receiver
{
	Q_OBJECT

public:
	explicit server(quint16 port);
	~server();

	virtual void receive(QHostAddress const & ip, quint16 port, std::unique_ptr<message> && msg) override;

protected slots:
	void incomingConnection(quintptr descriptor);

private:
	socket * find_socket(QHostAddress const & ip, quint16 port);

private:
	quint16 const port_;
	QVector<socket *> worker_sockets_; /// workers sockets
	worker_manager workers_manager_;
};

#endif // SERVER_H
