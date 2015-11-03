#ifndef __PROTOCOL_MESSAGE_FACTORY_HPP_
#define __PROTOCOL_MESSAGE_FACTORY_HPP_

#include <functional>

namespace share
{

namespace proto
{

template<typename MessageType, typename ... Args>
MessageType create_message(Args && ... args)
{
	return MessageType(std::forward(args)...);
}

} // proto
} // share

#endif // __PROTOCOL_MESSAGE_FACTORY_HPP_
