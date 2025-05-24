#ifndef ZTD_IO_WRITER_H
#define ZTD_IO_WRITER_H

#include "ztd/result.h"

namespace ztd { namespace io {
    struct generic_writer {
        result<> print(const char* format, ...);

        result<> write_all(const char* format);
    };

    typedef generic_writer writer;
}}

#endif
