#ifndef __UTILS_UTILS_H_
#define __UTILS_UTILS_H_

#include <cstring>

namespace share
{

namespace utils
{

template<typename T>
inline void to_bytes(T value, char * bytes) {
	char const * value_ptr = reinterpret_cast<char const *>(&value);
	memcpy(bytes, value_ptr, sizeof(T));
}

template<typename T>
inline void from_bytes(char const * bytes, T & value) {
	value = *(reinterpret_cast<T *>(&bytes));
}

} // utils
} // share

#endif // __UTILS_UTILS_H_

