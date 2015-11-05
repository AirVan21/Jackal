#include <QByteArray>
#include <QDataStream>
#include <cstring>
#include <cassert>

#include "utils/utils.h"
#include "message.h"
#include "message_factory.hpp"

namespace share
{

namespace proto
{

message_type message::get_type() const
{
	return type_;
}

message::message(message_type type)
	: type_(type)
{}

std::unique_ptr<message> message::deserialize(QByteArray const & bytes)
{
	quint8 tmp_type = 0;
	utils::from_bytes(bytes, tmp_type);
	auto const type = static_cast<message_type>(tmp_type);
	switch (type) {
		case response_ack:
		case response_err:
			return string_message::deserialize(bytes);
		case client_server_request:
		case worker_server_connect:
		case worker_server_state_changed:
			return number_message::deserialize(bytes);
		case server_client_response:
			return ip_port_array_message::deserialize(bytes);
		case client_worker_request:
		case worker_client_response: {
			return chunk_message::deserialize(bytes);
		}
		default:
			qDebug() << "Unknown message type.";
			assert(false && "Unknown message type");
	}
	return nullptr;
}

string_message::string_message(message_type type, QString const & str)
	: message(type)
	, str_(str)
{}

QByteArray string_message::serialize() const
{
//	auto const size = str_.size();
//	QByteArray bytes(1 + size, '\0');
//	auto const type = get_type();
//	utils::to_bytes(static_cast<quint8>(type), bytes.data());
	QByteArray bytes;
	QDataStream stream(&bytes, QIODevice::ReadWrite);
	stream << static_cast<quint8>(get_type()) << str_;
	return bytes;
}

std::unique_ptr<message> string_message::deserialize(QByteArray const & bytes)
{
//	quint8 tmp_type = 0;
//	utils::from_bytes(bytes, tmp_type);
//	auto const type = static_cast<message_type>(tmp_type);
//	if (message_type::response_ack != type && message_type::response_err != type)
//		assert(false && "Message type is not string");
//	QString str(bytes.data() + 1);

	QDataStream stream(bytes);
	quint8 type;
	stream >> type;
	QString str;
	stream >> str;
	return create_message<string_message>(static_cast<message_type>(type), str);
}

QString const & string_message::str() const
{
	return str_;
}

number_message::number_message(message_type type, quint32 number)
	: message(type)
	, number_(number)
{}

QByteArray number_message::serialize() const
{
	QByteArray bytes(5, '\0');
	auto const type = get_type();
	utils::to_bytes(static_cast<quint8>(type), bytes.data());
	utils::to_bytes(number_, bytes.data() + 1);
	return bytes;
}

std::unique_ptr<message> number_message::deserialize(QByteArray const & bytes)
{
	quint8 tmp_type = 0;
	utils::from_bytes(bytes.data(), tmp_type);
	auto const type = static_cast<message_type>(tmp_type);
	quint32 number = 0;
	utils::from_bytes(bytes.data() + 1, number);
	return create_message<number_message>(type, number);
}

quint32 number_message::number() const
{
	return number_;
}

QByteArray ip_port_array_message::serialize() const
{
	quint32 const size = ip_ports_.size();
	QByteArray bytes(1 + size * 6, '\0');
	auto const type = get_type();
	utils::to_bytes(static_cast<quint8>(type), bytes.data());
	char * ip_ports_bytes = bytes.data() + 1;
	for (auto const & ip_port : ip_ports_)
	{
		quint32 const ip = ip_port.first.toIPv4Address();
		utils::to_bytes(ip, ip_ports_bytes);
		ip_ports_bytes += 4;
		utils::to_bytes(ip_port.second, ip_ports_bytes);
		ip_ports_bytes += 2;
	}
	return bytes;
}

std::unique_ptr<message> ip_port_array_message::deserialize(QByteArray const & bytes)
{
	quint8 tmp_type = 0;
	utils::from_bytes(bytes, tmp_type);
	auto const type = static_cast<message_type>(tmp_type);
	quint32 const count = (bytes.size() - 1) / 6;
	char const * ip_ports_bytes = bytes.data() + 1;
	QVector<QPair<QHostAddress, quint16>> ip_ports;
	for (quint32 i = 0; i < count; ++i)
	{
		quint32 ip = 0;
		utils::from_bytes(ip_ports_bytes, ip);
		ip_ports_bytes += 4;
		quint16 port = 0;
		utils::from_bytes(ip_ports_bytes, port);
		ip_ports_bytes += 2;
		ip_ports.push_back({QHostAddress(ip), port});
	}
	return create_message<ip_port_array_message>(type, ip_ports);
}

QVector<QPair<QHostAddress, quint16>> ip_port_array_message::ip_ports() const
{
	return ip_ports_;
}

chunk_message::chunk_message(message_type type, qint32 chunk_id, QByteArray const & chunk)
	: message(type)
	, id_(chunk_id)
	, chunk_(chunk)
{}

QByteArray chunk_message::serialize() const
{
	QByteArray bytes;
	QDataStream stream(&bytes, QIODevice::WriteOnly);
	stream << static_cast<quint8>(get_type()) << id_ << chunk_;

	return bytes;
}

std::unique_ptr<message> chunk_message::deserialize(QByteArray const & bytes)
{
	QDataStream stream(bytes);
	quint8 type;
	stream >> type;
	quint32 id;
	stream >> id;
	quint32 size = bytes.size();
	qDebug() << size;
	QByteArray chunk(bytes.size() - 5, '\0');
	stream.readRawData(chunk.data(), bytes.size() - 5);

	return create_message<chunk_message>(static_cast<message_type>(type), id, chunk);
}

QByteArray const & chunk_message::chunk() const
{
	return chunk_;
}

quint32 chunk_message::size() const
{
	return chunk_.size();
}

quint32 chunk_message::id() const
{
	return id_;
}

} // proto
} // share
