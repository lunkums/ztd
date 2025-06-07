#ifndef ZTD_POSIX_H
#define ZTD_POSIX_H

#include "ztd/result.h"
#include "ztd/types.h"

#include <unistd.h>

namespace ztd { namespace posix {
    typedef int fd_t;

    const fd_t stdout_fileno = STDOUT_FILENO;

    Result<> getrandom(Slice<u8> buffer);
}}

#endif
