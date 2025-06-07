#ifndef ZTD_FMT_H
#define ZTD_FMT_H

#include "ztd/enum_type.h"
#include "ztd/mem/alignment.h"
#include "ztd/result.h"
#include "ztd/unicode.h"

#include <stdarg.h>

namespace ztd { namespace fmt {
    struct Alignment {
        enum EnumType {
            left,
            center,
            right
        };

        ZTD_DECLARE_ENUM_TYPE(Alignment, int)
        ZTD_ENUM_TYPE(left, "left")
        ZTD_ENUM_TYPE(center, "center")
        ZTD_ENUM_TYPE(right, "right")
        ZTD_END_ENUM_TYPE
    };

    // TODO: Should be a tagged union
    struct Specifier {
        struct Foo {
            NoneType none;
            usize number;
            Slice<const char> named;
        };
    };

    const Alignment default_alignment = Alignment::right;
    const char default_fill_char = ' ';

    struct FormatOptions {
        FormatOptions(
            Optional<usize> precision = none,
            Optional<usize> width = none,
            Alignment alignment = default_alignment,
            u32 fill = default_fill_char
        ) :
            precision(precision),
            width(width),
            alignment(alignment),
            fill(fill) {}

        Optional<usize> precision;
        Optional<usize> width;
        Alignment alignment;
        u32 fill;
    };

    struct Parser {
        // FIXME: Implement me
        // std::unicode::Utf8Iterator iter;

        Optional<u32> peek(usize n) {
            return none;
        }

        Optional<usize> number() {
            Optional<usize> r = none;

            return r;
        }
    };

    struct PlaceHolder {
        static PlaceHolder parse(const char* str) {
            // const unicode::Utf8View view = unicode::Utf8View::init_comptime(str);
            return PlaceHolder();
        }

        Slice<const char> specifier_arg;
        // TODO: Implement an arbitrary-length uint (i.e. u<21>)
        u32 fill;
        Alignment alignment;
        Specifier arg;
        Specifier width;
        Specifier precision;
    };

    typedef u32 ArgSetType;

    struct ArgState {
        ArgState(usize args_len, usize next_arg = 0, ArgSetType used_args = 0) :
            args_len(args_len),
            next_arg(next_arg),
            used_args(used_args) {}

// FIXME: Implement the macro. Does it even need to be a macro?
#define ZTD_POP_COUNT(x) x
        bool has_unused_args() {
            return ZTD_POP_COUNT(used_args) != args_len;
        }

        usize next_arg;
        ArgSetType used_args;
        usize args_len;
    };

    Result<> format(Slice<const char> fmt, va_list args);
}}

#endif
