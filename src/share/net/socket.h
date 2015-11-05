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
	~socket();

	bool connect_to_host(QHostAddress const & ip, quint16 port);
	void send(message const & msg);

	QHostAddress ip_address() const;
	quint16 port() const;

	QString error_message() const
	{
		return socket_->errorString();
	}

signals:
	void disconnected();

protected slots:
	void recv();
	void error_slot(QAbstractSocket::SocketError e);

private:
	QTcpSocket * socket_;
	bool need_manualy_delete_socket_;
	char read_buffer_[512];
	message_receiver * receiver_;
};

} // net
} // share

#endif // __NET_SOCKET_H_
