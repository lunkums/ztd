#ifndef ZTD_FS_FILE_H
#define ZTD_FS_FILE_H

#include "ztd/io/writer.h"
#include "ztd/posix.h"

namespace ztd { namespace fs {
    struct File {
        typedef posix::fd_t Handle;

        Handle handle;

        File(Handle handle) : handle(handle) {}

        typedef io::Writer Writer;

        Writer writer();
    };
}}

#endif
