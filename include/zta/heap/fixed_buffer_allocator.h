#ifndef ZTA_HEAP_FIXED_BUFFER_ALLOCATOR_H
#define ZTA_HEAP_FIXED_BUFFER_ALLOCATOR_H

#include "zta/mem.h"
#include "zta/mem/allocator.h"
#include "zta/types.h"

namespace zta { namespace heap {
    struct FixedBufferAllocator {
        static Optional<u8*> alloc(void* ctx, usize n, mem::Alignment alignment, usize ra) {
            return reinterpret_cast<FixedBufferAllocator*>(ctx)->alloc(n, alignment, ra);
        }

        static FixedBufferAllocator init(Slice<u8> buffer) {
            FixedBufferAllocator a;
            a.buffer = buffer;
            a.end_index = 0;
            return a;
        }

        mem::Allocator allocator() {
            mem::Allocator::VTable vtable;
            vtable.alloc = &FixedBufferAllocator::alloc;
            // vtable.resize = ?;
            // vtable.remap = ?;
            // vtable.free = ?;
            mem::Allocator a;
            a.ptr = this;
            a.vtable = vtable;
            return a;
        }

        Optional<u8*> alloc(usize n, mem::Alignment alignment, usize ra) {
            usize ptr_align = alignment.to_byte_units();
            Optional<usize> adjusted_off =
                mem::align_pointer_offset(buffer.ptr + end_index, ptr_align);
            if (!adjusted_off.has_value()) {
                return none;
            }
            usize adjusted_index = end_index + *adjusted_off;
            usize new_end_index = adjusted_index + n;
            if (new_end_index > buffer.len) {
                return none;
            }
            end_index = new_end_index;
            return buffer.ptr + adjusted_index;
        }

        void reset() {
            end_index = 0;
        }

        usize end_index;
        Slice<u8> buffer;
    };
}}

#endif
