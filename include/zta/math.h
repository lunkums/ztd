#ifndef ZTA_MATH_H
#define ZTA_MATH_H

#include "zta/builtin.h"
#include "zta/result.h"

namespace zta { namespace math {
    const double e = 2.71828182845904523536028747135266249775724709369995;
    const double pi = 3.14159265358979323846264338327950288419716939937510;
    const double phi = 1.6180339887498948482045868343656381177203091798057628621;
    const double tau = 2 * pi;

    const double log2e = 1.442695040888963407359924681001892137;
    const double log10e = 0.434294481903251827651128918916605082;
    const double ln2 = 0.693147180559945309417232121458176568;
    const double ln10 = 2.302585092994045684017991454684364208;

    const double two_sqrtpi = 1.128379167095512573896158903121545172;
    const double sqrt2 = 1.414213562373095048801688724209698079;
    const double sqrt1_2 = 0.707106781186547524400844362104849039;

    const double rad_per_deg = 0.0174532925199432957692369076848861271344287188854172545609719144;
    const double deg_per_rad = 57.295779513082320876798154814105170332405472466564321549160243861;

    template<typename T>
    bool is_power_of_two(T n) {
        assert(n > 0);
        return (n & (n - 1)) == 0;
    }

    template<typename T>
    T max_int() {
        if (builtin::type_info<T>().integer.is_signed) {
            return static_cast<T>(~(static_cast<T>(1) << (sizeof(T) * 8 - 1)));
        } else {
            return ~static_cast<T>(0);
        }
    }

    template<typename T>
    T min_int() {
        builtin::Type info = builtin::type_info<T>();
        u16 bit_count = info.integer.bits;
        if (!info.integer.is_signed) return 0;
        if (bit_count == 0) return 0;
        return -(static_cast<T>(1) << (bit_count - 1));
    }

    template<typename T>
    u64 mul_wide(T a, T b) {
        // TODO: Impelement me to return an int of exactly twice the capacity
        return static_cast<u64>(a) * b;
    }

    /// Returns the product of a and b. Returns an error on overflow.
    template<typename T>
    Result<T> mul(T a, T b) {
        T x = a * b;
        if (a != 0 and x / a != b) {
            return Error("overflow");
        }
        return x;
    }

    /// Returns the sum of a and b. Returns an error on overflow.
    template<typename T>
    Result<T> add(T a, T b) {
        if (builtin::type_info<T>().integer.is_signed) {
            if (b > 0 and a > max_int<T>() - b) {
                return Error("overflow");
            }
            if (b < 0 and a < min_int<T>() - b) {
                return Error("overflow");
            }
        } else {
            if (a > max_int<T>() - b) {
                return Error("overflow");
            }
        }
        return a + b;
    }

    /// Returns a - b, or an error on overflow.
    template<typename T>
    Result<T> sub(T a, T b) {
        if (builtin::type_info<T>().integer.is_signed) {
            if (b < 0 and a > max_int<T>() + b) {
                return Error("overflow");
            }
            if (b > 0 and a < min_int<T>() + b) {
                return Error("overflow");
            }
        } else {
            if (a < b) {
                return Error("overflow");
            }
        }

        return a - b;
    }

    template<typename T>
    Result<T> div_ceil(T numerator, T denominator) {
        // TODO: Implement setRuntimeSafety
        //@setRuntimeSafety(false);
        if (denominator == 0) return Error("division by zero");
        if (numerator < 0 and denominator < 0) {
            if (numerator == min_int<T>() and denominator == -1) return Error("overflow");
            return builtin::div_floor<T>(numerator + 1, denominator) + 1;
        }
        if (numerator > 0 and denominator > 0)
            return builtin::div_floor<T>(numerator - 1, denominator) + 1;
        return numerator / denominator;
    }

    template<typename T, typename U>
    T rotl(T x, U r) {
        if (false /*builtin::type_info<T>() ==.vector*/) {
            // const C = @typeInfo(T).vector.child;
            // if (C == u0) return 0;

            // if (@typeInfo(C).int.signedness ==.signed) {
            //     @compileError("cannot rotate signed integers");
            // }
            // const ar : Log2Int(C) = @intCast(@mod(r, @typeInfo(C).int.bits));
            // return (x << @splat(ar)) | (x >> @splat(1 + % ~ar));
        } else if (builtin::type_info<T>().integer.is_signed) {
            // @compileError("cannot rotate signed integer");
            throw 1;
        } else {
            if (builtin::type_info<T>().integer.bits == 0) return 0;

            return (x << r) | (x >> (builtin::type_info<T>().integer.bits - r));
        }
    }

    template<typename T, typename U>
    Optional<T> cast(U x) {
        if ((max_int<U>() > max_int<T>()) and x > max_int<T>()) {
            return none;
        } else if ((min_int<U>() < min_int<T>()) and x < min_int<T>()) {
            return none;
        } else {
            return static_cast<T>(x);
        }
    }
}}

#endif
