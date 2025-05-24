#ifndef ZTD_TYPES_H
#define ZTD_TYPES_H

#include <stdint.h>

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
    typedef unsigned u128;
    typedef intptr_t isize;
    typedef uintptr_t usize;
    // typedef _Float16 f16; // FIXME: Implement this
    typedef float f32;
    typedef double f64;
    typedef long f80;
    // typedef _Float128 f128; // FIXME: Implement this
    typedef void anyopaque;
    typedef int anyerror; // TODO: Revisit this
}

#endif
