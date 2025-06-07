#include "ztd/unicode.h"

namespace ztd { namespace unicode {
    Result<u3> utf8_byte_sequence_length(u8 first_byte) {
        // The switch is optimized much better than a "smart" approach using @clz

        if (first_byte <= 0x7F) return 1; // 0b0111_1111
        if (first_byte >= 0xC0 && first_byte <= 0xDF) return 2; // 0b1100_0000 to 0b1101_1111
        if (first_byte >= 0xE0 && first_byte <= 0xEF) return 3; // 0b1110_0000 to 0b1110_1111
        if (first_byte >= 0xF0 && first_byte <= 0xF7) return 4; // 0b1111_0000 to 0b1111_0111

        return Error("invalid UTF-8 start byte");
    }

    /// Deprecated. This function has an awkward API that is too easy to use incorrectly.
    Result<u21> utf8_decode(Slice<const char> bytes) {
        switch (bytes.len) {
            case 1:
                return bytes[0];
            // case 2:
            //     return utf8_decode2(bytes[0..2].*);
            // case 3:
            //     return utf8_decode3(bytes[0..3].*);
            // case 4:
            //     return utf8_decode3(bytes[0..4].*);
            default:
                //else = > unreachable
                throw 1;
        };
    }

    bool utf8_validate_slice_impl(Slice<const char> input, Surrogates surrogates) {
        Slice<const char> remaining = input;

        // TODO: Implement this
        // if (std.simd.suggestVectorLength(u8)) | chunk_len | {
        //         const Chunk = @Vector(chunk_len, u8);

        //         // Fast path. Check for and skip ASCII characters at the start of the input.
        //         while (remaining.len >= chunk_len) {
        //             const chunk : Chunk = remaining[0..chunk_len].*;
        //             const mask : Chunk = @splat(0x80);
        //             if (@reduce(.Or, chunk & mask == mask)) {
        //                 // found a non ASCII byte
        //                 break;
        //             }
        //             remaining = remaining[chunk_len..];
        //         }
        //     }

        // default lowest and highest continuation byte
        const int lo_cb = 128;
        const int hi_cb = 191;

        const int min_non_ascii_codepoint = 0x80;

        // The first nibble is used to identify the continuation byte range to
        // accept. The second nibble is the size.
        const int xx = 0xF1; // invalid: size 1
        const int as = 0xF0; // ASCII: size 1
        const int s1 = 0x02; // accept 0, size 2
        const int s2 = surrogates == cannot_encode_surrogate_half ? 0x13 : 0x03;
        const int s3 = 0x03; // accept 0, size 3
        const int s4 = surrogates == cannot_encode_surrogate_half ? 0x23 : 0x03;
        const int s5 = 0x34; // accept 3, size 4
        const int s6 = 0x04; // accept 0, size 4
        const int s7 = 0x44; // accept 4, size 4

        // Information about the first byte in a UTF-8 sequence.
        // const first = comptime([_] u8 {
        //     as
        // } * *128)++([_] u8 {
        //     xx
        // } * *64)++ [_] u8 {
        //     xx, xx, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1,
        //         s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s2, s3, s3, s3, s3, s3, s3, s3, s3, s3, s3,
        //         s3, s3, s4, s3, s3, s5, s6, s6, s6, s7, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx,
        // };
        const char* first = 0;

        const usize n = remaining.len;
        usize i = 0;
        while (i < n) {
            const u8 first_byte = remaining[i];
            if (first_byte < min_non_ascii_codepoint) {
                i += 1;
                continue;
            }

            const u8 info = first[first_byte];
            if (info == xx) {
                return false; // Illegal starter byte.
            }

            const u8 size = info & 7;
            if (i + size > n) {
                return false; // Short or invalid.
            }

            // Figure out the acceptable low and high continuation bytes, starting
            // with our defaults.
            u8 accept_lo = lo_cb;
            u8 accept_hi = hi_cb;

            switch (info >> 4) {
                case 4:
                    accept_hi = 0x8F;
                    break;
                case 3:
                    accept_lo = 0x90;
                    break;
                case 2:
                    accept_hi = 0x9F;
                    break;
                case 1:
                    accept_lo = 0xA0;
                    break;
                default:
                case 0:
                    // unreachable
                    break;
            }

            const u8 c1 = remaining[i + 1];
            if (c1 < accept_lo or accept_hi < c1) {
                return false;
            }

            switch (size) {
                case 2:
                    i += 2;
                    break;
                case 3: {
                    const u8 c2 = remaining[i + 2];
                    if (c2 < lo_cb or hi_cb < c2) {
                        return false;
                    }
                    i += 3;
                    break;
                }
                case 4: {
                    const u8 c2 = remaining[i + 2];
                    if (c2 < lo_cb or hi_cb < c2) {
                        return false;
                    }
                    const u8 c3 = remaining[i + 3];
                    if (c3 < lo_cb or hi_cb < c3) {
                        return false;
                    }
                    i += 4;
                    break;
                }
                default:
                    // Unreachable
                    break;
            }
        }

        return true;
    }

    /// Returns true if the input consists entirely of UTF-8 codepoints
    bool utf8_validate_slice(Slice<const char> input) {
        return utf8_validate_slice_impl(input, cannot_encode_surrogate_half);
    }
}}
