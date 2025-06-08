#include "zta/io.h"

#include "zta/posix.h"

namespace zta { namespace io {
    posix::fd_t get_std_out_handle() {
        return posix::stdout_fileno;
    }

    fs::File get_std_out() {
        return fs::File(get_std_out_handle());
    }

    posix::fd_t get_std_in_handle() {
        return posix::stdin_fileno;
    }

    fs::File get_std_in() {
        return fs::File(get_std_in_handle());
    }
}}
