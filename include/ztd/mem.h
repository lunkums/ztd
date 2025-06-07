#ifndef ZTD_MEM_H
#define ZTD_MEM_H

#include "ztd/mem/alignment.h"
#include "ztd/mem/allocator.h"

namespace ztd { namespace mem {
    template<typename T>
    slice<u8> as_bytes(T* ptr) {
        // TODO: Verify this formally
        return slice<u8>(reinterpret_cast<u8*>(ptr), static_cast<usize>(sizeof(ptr) / sizeof(u8)));
    }
}}

#endif
