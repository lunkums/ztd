#include "ztd/io.h"

#include "ztd/posix.h"

namespace ztd { namespace io {
    posix::fd_t get_std_out_handle() {
        return posix::stdout_fileno;
    }

    fs::File get_std_out() {
        return fs::File(get_std_out_handle());
    }
}}
