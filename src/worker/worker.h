#ifndef __WORKER_WORKER_H_
#define __WORKER_WORKER_H_

#include <QTcpServer>
#include <QHostAddress>

#include <share/protocol/socket.h>
#include "ffmpeg_wrapper.h"

using namespace share::proto;

class worker : public QTcpServer, public message_receiver
{
	Q_OBJECT

public:
	worker(quint16 port);
	~worker();

	bool connect_to_server(QHostAddress const & ip, quint16 port);

	virtual void receive(QHostAddress const & ip, quint16 port, std::unique_ptr<message> && msg) override;

protected slots:
	void incomingConnection(quintptr descriptor);

private:
	socket * find_socket(QHostAddress const & ip, quint16 port);

private:
	share::proto::socket server_socket_;
	quint16 port_;
	QVector<socket *> client_sockets_; /// workers sockets
	ffmpeg_wrapper coder;
};

#endif // __WORKER_WORKER_H_
