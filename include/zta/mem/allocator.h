#ifndef ZTA_MEM_ALLOCATOR_H
#define ZTA_MEM_ALLOCATOR_H

#include "zta/mem/alignment.h"

namespace zta { namespace mem {
    struct Allocator {
        struct VTable {
            // void* (*alloc)(std::size_t len, Alignment alignment, std::size_t ret_addr);

            // bool (*resize)(
            //     MemorySlice memory,
            //     Alignment alignment,
            //     std::size_t new_len,
            //     std::size_t ret_addr
            // );

            // unsigned char* (*remap)(
            //     MemorySlice memory,
            //     Alignment alignment,
            //     std::size_t new_len,
            //     std::size_t ret_addr
            // );

            // void (*free)(void* context, MemorySlice memory, Alignment alignment, std::size_t ret_addr);

            Optional<u8*> (*alloc)(void*, usize len, Alignment alignment, usize ret_addr);
        };

        static bool no_resize(void*, Slice<u8>, Alignment, usize, usize) {
            return false;
        }

        static Optional<u8*> no_remap(void*, Slice<u8>, Alignment, usize, usize) {
            return none;
        }

        static void no_free(void*, Slice<u8>, Alignment, usize) {}

        Optional<u8*> raw_alloc(usize len, Alignment alignment, usize ret_addr) {
            return vtable.alloc(ptr, len, alignment, ret_addr);
        }

        bool raw_resize(Slice<u8> memory, Alignment alignment, usize new_len, usize ret_addr) {
            // FIXME: Implement me
            // return vtable.resize(ptr, memory, alignment, new_len, ret_addr);
            return false;
        }

        Optional<u8*> raw_remap(
            Slice<u8> memory,
            Alignment alignment,
            usize new_len,
            usize ret_addr
        ) {
            // FIXME: Implement me
            // return vtable.remap(ptr, memory, alignment, new_len, ret_addr);
            return none;
        }

        void raw_free(Slice<u8> memory, Alignment alignment, usize ret_addr) {
            // FIXME: Implement me
            // return vtable.free(ptr, memory, alignment, ret_addr);
        }

        void* ptr;
        VTable vtable;
    };
}}

#endif
