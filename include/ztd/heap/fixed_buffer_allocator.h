#ifndef ZTD_FIXED_BUFFER_ALLOCATOR_H
#define ZTD_FIXED_BUFFER_ALLOCATOR_H

#include "ztd/mem.h"
#include "ztd/mem/allocator.h"
#include "ztd/types.h"

namespace ztd { namespace heap {
    struct fixed_buffer_allocator {
        static optional<u8*> alloc(void* ctx, usize n, mem::alignment alignment, usize ra) {
            fixed_buffer_allocator* self = reinterpret_cast<fixed_buffer_allocator*>(ctx);
            usize ptr_align = alignment.to_byte_units();
            optional<usize> adjusted_off =
                mem::align_pointer_offset(self->buffer.ptr + self->end_index, ptr_align);
            if (!adjusted_off.has_value()) {
                return none;
            }
            usize adjusted_index = self->end_index + *adjusted_off;
            usize new_end_index = adjusted_index + n;
            if (new_end_index > self->buffer.len) {
                return none;
            }
            self->end_index = new_end_index;
            return self->buffer.ptr + adjusted_index;
        }

        static fixed_buffer_allocator init(slice<u8> buffer) {
            fixed_buffer_allocator a;
            a.buffer = buffer;
            a.end_index = 0;
            return a;
        }

        mem::allocator allocator() {
            struct mem::allocator::vtable vtable;
            vtable.alloc = &fixed_buffer_allocator::alloc;
            // vtable.resize = ?;
            // vtable.remap = ?;
            // vtable.free = ?;
            mem::allocator a;
            a.ptr = this;
            a.vtable = vtable;
            return a;
        }

        optional<u8*> alloc(usize n, mem::alignment alignment, usize ra) {
            return fixed_buffer_allocator::alloc(this, n, alignment, ra);
        }

        void reset() {
            end_index = 0;
        }

        usize end_index;
        slice<u8> buffer;
    };
}}

#endif
