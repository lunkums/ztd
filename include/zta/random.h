#ifndef ZTA_RANDOM_H
#define ZTA_RANDOM_H

#include "zta/builtin.h"
#include "zta/math.h"

namespace zta {
    struct Random {
        typedef void (*FillFn)(void*, Slice<u8>);

        void* ptr;
        FillFn fill_fn;

        Random(void* ptr, FillFn fill_fn) : ptr(ptr), fill_fn(fill_fn) {}

        static Random init(void* pointer, FillFn fill_fn) {
            return Random(pointer, fill_fn);
        }

        void bytes(Slice<u8> buf) {
            fill_fn(ptr, buf);
        }

        template<typename T>
        T integer() {
            const u16 bits = builtin::type_info<T>().integer.bits;
            // const UnsignedT = std.meta.Int(.unsigned, bits);
            Result<u16> result = math::div_ceil<u16>(bits, 8);
            if (result.is_error()) throw 1;
            const u16 ceil_bytes = *result;

            Array<u8, sizeof(T)> rand_bytes;
            bytes(rand_bytes);

            T value = 0;

            // Convert bytes to integer (little-endian)
            for (u16 i = 0; i < ceil_bytes; ++i) {
                value |= static_cast<T>(rand_bytes[i]) << (i * 8);
            }

            // Mask to ensure we don't exceed the bit width of T
            if (bits < sizeof(T) * 8) {
                T mask = (static_cast<T>(1) << bits) - 1;
                value &= mask;
            }

            return value;
        }

        template<typename T>
        T uint_less_than(T less_than) {
            assert(builtin::type_info<T>().integer.is_signed == false);
            const u16 bits = builtin::type_info<T>().integer.bits;
            assert(0 < less_than);

            // adapted from:
            //   http://www.pcg-random.org/posts/bounded-rands.html
            //   "Lemire's (with an extra tweak from me)"
            T x = integer<T>();
            u64 m = math::mul_wide<T>(x, less_than);
            T l = static_cast<T>(m);
            if (l < less_than) {
                T t = static_cast<T>(0 - less_than);

                if (t >= less_than) {
                    t -= less_than;
                    if (t >= less_than) {
                        t %= less_than;
                    }
                }
                while (l < t) {
                    x = integer<T>();
                    m = math::mul_wide<T>(x, less_than);
                    l = static_cast<T>(m);
                }
            }
            return static_cast<T>(m >> bits);
        }

        template<typename T>
        T uint_at_most(T at_most) {
            assert(builtin::type_info<T>().integer.is_signed == false);
            if (at_most == math::max_int<T>()) {
                // have the full range
                return integer<T>();
            }
            return uint_less_than<T>(at_most + 1);
        }

        template<typename T>
        T int_range_at_most(T at_least, T at_most) {
            assert(at_least <= at_most);
            if (builtin::type_info<T>().integer.is_signed) {
                throw 1;
            } else {
                // The signed implementation would work fine, but we can use stricter arithmetic operators here.
                return at_least + uint_at_most<T>(at_most - at_least);
            }
        }
    };

    namespace rand {
        struct SplitMix64 {
            u64 s;

            static SplitMix64 init(u64 seed) {
                SplitMix64 x;
                x.s = seed;
                return x;
            }

            u64 next() {
                static const u64 increment =
                    (static_cast<u64>(0x9e3779b9) << 32) | static_cast<u64>(0x7f4a7c15);
                static const u64 mult1 =
                    (static_cast<u64>(0xbf58476d) << 32) | static_cast<u64>(0x1ce4e5b9);
                static const u64 mult2 =
                    (static_cast<u64>(0x94d049bb) << 32) | static_cast<u64>(0x133111eb);

                s += increment;

                u64 z = s;
                z = (z ^ (z >> 30)) * mult1;
                z = (z ^ (z >> 27)) * mult2;
                return z ^ (z >> 31);
            }
        };

        struct Xoshiro256 {
            Array<u64, 4> s;

            static Xoshiro256 init(u64 init_s) {
                Xoshiro256 x;
                x.seed(init_s);
                return x;
            }

            Random random() {
                return zta::Random::init(this, &Xoshiro256::fill);
            }

            u64 next() {
                const u64 r = math::rotl(s[0] + s[3], 23) + s[0];

                const u64 t = s[1] << 17;

                s[2] ^= s[0];
                s[3] ^= s[1];
                s[1] ^= s[2];
                s[0] ^= s[3];

                s[2] ^= t;

                s[3] = math::rotl(s[3], 45);

                return r;
            }

            static void fill(void* self, Slice<u8> buf) {
                reinterpret_cast<Xoshiro256*>(self)->fill(buf);
            }

            void fill(Slice<u8> buf) {
                usize i = 0;
                const usize aligned_len = buf.len - (buf.len & 7);

                // Complete 8 byte segments.
                while (i < aligned_len) {
                    u64 n = next();
                    usize j = 0;
                    while (j < 8) {
                        buf[i + j] = static_cast<u8>(n);
                        n >>= 8;
                        j += 1;
                    }
                    i += 8;
                }

                // Remaining. (cuts the stream)
                if (i != buf.len) {
                    u64 n = next();
                    while (i < buf.len) {
                        buf[i] = static_cast<u8>(n);
                        n >>= 8;
                        i += 1;
                    }
                }
            }

            void seed(u64 init_s) {
                // Xoshiro requires 256-bits of seed.
                SplitMix64 gen = SplitMix64::init(init_s);

                s[0] = gen.next();
                s[1] = gen.next();
                s[2] = gen.next();
                s[3] = gen.next();
            }
        };

        typedef rand::Xoshiro256 DefaultPrng;
    }
}

#endif
