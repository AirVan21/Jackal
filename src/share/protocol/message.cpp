#include <cstring>

#include "message.h"

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


data_message::data_message(message_type type, char const * data, uint32_t size)
	: message(type)
	, data_(new char[size])
	, size_(size)
{
	memcpy(data_, data, size);
}

data_message::~data_message()
{
	delete[] data_;
}

char const * data_message::data() const
{
	return data_;
}

uint32_t data_message::size() const
{
	return size_;
}

} // proto
} // share
