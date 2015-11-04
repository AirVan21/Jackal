#include <QByteArray>
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

string_message::string_message(message_type type, QString const & str)
	: message(type)
	, str_(str)
{}

QByteArray string_message::serialize() const
{
	auto const size = str_.size();
	QByteArray bytes(1 + size, ' ');
	auto const type = get_type();
	utils::to_bytes(static_cast<quint8>(type), bytes.data());
	memcpy(bytes.data() + 1, str_.data(), size);
	return bytes;
}

std::unique_ptr<message> string_message::deserialize(QByteArray const & bytes)
{
	quint8 tmp_type = 0;
	utils::from_bytes(bytes, tmp_type);
	auto const type = static_cast<message_type>(tmp_type);
	if (message_type::response_ack != type && message_type::response_err != type)
		assert(false && "Message type is not string");
	QString str(bytes.data() + 1);
	return create_message<string_message>(type, str);
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
	QByteArray bytes(5, ' ');
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
	QByteArray bytes(1 + size * 6, ' ');
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

chunk_message::chunk_message(message_type type, qint32 chunk_id, char const * chunk, quint32 size)
	: message(type)
	, id_(chunk_id)
	, chunk_(new char[size])
	, size_(size)
{
	memcpy(chunk_, chunk, size);
}

chunk_message::~chunk_message()
{
	delete[] chunk_;
}

QByteArray chunk_message::serialize() const
{
	QByteArray bytes(5 + size_, ' ');
	auto const type = get_type();
	utils::to_bytes(static_cast<quint8>(type), bytes.data());
	utils::to_bytes(id_, bytes.data() + 1);
	memcpy(bytes.data() + 5, chunk_, size_);
	return bytes;
}

std::unique_ptr<message> chunk_message::deserialize(QByteArray const & bytes)
{
	quint8 tmp_type = 0;
	utils::from_bytes(bytes.data(), tmp_type);
	auto const type = static_cast<message_type>(tmp_type);
	auto id = 0;
	utils::from_bytes(bytes.data() + 1, id);
	auto const size = bytes.size() - 5;
	return create_message<chunk_message>(type, id, bytes.data(), size);
}

char const * chunk_message::chunk() const
{
	return chunk_;
}

quint32 chunk_message::size() const
{
	return size_;
}

quint32 chunk_message::id() const
{
	return id_;
}

} // proto
} // share
