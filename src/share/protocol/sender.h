#ifndef __PROTOCOL_SENDER_H_
#define __PROTOCOL_SENDER_H_

#include <qt5/QtNetwork/QTcpSocket>
#include <memory>

#include "message.h"

namespace share { namespace proto {

class sender {
public:
	sender(std::shared_ptr<QTcpSocket> socket);
	void send(message const & msg);

private:
	std::shared_ptr<QTcpSocket> socket_;
};

} // share
} // proto

#endif // __PROTOCOL_SENDER_H_
