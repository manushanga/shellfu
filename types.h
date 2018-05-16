#ifndef TYPES_H
#define TYPES_H
#include <string>
#include <memory>

typedef std::size_t sz;

typedef uint8_t ui8;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

template <class T>
using UPtr = std::unique_ptr<T>;

template <class T>
using SPtr = std::shared_ptr<T>;

enum class VirtualKey
{
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,
    LETTER,
    CONTROL,
    SHIFT,
    META,
    ESCAPE,
    RETURN,
    BACKSPACE,
    UNKNOWN
};

#define CAST_UI(__num) \
    static_cast<unsigned int>(__num)



#endif // TYPES_H
