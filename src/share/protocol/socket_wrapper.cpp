#include "utils/utils.h"

#include "socket_wrapper.h"

namespace share
{

namespace proto
{

socket_wrapper::socket_wrapper(QTcpSocket * socket)
	: socket_(socket)
{}

socket_wrapper::~socket_wrapper()
{
	socket_->close();
}

void socket_wrapper::send(message const & /*msg*/)
{
	QByteArray message_bytes;

	uint32_t const size = message_bytes.size();
	QByteArray packet(4, ' ');
	utils::to_bytes(size, packet.data());

	packet.append(message_bytes);
	socket_->write(packet, packet.size());
}

message socket_wrapper::recv()
{
	QByteArray size_bytes(4, ' ');
	socket_->read(size_bytes.data(), 4);
	uint64_t size = 0;
	utils::from_bytes(size_bytes, size);

	QByteArray message_bytes(size, ' ');
	socket_->read(message_bytes.data(), size);

	return data_message(response_ack, nullptr, 0);
}

} // proto
} // share
