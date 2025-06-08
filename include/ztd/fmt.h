#ifndef ZTD_FMT_H
#define ZTD_FMT_H

#include "ztd/ascii.h"
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

    enum Sign {
        pos,
        neg
    };

    Result<u8> char_to_digit(u8 c, u8 base);

    template<typename T, typename U>
    Result<T> parse_int_with_sign(Slice<const U> buf, u8 base, Sign sign) {
        if (buf.len == 0) return Error("invalid character");

        u8 buf_base = base;
        Slice<const U> buf_start = buf;
        if (base == 0) {
            // Treat is as a decimal number by default.
            buf_base = 10;
            // Detect the base by looking at buf prefix.
            if (buf.len > 2 and buf[0] == '0') {
                Optional<u8> c = math::cast<u8>(buf[1]);
                if (c.has_value()) {
                    switch (ascii::to_lower(*c)) {
                        case 'b':
                            buf_base = 2;
                            buf_start = buf(2);
                            break;
                        case 'o':
                            buf_base = 8;
                            buf_start = buf(2);
                            break;
                        case 'x':
                            buf_base = 16;
                            buf_start = buf(2);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        Result<T> (*add)(T, T) = (sign == pos) ? &math::add<T> : &math::sub<T>;

        T accumulate = 0;

        if (buf_start[0] == '_' or buf_start[buf_start.len - 1] == '_')
            return Error("invalid character");

        for (usize i = 0; i < buf_start.len; ++i) {
            U c = buf_start[i];
            if (c == '_') continue;
            Optional<u8> casted_c = math::cast<u8>(c);
            if (!casted_c.has_value()) return Error("invalid character");
            Result<u8> digit_result = char_to_digit(*casted_c, buf_base);
            if (digit_result.is_error()) return Error("invalid character");
            if (accumulate != 0) {
                Optional<T> casted_buf_base = math::cast<T>(buf_base);
                if (!casted_buf_base.has_value()) return Error("overflow");
                Result<T> mul_result = math::mul<T>(accumulate, *casted_buf_base);
                if (mul_result.is_error()) return mul_result.error();
                accumulate = *mul_result;
            } else if (sign == neg) {
                // The first digit of a negative number.
                // Consider parsing "-4" as an i3.
                // This should work, but positive 4 overflows i3, so we can't cast the digit to T and subtract.
                Optional<T> casted_digit = math::cast<T>(-static_cast<i8>(*digit_result));
                if (!casted_digit.has_value()) return Error("overflow");
                accumulate = *casted_digit;
                continue;
            }
            Optional<T> casted_digit = math::cast<T>(*digit_result);
            if (!casted_digit.has_value()) return Error("overflow");
            Result<T> add_result = add(accumulate, *casted_digit);
            if (add_result.is_error()) return add_result.error();
            accumulate = *add_result;
        }

        return accumulate;
    }

    template<typename T, typename U>
    Result<T> parse_int_with_generic_character(Slice<const U> buf, u8 base) {
        if (buf.len == 0) return Error("invalid character");
        if (buf[0] == '+') return parse_int_with_sign<T, U>(buf(1), base, pos);
        if (buf[0] == '-') return parse_int_with_sign<T, U>(buf(1), base, neg);
        return parse_int_with_sign<T, U>(buf, base, pos);
    }

    template<typename T>
    Result<T> parse_int(Slice<const u8> buf, u8 base) {
        return parse_int_with_generic_character<T, u8>(buf, base);
    }
}}

#endif
