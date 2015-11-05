#ifndef __NET_SERVER_BASE_H_
#define __NET_SERVER_BASE_H_

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QDebug>
#include <QVector>
#include <memory>

#include <share/protocol/message.h>

#include "socket.h"

namespace share
{

namespace net
{

using namespace share::proto;

class server_base : public QTcpServer, public message_receiver
{
	Q_OBJECT

public:
	explicit server_base(quint16 port);
	~server_base();

public slots:
	virtual void accept();
	virtual void socket_disconnected();

protected:
	socket * find_socket(QHostAddress const & ip, quint16 port);
	void remove_socket(socket * sock);

protected:
	quint16 const port_;
	QVector<socket *> connections_sockets_;
};

} // net
} // share

#endif // __NET_SERVER_BASE_H_
