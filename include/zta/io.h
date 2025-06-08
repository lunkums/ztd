#ifndef ZTA_IO_H
#define ZTA_IO_H

#include "zta/fs/file.h"
#include "zta/io/writer.h"

namespace zta { namespace io {
    posix::fd_t get_std_out_handle();

    fs::File get_std_out();

    posix::fd_t get_std_in_handle();

    fs::File get_std_in();
}}

#endif
