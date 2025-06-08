#ifndef ZTA_BUILTIN_H
#define ZTA_BUILTIN_H

#include "zta/types.h"

namespace zta { namespace builtin {
    struct Type {
        struct Int {
            bool is_signed;
            u16 bits;
        };

        Int integer;
    };

    template<typename T>
    Type type_info() {
        Type t;
        t.integer.is_signed = static_cast<T>(-1) < static_cast<T>(0);
        t.integer.bits = sizeof(T) * 8;
        return t;
    }

    template<typename T>
    T div_floor(T numerator, T denominator) {
        if (!type_info<T>().integer.is_signed) {
            return numerator / denominator;
        }

        T quotient = numerator / denominator;
        T remainder = numerator % denominator;

        if (remainder == 0) {
            return quotient;
        }

        bool numerator_negative = numerator < 0;
        bool denominator_negative = denominator < 0;
        bool different_signs = numerator_negative != denominator_negative;

        if (different_signs) {
            return quotient - 1;
        }

        return quotient;
    }

    template<typename T>
    T min(T a, T b) {
        return a < b ? a : b;
    }
}}

#endif
