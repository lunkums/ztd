#ifndef ZTD_HEAP_PAGE_ALLOCATOR_H
#define ZTD_HEAP_PAGE_ALLOCATOR_H

namespace ztd { namespace heap {
    struct PageAllocator {
        static Optional<u8*> alloc(void*, usize n, mem::Alignment alignment, usize ra) {
            // FIXME: Implement me
            //assert(n > 0);
            //return map(n, alignment);
            return none;
        }

        static bool resize(
            void*,
            Slice<u8> memory,
            mem::Alignment alignment,
            usize new_len,
            usize return_address
        ) {
            // FIXME: Implement me
            //return realloc(memory, new_len, false) != null;
            return false;
        }

        static Optional<u8*> remap(
            void*,
            Slice<u8> memory,
            mem::Alignment alignment,
            usize new_len,
            usize ra
        ) {
            // FIXME: Implement me
            //return realloc(memory, new_len, true);
            return none;
        }

        static void free(void*, Slice<u8> memory, mem::Alignment alignment, usize return_address) {
            // FIXME: Implement me
            // return unmap(@alignCast(memory));
        }
    };
}}

#endif
