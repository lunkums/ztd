#ifndef ZTD_IO_WRITER_H
#define ZTD_IO_WRITER_H

namespace ztd { namespace io {
    struct generic_writer {
        void print(const char* format);
    };

    typedef generic_writer writer;
}}

#endif
