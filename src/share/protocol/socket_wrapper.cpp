#include <cassert>

#include "utils/utils.h"

#include "socket_wrapper.h"
#include "message_factory.hpp"

namespace share
{

namespace proto
{

namespace {

QByteArray message_to_bytes(message const & msg)
{
	QByteArray bytes(1, ' ');
	auto const type = msg.get_type();
	utils::to_bytes(static_cast<uint8_t>(type), bytes.data());
	switch (type) {
		case message_type::response_ack:
		case message_type::response_err:
			break;
		case message_type::client_server_request:
		case message_type::server_client_response:
		case message_type::client_worker_request:
		case message_type::worker_server_connect:
		case message_type::worker_server_state_changed:
		case message_type::worker_client_response: {
			auto data_msg = static_cast<data_message const &>(msg);
			bytes.append(data_msg.data(), data_msg.size());
			break;
		}
	}
	return bytes;
}

message bytes_to_message(QByteArray const & bytes) {
	assert(bytes.isEmpty());
	quint8 tmp_type = 0;
	utils::from_bytes(bytes.data(), tmp_type);
	auto const type = static_cast<message_type>(tmp_type);
	switch (type) {
		case message_type::response_ack:
		case message_type::response_err:
			return create_message<message>(type);
		case message_type::client_server_request:
		case message_type::server_client_response:
		case message_type::client_worker_request:
		case message_type::worker_server_connect:
		case message_type::worker_client_response: {
			uint32_t const size = bytes.size() - 1;
			return create_message<data_message>(type, bytes.data() + 1, size);
		}
		default:
			// Should throw here?
			assert(false && "Unrecognized message type");
	}
}

}

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
	QByteArray message_bytes = message_to_bytes(msg);
	quint32 const size = message_bytes.size();
	QByteArray packet(4, ' ');
	utils::to_bytes(size, packet.data());

	packet.append(message_bytes);

	socket_->write(packet, packet.size());
}

message socket_wrapper::recv()
{
	QByteArray size_bytes(4, ' ');
	socket_->read(size_bytes.data(), 4);
	quint32 size = 0;
	utils::from_bytes(size_bytes, size);

	QByteArray message_bytes(size, ' ');
	socket_->read(message_bytes.data(), size);

	return bytes_to_message(message_bytes);
}

QHostAddress socket_wrapper::ip_address() const {
	return socket_->peerAddress();
}

quint16 socket_wrapper::port() const {
	return socket_->peerPort();
}


} // proto
} // share
