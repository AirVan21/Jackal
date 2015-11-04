#ifndef __PROTOCOL_SOCKET_H_
#define __PROTOCOL_SOCKET_H_

#include <QTcpSocket>
#include <QHostAddress>
#include <memory>

#include "message.h"

namespace share
{

namespace proto
{

class message_receiver
{
public:
	virtual ~message_receiver() = default;
	virtual void receive(std::unique_ptr<message> && msg) = 0;
};

class socket : public QTcpSocket
{
	Q_OBJECT

public:
	explicit socket(message_receiver * receiver);
	socket(QHostAddress const & ip_address, quint16 port, message_receiver * receiver = nullptr);

	void send(message const & msg);

	QHostAddress ip_address() const;
	quint16 port() const;

signals:
	void readyRead();

protected slots:
	void recv();

private:
	message_receiver * receiver_;
};

} // proto
} // share

#endif // __PROTOCOL_SOCKET_H_
