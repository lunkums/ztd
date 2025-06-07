#ifndef ZTD_IO_WRITER_H
#define ZTD_IO_WRITER_H

#include "ztd/result.h"

namespace ztd { namespace io {
    struct GenericWriter {
        void* const context;
        Result<usize> (*const write_fn)(void* const context, Slice<const char> bytes);

        Result<usize> write(Slice<const char> bytes);

        Result<> write_all(Slice<const char> format);

        Result<> print(Slice<const char> format, ...);
    };

    typedef GenericWriter Writer;
}}

#endif
