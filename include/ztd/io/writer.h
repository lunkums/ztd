#ifndef ZTD_IO_WRITER_H
#define ZTD_IO_WRITER_H

#include "ztd/fmt.h"
#include "ztd/result.h"

#include <stdarg.h>
#include <stdio.h>

namespace ztd { namespace io {
    template<
        typename Context,
        Result<usize> (*const write_fn)(Context context, Slice<const char> bytes)>
    struct GenericWriter {
        Context context;

        GenericWriter(Context context) : context(context) {}

        Result<usize> write(Slice<const char> bytes) {
            return write_fn(context, bytes);
        }

        Result<> write_all(Slice<const char> bytes) {
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

        Result<> print(Slice<const char> format, ...) {
            va_list args;
            va_start(args, format);
            Result<> result = fmt::format(format, args);
            va_end(args);
            return result;
        }
    };
}}

#endif
