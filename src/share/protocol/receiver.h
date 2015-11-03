#ifndef __PROTOCOL_RECEIVER_H__
#define __PROTOCOL_RECEIVER_H__

#include <qt5/QtNetwork/QTcpSocket>
#include <memory>

#include "message.h"

namespace share { namespace proto {

class receiver {
public:
	receiver(std::shared_ptr<QTcpSocket> socket);
	message receive();

private:
	std::shared_ptr<QTcpSocket> socket_;
};

} // namespace share
} // namespace proto

#endif // __PROTOCOL_RECEIVER_H__
