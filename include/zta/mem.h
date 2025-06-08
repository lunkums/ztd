#ifndef ZTA_MEM_H
#define ZTA_MEM_H

#include "zta/mem/alignment.h"
#include "zta/mem/allocator.h"

namespace zta { namespace mem {
    template<typename T>
    Slice<u8> as_bytes(T* ptr) {
        // TODO: Verify this formally
        return Slice<u8>(reinterpret_cast<u8*>(ptr), static_cast<usize>(sizeof(ptr) / sizeof(u8)));
    }
}}

#endif
