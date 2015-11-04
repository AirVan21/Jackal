#ifndef __SERVER_H_
#define __SERVER_H_

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QDebug>
#include <QVector>
#include <memory>

#include <share/protocol/message.h>
#include <share/net/server_base.h>

#include "worker_manager.h"

using namespace share::proto;
using namespace share::net;

class server : public server_base
{
public:
	explicit server(quint16 port);

	virtual void receive(QHostAddress const & ip, quint16 port, message const & msg) override;

private:
	worker_manager workers_manager_;
};

#endif // SERVER_H
