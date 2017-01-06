#ifndef DBR_ENG_UTIL_TYPES_HPP
#define DBR_ENG_UTIL_TYPES_HPP

#include <cstdint>
#include <cstddef>

using std::uint64_t;
using std::uint32_t;
using std::uint16_t;
using std::uint8_t;

using std::int64_t;
using std::int32_t;
using std::int16_t;
using std::int8_t;

using std::size_t;

namespace dbr
{
	namespace eng
	{
        using byte = uint8_t;
        using sbyte = int8_t;

        namespace util
        {
            struct Size
            {
                using Type = uint32_t;

                Size() = default;
                Size(Type w, Type h)
                    : width{w},
                    height{h}
                {}

                Size(int w, int h)
                    : width{static_cast<Type>(w)},
                    height{static_cast<Type>(h)}
                {}

                Type width;
                Type height;
            };
        }
	}
}

#endif
