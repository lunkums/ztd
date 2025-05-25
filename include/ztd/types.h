#ifndef ZTD_TYPES_H
#define ZTD_TYPES_H

#include <stddef.h>
#include <stdint.h>

#define ZTD_NULL NULL

namespace ztd {
    // Primitive Types
    typedef int8_t i8;
    typedef uint8_t u8;
    typedef int16_t i16;
    typedef uint16_t u16;
    typedef int32_t i32;
    typedef uint32_t u32;
    typedef int64_t i64;
    typedef uint64_t u64;
    // typedef __int128 i128; // FIXME: Implement this
    // typedef unsigned __int128 u128; // FIXME: Implement this
    typedef intptr_t isize;
    typedef uintptr_t usize;
    // typedef _Float16 f16; // FIXME: Implement this
    typedef float f32;
    typedef double f64;
    typedef long double f80;
    // typedef _Float128 f128; // FIXME: Implement this
    typedef void anyopaque;
    typedef int anyerror; // TODO: Revisit this

    // A fat pointer
    template<typename T>
    struct slice {
        slice() : ptr(ZTD_NULL), len(0) {}

        template<usize N>
        slice(T (&ptr)[N]) : ptr(ptr), len(N) {}

        slice(T* ptr, usize len) : ptr(ptr), len(len) {}

        T& operator[](usize index) {
            return ptr[index];
        }

        const T& operator[](usize index) const {
            return ptr[index];
        }

        T* ptr;
        usize len;
    };

    struct none_type {};
    const none_type none;

    template<typename T>
    class optional {
      public:
        optional() : m_has_value(false) {}
        optional(none_type) : m_has_value(false) {}
        optional(T value) : m_value(value), m_has_value(true) {}

        bool has_value() const {
            return m_has_value;
        }

        T& value() {
            return m_value;
        }

        const T& value() const {
            return m_value;
        }

        T& operator*() {
            return m_value;
        }

        const T& operator*() const {
            return m_value;
        }
      private:
        T m_value;
        bool m_has_value;
    };
}

#endif
