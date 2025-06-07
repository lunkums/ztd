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

    Result<> format(Slice<const char> fmt, va_list args) {
        usize i = 0;
        Slice<const char> literal = "";
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

            const PlaceHolder placeholder = PlaceHolder::parse(*fmt(fmt_begin, fmt_end));
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
        return Ok();
    }

}}

#endif
