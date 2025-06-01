#ifndef ZTD_FMT_H
#define ZTD_FMT_H

#include "ztd/enum_type.h"
#include "ztd/mem/alignment.h"
#include "ztd/result.h"
#include "ztd/unicode.h"

#include <stdarg.h>

namespace ztd { namespace fmt {
    struct alignment {
        enum enum_type {
            left,
            center,
            right
        };

        ZTD_DECLARE_ENUM_TYPE(alignment, int)
        ZTD_ENUM_TYPE(left, "left")
        ZTD_ENUM_TYPE(center, "center")
        ZTD_ENUM_TYPE(right, "right")
        ZTD_END_ENUM_TYPE
    };

    // TODO: Should be a tagged union
    struct specifier {
        struct foo {
            none_type none;
            usize number;
            slice<const char> named;
        };
    };

    const alignment default_alignment = alignment::right;
    const char default_fill_char = ' ';

    struct format_options {
        format_options(
            optional<usize> precision = none,
            optional<usize> width = none,
            alignment alignment = default_alignment,
            u32 fill = default_fill_char
        ) :
            precision(precision),
            width(width),
            alignment(alignment),
            fill(fill) {}

        optional<usize> precision;
        optional<usize> width;
        alignment alignment;
        u32 fill;
    };

    struct parser {
        // FIXME: Implement me
        // std::unicode::utf8_iterator iter;

        optional<u32> peek(usize n) {
            return none;
        }

        optional<usize> number() {
            optional<usize> r = none;

            return r;
        }
    };

    struct placeholder {
        static placeholder parse(const char* str) {
            // const unicode::utf8_view view = unicode::utf8_view::init_comptime(str);
            return placeholder();
        }

        slice<const char> specifier_arg;
        // TODO: Implement an arbitrary-length uint (i.e. u<21>)
        u32 fill;
        alignment alignment;
        specifier arg;
        specifier width;
        specifier precision;
    };

    typedef u32 arg_set_type;

    struct arg_state {
        arg_state(usize args_len, usize next_arg = 0, arg_set_type used_args = 0) :
            args_len(args_len),
            next_arg(next_arg),
            used_args(used_args) {}

// FIXME: Implement the macro. Does it even need to be a macro?
#define ZTD_POP_COUNT(x) x
        bool has_unused_args() {
            return ZTD_POP_COUNT(used_args) != args_len;
        }

        usize next_arg;
        arg_set_type used_args;
        usize args_len;
    };

    result<> format(slice<const char> fmt, va_list args) {
        usize i = 0;
        slice<const char> literal = "";
        while (true) {
            usize start_index = i;

            while (i < fmt.len) {
                // FIXME: I don't really understand what this is trying to do
                switch (fmt[i]) {
                    case '{':
                    case '}':
                        break;
                    default:
                        break;
                }
                i += 1;
            }

            usize end_index = i;
            bool unescape_brace = false;

            // Handle {{ and }}, those are un-escaped as single braces
            if (i + 1 < fmt.len && fmt[i + 1] == fmt[i]) {
                unescape_brace = true;
                // Make the first brace part of the literal...
                end_index += 1;
                // ...and skip both
                i += 2;
            }

            // FIXME: Translate to C++
            //literal = literal ++ fmt[start_index..end_index];

            // We've already skipped the other brace, restart the loop
            if (unescape_brace) continue;

            // Write out the literal
            if (literal.len != 0) {
                // FIXME: Pass in the writer
                // ZTD_TRY(writer.write_all(literal));
                literal = "";
            }

            if (i >= fmt.len) break;

            if (fmt[i] == '}') {
                // FIXME: Throw compile error
                //@compileError("missing opening {");
            }

            // Get past the {
            // FIXME: Implement comptime assert
            //comptime assert(fmt[i] == '{');
            i += 1;

            usize fmt_begin = i;
            while (i < fmt.len && fmt[i] != '}') {
                i += 1;
            }
            usize fmt_end = i;

            if (i >= fmt.len) {
                // FIXME
                //@compileError("missing closing }");
            }

            // Get past the }
            // FIXME
            //comptime assert(fmt[i] == '}');
            i += 1;

            const placeholder placeholder = placeholder::parse(*fmt(fmt_begin, fmt_end));
            //                 const arg_pos = comptime switch (placeholder.arg) {
            //                     .none = > null, .number = > | pos | pos,
            //                     .named = > |
            //                         arg_name |
            //                         meta.fieldIndex(ArgsType, arg_name) orelse
            //                         @compileError("no argument with name '" ++arg_name++ "'"),
            //                 };

            //                 const width = switch (placeholder.width
            //                 ) {.none = > null,
            //                    .number = > | v | v,
            //                    .named = > |
            //                        arg_name |
            //                        blk:
            //                            {const arg_i = comptime meta.fieldIndex(ArgsType, arg_name) orelse
            //                                           @compileError("no argument with name '" ++arg_name++ "'");
            //                 _ = comptime arg_state.nextArg(arg_i) orelse @compileError("too few arguments");
            //                 break : blk @field(args, arg_name);
            //             }
            //             ,
            //         };

            //         const precision = switch (placeholder.precision
            //         ) {.none = > null,
            //            .number = > | v | v,
            //            .named = > |
            //                arg_name |
            //                blk:
            //                    {const arg_i = comptime meta.fieldIndex(ArgsType, arg_name) orelse
            //                                   @compileError("no argument with name '" ++arg_name++ "'");
            //         _ = comptime arg_state.nextArg(arg_i) orelse @compileError("too few arguments");
            //         break : blk @field(args, arg_name);
            //     }
            //     ,
            // };

            // const arg_to_print = comptime arg_state.nextArg(arg_pos) orelse @compileError("too few arguments");

            // try formatType(
            //     @field(args, fields_info[arg_to_print].name),
            //     placeholder.specifier_arg,
            //     FormatOptions {
            //         .fill = placeholder.fill,
            //         .alignment = placeholder.alignment,
            //         .width = width,
            //         .precision = precision,
            //     },
            //     writer,
            //     std.options.fmt_max_depth,
            // );
        }
        return ok();
    }

}}

#endif
