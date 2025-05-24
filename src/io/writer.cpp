#include "ztd/io.h"

#include <stdio.h>

namespace ztd { namespace io {
    void generic_writer::print(const char* format) {
        fputs(format, stdout);
    }
}}
