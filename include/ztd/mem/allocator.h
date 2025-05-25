#ifndef ZTD_MEM_ALLOCATOR_H
#define ZTD_MEM_ALLOCATOR_H

#include "ztd/mem/alignment.h"

namespace ztd { namespace mem {
    struct allocator {
        struct vtable {
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

            optional<u8*> (*alloc)(void*, usize len, alignment alignment, usize ret_addr);
        };

        static bool no_resize(void*, slice<u8>, alignment, usize, usize) {
            return false;
        }

        static optional<u8*> no_remap(void*, slice<u8>, alignment, usize, usize) {
            return none;
        }

        static void no_free(void*, slice<u8>, alignment, usize) {}

        optional<u8*> raw_alloc(usize len, alignment alignment, usize ret_addr) {
            return vtable.alloc(ptr, len, alignment, ret_addr);
        }

        bool raw_resize(slice<u8> memory, alignment alignment, usize new_len, usize ret_addr) {
            // FIXME: Implement me
            // return vtable.resize(ptr, memory, alignment, new_len, ret_addr);
            return false;
        }

        optional<u8*> raw_remap(
            slice<u8> memory,
            alignment alignment,
            usize new_len,
            usize ret_addr
        ) {
            // FIXME: Implement me
            // return vtable.remap(ptr, memory, alignment, new_len, ret_addr);
            return none;
        }

        void raw_free(slice<u8> memory, alignment alignment, usize ret_addr) {
            // FIXME: Implement me
            // return vtable.free(ptr, memory, alignment, ret_addr);
        }

        void* ptr;
        vtable vtable;
    };
}}

#endif
