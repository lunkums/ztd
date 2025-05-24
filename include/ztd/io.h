#ifndef ZTD_IO_H
#define ZTD_IO_H

#include "ztd/fs.h"

// Forward declarations
namespace ztd { namespace fs {
    struct file;
}}

namespace ztd { namespace io {
    fs::file get_std_out();

    struct generic_writer {
        void print(const char* format);
    };

    typedef generic_writer writer;
}}

#endif
