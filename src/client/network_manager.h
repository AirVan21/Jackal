#ifndef __NETWORK_MANAGER_H_
#define __NETWORK_MANAGER_H_

#include <QHostAddress>
#include <QByteArray>
#include <QVector>
#include <share/net/socket.h>

class client_logic;

using namespace share::net;

class network_manager : public message_receiver
{
public:
	explicit network_manager(client_logic * logic = 0);
	~network_manager() = default;

	virtual void receive(QHostAddress const & /*ip*/, quint16 /*port*/, std::unique_ptr<message> && /*msg*/) override;

	void send_workers_request(quint32 task_size);
	void send_chunk(QHostAddress const & ip, quint16 port, quint32 chunk_id, QByteArray const & chunk);

private:
	client_logic * logic_;
	socket socket_;
};

#endif // __NETWORK_MANAGER_H_
