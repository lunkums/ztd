#include "ztd/debug.h"

#include <stdarg.h>
#include <stdio.h>

namespace ztd { namespace debug {
    void print(const char* fmt, ...) {
        // FIXME: This should implement Zig-style format printing, not C-style
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }
}}
