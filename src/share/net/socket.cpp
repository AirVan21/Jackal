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
	, need_manualy_delete_socket_(false)
	, receiver_(receiver)
{
	connect(socket_, SIGNAL(readyRead()), this, SLOT(recv()));
	connect(socket_, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error_slot(QAbstractSocket::SocketError)));
}

socket::socket(QHostAddress const & ip_address, quint16 port, message_receiver * receiver)
	: socket(new QTcpSocket(), receiver)
{
	need_manualy_delete_socket_ = true;
	socket_->connectToHost(ip_address, port);
	socket_->waitForConnected();
}

socket::~socket()
{
	if (need_manualy_delete_socket_)
		delete socket_;
	else
		socket_->deleteLater();
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
	while (socket_->bytesAvailable())
	{
		while (4 > socket_->bytesAvailable())
			socket_->waitForReadyRead();
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
			while (0 == socket_->bytesAvailable())
				socket_->waitForReadyRead();
			qint64 need_read = size > 512 ? 512 : size;
			qint64 const available = socket_->bytesAvailable();
			need_read = need_read > available ? available : need_read;

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

void socket::error_slot(QAbstractSocket::SocketError e)
{
	switch (e)
	{
		case QAbstractSocket::SocketError::ConnectionRefusedError:
		case QAbstractSocket::SocketError::RemoteHostClosedError:
			emit disconnected();
			break;
		default:
			qDebug() << "Error on socket :(";
	}
}

bool socket::connect_to_host(QHostAddress const & ip, quint16 port)
{
	socket_->connectToHost(ip, port);
	if (!socket_->waitForConnected())
		return false;
	return true;
}

QHostAddress socket::ip_address() const
{
	return socket_->peerAddress();
}

quint16 socket::port() const
{
	return socket_->peerPort();
}

} // net
} // share
