#include <cassert>

#include <share/protocol/message_factory.hpp>
#include <share/utils/utils.h>

#include "socket.h"

namespace share
{

namespace net
{

socket::socket(QTcpSocket * s, message_receiver * receiver)
	: socket_(s)
	, receiver_(receiver)
{
	connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(recv()));
}

socket::socket(QHostAddress const & ip_address, quint16 port, message_receiver * receiver)
	: socket_(std::make_unique<QTcpSocket>())
	, receiver_(receiver)
{
	connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(recv()));
	socket_->connectToHost(ip_address, port);
	socket_->waitForConnected();
}

void socket::send(message const & msg)
{
	QByteArray msg_bytes = msg.serialize();
	QByteArray packet(4, '\0');
	quint32 const size = msg_bytes.size();
	utils::to_bytes(size, packet.data());
	packet += msg_bytes;
	if (packet.size() != socket_->write(packet))
		qDebug() << socket_->errorString();
}

void socket::recv()
{
	qDebug() << "Socket receiving message";
	QByteArray size_bytes(4, '\0');
	socket_->read(size_bytes.data(), 4);
	quint32 size = 0;
	utils::from_bytes(size_bytes, size);

	QByteArray message_bytes(size, '\0');
	socket_->read(message_bytes.data(), size);

	auto msg = message::deserialize(message_bytes);
	if (receiver_)
		receiver_->receive(ip_address(), port(), *msg);
}

bool socket::connectToHost(QHostAddress const & ip, quint16 port)
{
	socket_->connectToHost(ip, port);
	if (!socket_->waitForConnected())
		return false;
	return true;
}

QHostAddress socket::ip_address() const {
	return socket_->peerAddress();
}

quint16 socket::port() const {
	return socket_->peerPort();
}

} // net
} // share
