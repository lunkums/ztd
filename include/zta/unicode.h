#ifndef ZTA_UNICODE_H
#define ZTA_UNICODE_H

#include "zta/result.h"
#include "zta/types.h"

namespace zta { namespace unicode {
    const u21 replacement_character = 0xFFFD;

    Result<u3> utf8_byte_sequence_length(u8 first_byte);

    /// Deprecated. This function has an awkward API that is too easy to use incorrectly.
    Result<u21> utf8_decode(Slice<const char> bytes);

    enum Surrogates {
        cannot_encode_surrogate_half,
        can_encode_surrogate_half
    };

    bool utf8_validate_slice_impl(Slice<const char> input, Surrogates surrogates);

    /// Returns true if the input consists entirely of UTF-8 codepoints
    bool utf8_validate_slice(Slice<const char> input);

    struct Utf8Iterator {
        Optional<Slice<const char> > next_codepoint_slice() {
            if (i >= bytes.len) {
                return none;
            }

            Result<u3> cp_len = utf8_byte_sequence_length(bytes[i]);
            if (cp_len.is_error()) {
                // unreachable
                throw 1;
            }
            i += *cp_len;
            return bytes(i - *cp_len, i);
        }

        Optional<u21> next_codepoint() {
            Optional<Slice<const char> > slice = next_codepoint_slice();
            if (!slice.has_value()) return none;
            Result<u21> r = utf8_decode(*slice);
            if (r.is_error()) throw 1;
            return *r;
        }

        /// Look ahead at the next n codepoints without advancing the iterator.
        /// If fewer than n codepoints are available, then return the remainder of the string.
        Slice<const char> peek(usize n) {
            usize original_i = i;
            // defer i = original_i;

            usize end_ix = original_i;
            usize found = 0;
            while (found < n) {
                Optional<Slice<const char> > next_codepoint = next_codepoint_slice();
                if (next_codepoint.has_value()) {
                    return bytes(original_i);
                }
                end_ix += (*next_codepoint).len;

                found += 1;
            }

            return bytes(original_i, end_ix);
        }

        Slice<const char> bytes;
        usize i;
    };

    struct Utf8View {
        static Result<Utf8View> init(Slice<const char> s) {
            if (!utf8_validate_slice(s)) {
                return Error("invalid utf8");
            }
            return Utf8View();
        }

        static Utf8View init_comptime(Slice<const char> s) {
            Result<Utf8View> result = init(s);
            if (result.is_error()) {
                throw 1;
            }
            return *result;
        }

        Slice<const char> bytes;
    };
}}

#endif
