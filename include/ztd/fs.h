#ifndef ZTD_FS_H
#define ZTD_FS_H

#include "ztd/io.h"

namespace ztd { namespace io {
    struct generic_writer;
    typedef generic_writer writer;
}}

namespace ztd { namespace fs {
    struct file {
        io::writer writer();
    };
}}

#endif
