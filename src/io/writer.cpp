#include "ztd/io/writer.h"

#include "ztd/fmt.h"

#include <stdarg.h>
#include <stdio.h>

namespace ztd { namespace io {
    result<usize> generic_writer::write(slice<const char> bytes) {
        return write_fn(context, bytes);
    }

    result<> generic_writer::write_all(slice<const char> bytes) {
        usize index = 0;
        while (index != bytes.len) {
            result<usize> result = write(bytes(index));
            if (result.is_error()) {
                return result.error();
            }
            index += *result;
        }
        return ok();
    }

    result<> generic_writer::print(slice<const char> format, ...) {
        va_list args;
        va_start(args, format);
        result<> result = fmt::format(format, args);
        va_end(args);
        return result;
    }
}}
