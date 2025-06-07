#ifndef ZTD_POSIX_H
#define ZTD_POSIX_H

#include <stdlib.h>
#include <time.h>

namespace ztd { namespace posix {
    result<> getrandom(slice<u8> buffer) {
        std::srand(time(ZTD_NULL));
        for (usize i = 0; i < buffer.len; ++i) {
            buffer[i] = std::rand() % 256;
        }
        return ok();
    }
}}

#endif
