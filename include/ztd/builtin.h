#ifndef ZTD_BUILTIN_H
#define ZTD_BUILTIN_H

#include "ztd/types.h"

namespace ztd { namespace builtin {
    struct type {
        struct integer {
            bool is_signed;
            u16 bits;
        };

        integer integer;
    };

    template<typename T>
    type type_info() {
        type t;
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
}}

#endif
