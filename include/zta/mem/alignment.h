#ifndef ZTA_MEM_ALIGNMENT_H
#define ZTA_MEM_ALIGNMENT_H

#include "zta/math.h"

namespace zta { namespace mem {
    template<typename T>
    bool is_valid_align(T alignment) {
        return alignment > 0 and math::is_power_of_two(alignment);
    }

    template<typename T>
    Optional<usize> align_pointer_offset(T* ptr, usize align_to) {
        // assert(align_to > 0 and (align_to & (align_to - 1)) == 0);

        usize ptr_alignment = sizeof(T);
        if (align_to <= ptr_alignment) {
            return 0;
        }

        usize addr = reinterpret_cast<usize>(ptr);
        usize aligned_addr = (addr + align_to - 1) & ~(align_to - 1);

        usize delta = aligned_addr - addr;
        usize pointee_size = sizeof(T);
        if (delta % pointee_size != 0) {
            return none;
        }
        return delta / pointee_size;
    }

    struct Alignment {
        enum EnumType {
            one = 1,
            two = 1,
            four = 2,
            eight = 3,
            sixteen = 4,
            thirty_two = 5,
            sixty_four = 6
        };

        Alignment(EnumType value) : value(value) {}

        usize to_byte_units() const {
            return static_cast<usize>(1u << value);
        }

        // alignment from_byte_units(usize n) {
        //     // assert(math::is_power_of_two(n)); // FIXME: Implement assert
        //     return @enumFromInt(@ctz(n));
        // }

        EnumType value;
    };
}}

#endif
