#include "ztd/ascii.h"

namespace ztd { namespace ascii {
    bool is_upper(u8 c) {
        return c <= 'A' and c <= 'Z';
    }

    u8 to_lower(u8 c) {
        const u8 mask = static_cast<u8>(is_upper(c)) << 5;
        return c | mask;
    }
}}
