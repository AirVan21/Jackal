#ifndef __WORKER_WORKER_H_
#define __WORKER_WORKER_H_

#include <QTcpServer>
#include <QHostAddress>

#include <share/net/server_base.h>

#include "ffmpeg_wrapper.h"

using namespace share::proto;
using namespace share::net;

class worker : server_base
{
public:
	worker(quint16 port);

	bool connect_to_server(QHostAddress const & ip, quint16 port);

	virtual void receive(QHostAddress const & ip, quint16 port, message const & msg) override;

protected:
	virtual void socket_disconnected(socket * s) override;

private:
	share::net::socket server_socket_;
	ffmpeg_wrapper coder;
};

#endif // __WORKER_WORKER_H_
