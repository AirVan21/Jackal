#include <functional>

#include "receiver.h"

namespace share { namespace proto {

receiver::receiver(std::shared_ptr<QTcpSocket> socket)
	: socket_(socket)
{}

} // share
} // proto
