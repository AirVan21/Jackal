#ifndef __PROTOCOL_MESSAGE_FACTORY_HPP_
#define __PROTOCOL_MESSAGE_FACTORY_HPP_

#include <functional>
#include <memory>

namespace share
{

namespace proto
{

template<typename MessageType, typename ... Args>
std::unique_ptr<MessageType> create_message(Args && ... args)
{
	return std::make_unique<MessageType>(std::forward<Args>(args)...);
}

} // proto
} // share

#endif // __PROTOCOL_MESSAGE_FACTORY_HPP_
