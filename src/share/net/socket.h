#ifndef __NET_SOCKET_H_
#define __NET_SOCKET_H_

#include <QTcpSocket>
#include <QHostAddress>
#include <memory>

#include <share/protocol/message.h>

namespace share
{

namespace net
{

using namespace proto;

class message_receiver
{
public:
	virtual ~message_receiver() = default;
	virtual void receive(QHostAddress const & ip, quint16 port, message const & msg) = 0;
};

class socket : public QObject
{
	Q_OBJECT

public:
	explicit socket(QTcpSocket * s, message_receiver * receiver = nullptr);
	socket(QHostAddress const & ip_address, quint16 port, message_receiver * receiver = nullptr);

	bool connectToHost(QHostAddress const & ip, quint16 port);
	void send(message const & msg);

	QHostAddress ip_address() const;
	quint16 port() const;

	QString error() const
	{
		return socket_->errorString();
	}

protected slots:
	void recv();

private:
	std::unique_ptr<QTcpSocket> socket_;
	message_receiver * receiver_;
};

} // net
} // share

#endif // __NET_SOCKET_H_
