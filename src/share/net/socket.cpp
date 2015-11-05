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
	connect(socket_.get(), SIGNAL(connected()), this, SLOT(connected_slot()));
}

socket::socket(QHostAddress const & ip_address, quint16 port, message_receiver * receiver)
	: socket_(std::make_unique<QTcpSocket>(nullptr))
	, receiver_(receiver)
{
	connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(recv()));
	connect(socket_.get(), SIGNAL(connected()), this, SLOT(connected_slot()));
	socket_->connectToHost(ip_address, port);
	socket_->waitForConnected();
}

void socket::connected_slot()
{
	qDebug() << "connected!";
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
	if (socket_->bytesAvailable()) {
		qDebug() << "Socket receiving message";
		if (4 != socket_->read(read_buffer_, 4))
		{
			qDebug() << "Failed when reading packet size";
			return;
		}
		quint32 size = 0;
		utils::from_bytes(read_buffer_, size);

		QByteArray packet;
		while (size > 0) {
			qint64 need_read = size > 512 ? 512 : size;
			qint64 bytes_read = socket_->read(read_buffer_, need_read);
			if (bytes_read != need_read)
			{
				qDebug() << "Failed when reading packet size";
				return;
			}
			packet.append(read_buffer_, bytes_read);
			size -= bytes_read;
		}

		auto msg = message::deserialize(packet);
		if (receiver_)
			receiver_->receive(ip_address(), port(), *msg);
	}
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
