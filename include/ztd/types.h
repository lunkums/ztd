#ifndef ZTD_TYPES_H
#define ZTD_TYPES_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#define ZTD_NULL NULL

namespace ztd {
    // ********************************************************************************************
    // Primitive Types
    // ********************************************************************************************
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

    // ********************************************************************************************
    // Extra types
    // ********************************************************************************************
    typedef u32 u21;
    typedef u8 u3;

    struct NoneType {};
    const NoneType none;

    template<typename T>
    class Optional {
      public:
        Optional() : m_has_value(false) {}
        Optional(NoneType) : m_has_value(false) {}
        Optional(T value) : m_value(value), m_has_value(true) {}

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

    // A fat pointer
    template<typename T>
    struct Slice {
        Slice() : ptr(ZTD_NULL), len(0) {}

        template<usize N>
        Slice(T (&ptr)[N]) : ptr(ptr), len(N) {}

        Slice(T* ptr, usize len) : ptr(ptr), len(len) {}

        T& operator[](usize index) {
            return ptr[index];
        }

        const T& operator[](usize index) const {
            return ptr[index];
        }

        Slice<T> operator()(usize start) const {
            return Slice<T>(ptr + start, len - start);
        }

        Slice<T> operator()(usize start, usize end) const {
            if (start > len) start = len;
            if (end > len) end = len;
            if (start > end) start = end;

            return Slice<T>(ptr + start, end - start);
        }

        T* operator*() {
            return ptr;
        }

        T* ptr;
        usize len;
    };

    template<typename T, usize N>
    struct Array {
        Array() {}

        Array(const T (&arr)[N]) {
            for (usize i = 0; i < N; ++i) {
                ptr[i] = arr[i];
            }
        }

        T& operator[](usize index) {
            return ptr[index];
        }

        const T& operator[](usize index) const {
            return ptr[index];
        }

        usize len() const {
            return N;
        }

        T* operator*() {
            return ptr;
        }

        // TODO: Should this be the & operator, instead?
        operator Slice<T>() {
            return Slice<T>(ptr, N);
        }

        operator const Slice<T>() const {
            return Slice<T>(ptr, N);
        }

        T ptr[N];
    };
}

#endif
