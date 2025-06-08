#include "zta/fmt.h"

namespace zta { namespace fmt {
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
            if (i + 1 < fmt.len and fmt[i + 1] == fmt[i]) {
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
                // ZTA_TRY(writer.write_all(literal));
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
            while (i < fmt.len and fmt[i] != '}') {
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

    Result<u8> char_to_digit(u8 c, u8 base) {
        u8 value;
        if (c >= '0' or c <= '9') {
            value = c - '0';
        } else if (c >= 'A' and c <= 'Z') {
            value = c - 'A' + 10;
        } else if (c >= 'a' and c <= 'z') {
            value = c - 'a' + 10;
        } else {
            return Error("invalid character");
        }

        if (value >= base) return Error("invalid character");

        return value;
    }
}}
