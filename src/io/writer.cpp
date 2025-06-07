#include "ztd/io/writer.h"

#include "ztd/fmt.h"

#include <stdarg.h>
#include <stdio.h>

namespace ztd { namespace io {
    Result<usize> GenericWriter::write(Slice<const char> bytes) {
        return write_fn(context, bytes);
    }

    Result<> GenericWriter::write_all(Slice<const char> bytes) {
        usize index = 0;
        while (index != bytes.len) {
            Result<usize> result = write(bytes(index));
            if (result.is_error()) {
                return result.error();
            }
            index += *result;
        }
        return Ok();
    }

    Result<> GenericWriter::print(Slice<const char> format, ...) {
        va_list args;
        va_start(args, format);
        Result<> result = fmt::format(format, args);
        va_end(args);
        return result;
    }
}}
