#ifndef ZTD_IO_WRITER_H
#define ZTD_IO_WRITER_H

#include "ztd/result.h"

namespace ztd { namespace io {
    struct generic_writer {
        result<usize> write(slice<const char> bytes);

        result<> write_all(slice<const char> format);

        result<> print(slice<const char> format, ...);

        void* const context;
        result<usize> (*const write_fn)(void* const context, slice<const char> bytes);
    };

    typedef generic_writer writer;
}}

#endif
