#include "sender.h"

namespace share { namespace proto {

sender::sender(std::shared_ptr<QTcpSocket> socket)
	: socket_(socket)
{}

} // share
} // proto
