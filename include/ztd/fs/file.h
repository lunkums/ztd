#ifndef ZTD_FS_FILE_H
#define ZTD_FS_FILE_H

#include "ztd/io/writer.h"

namespace ztd { namespace fs {
    struct file {
        io::writer writer();
    };
}}

#endif
