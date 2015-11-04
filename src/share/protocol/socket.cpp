#include <cassert>

#include "utils/utils.h"

#include "socket.h"
#include "message_factory.hpp"

namespace share
{

namespace proto
{

socket::socket(message_receiver * receiver)
	: receiver_(receiver)
{
	connect(this, SIGNAL(readyRead()), this, SLOT(recv()));
}

socket::socket(QHostAddress const & ip_address, quint16 port, message_receiver * receiver)
	: receiver_(receiver)
{
	connectToHost(ip_address, port);
	waitForConnected();
	connect(this, SIGNAL(readyRead()), this, SLOT(recv()));
}

void socket::send(message const & msg)
{
	QByteArray msg_bytes = msg.serialize();
	QByteArray packet(4, ' ');
	utils::to_bytes(msg_bytes.size(), packet.data());
	packet.append(msg_bytes);
	write(packet, packet.size());
}

void socket::recv()
{
	QByteArray size_bytes(4, ' ');
	read(size_bytes.data(), 4);
	quint32 size = 0;
	utils::from_bytes(size_bytes, size);

	QByteArray message_bytes(size, ' ');
	read(message_bytes.data(), size);

	if (receiver_)
		receiver_->receive(data_message::deserialize(message_bytes));
}

QHostAddress socket::ip_address() const {
	return peerAddress();
}

quint16 socket::port() const {
	return peerPort();
}


} // proto
} // share
