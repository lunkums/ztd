#ifndef ZTD_POSIX_H
#define ZTD_POSIX_H

#include "ztd/result.h"

#include <stdlib.h>
#include <time.h>

namespace ztd { namespace posix {
    Result<> getrandom(Slice<u8> buffer) {
        std::srand(time(ZTD_NULL));
        for (usize i = 0; i < buffer.len; ++i) {
            buffer[i] = std::rand() % 256;
        }
        return Ok();
    }
}}

#endif
