#ifndef ZTD_IO_H
#define ZTD_IO_H

#include "ztd/fs/file.h"
#include "ztd/io/writer.h"

namespace ztd { namespace io {
    posix::fd_t get_std_out_handle();

    fs::File get_std_out();

    posix::fd_t get_std_in_handle();

    fs::File get_std_in();
}}

#endif
