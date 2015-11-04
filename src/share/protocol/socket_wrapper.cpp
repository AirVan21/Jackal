#include <cassert>

#include "utils/utils.h"

#include "socket_wrapper.h"
#include "message_factory.hpp"

namespace share
{

namespace proto
{

socket_wrapper::socket_wrapper(QHostAddress const & ip_address, quint16 port)
	: socket_(std::make_unique<QTcpSocket>(nullptr))
{
	socket_->connectToHost(ip_address, port);
}

socket_wrapper::socket_wrapper(QTcpSocket * socket)
	: socket_(socket)
{}

socket_wrapper::~socket_wrapper()
{
	socket_->close();
}

void socket_wrapper::send(message const & msg)
{
	QByteArray msg_bytes = msg.serialize();
	QByteArray packet(4, ' ');
	utils::to_bytes(msg_bytes.size(), packet.data());
	packet.append(msg_bytes);
	socket_->write(packet, packet.size());
}

std::unique_ptr<message> socket_wrapper::recv()
{
	QByteArray size_bytes(4, ' ');
	socket_->read(size_bytes.data(), 4);
	quint32 size = 0;
	utils::from_bytes(size_bytes, size);

	QByteArray message_bytes(size, ' ');
	socket_->read(message_bytes.data(), size);

	return data_message::deserialize(message_bytes);
}

QHostAddress socket_wrapper::ip_address() const {
	return socket_->peerAddress();
}

quint16 socket_wrapper::port() const {
	return socket_->peerPort();
}


} // proto
} // share
