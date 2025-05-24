#include "ztd/io/writer.h"

#include <stdio.h>

namespace ztd { namespace io {
    result<> generic_writer::print(const char* format, ...) {
        if (fputs(format, stdout)) {
            return error();
        }
        return ok();
    }

    result<> generic_writer::write_all(const char* format) {
        if (fputs(format, stdout)) {
            return error();
        }
        return ok();
    }
}}
