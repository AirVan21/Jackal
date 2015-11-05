#ifndef __PROTOCOL_MESSAGE_H_
#define __PROTOCOL_MESSAGE_H_

#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QHostAddress>
#include <QPair>
#include <memory>

namespace share
{

namespace proto
{

enum message_type
{
	/* messages without data */
	response_ack,
	response_err,

	/* messages with data */
	client_server_request,
	server_client_response,
	client_worker_request,
	worker_server_connect,
	worker_server_state_changed,
	worker_client_response
};

class message
{
public:
	virtual ~message() = default;

	static std::unique_ptr<message> deserialize(QByteArray const & bytes);

	virtual message_type get_type() const;
	virtual QByteArray serialize() const = 0;

protected:
	explicit message(message_type type);

private:
	message_type type_;
};

class string_message : public message {
public:
	string_message(message_type type, QString const & str = "");

	virtual QByteArray serialize() const override;
	static std::unique_ptr<message> deserialize(QByteArray const & bytes);

	QString const & str() const;

private:
	QString const str_;
};

class number_message : public message {
public:
	number_message(message_type type, quint32 number);

	virtual QByteArray serialize() const override;
	static std::unique_ptr<message> deserialize(QByteArray const & bytes);

	quint32 number() const;

private:
	quint32 const number_;
};

class ip_port_array_message : public message {
public:
	ip_port_array_message(message_type type, QVector<QPair<QHostAddress, quint16>> const & ip_ports)
		: message(type)
		, ip_ports_(ip_ports)
	{}

	virtual QByteArray serialize() const override;
	static std::unique_ptr<message> deserialize(QByteArray const & bytes);

	QVector<QPair<QHostAddress, quint16> > ip_ports() const;

private:
	QVector<QPair<QHostAddress, quint16>> ip_ports_;
};

class chunk_message : public message {
public:
	chunk_message(message_type type, qint32 chunk_id, QByteArray const & chunk);

	virtual QByteArray serialize() const override;
	static std::unique_ptr<message> deserialize(QByteArray const & bytes);

	quint32 id() const;
	QByteArray const & chunk() const;
	quint32 size() const;

private:
	quint32 id_;
	QByteArray chunk_;
};

} // proto
} // share

#endif // __PROTOCOL_MESSAGE_H_
