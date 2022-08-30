#include "../arithmetic/arithmetic.h"
#include "big_decimal.h"

big_decimal big_decimal_sub(big_decimal minuend, big_decimal subtrahend) {
    big_decimal result;
    if (big_decimal_is_zero(minuend)) {
        if (big_decimal_get_sign(subtrahend)) {
            subtrahend = big_decimal_set_sign(subtrahend, 0);
        } else {
            subtrahend = big_decimal_set_sign(subtrahend, 1);
        }
        result = subtrahend;
    } else if (big_decimal_is_zero(subtrahend)) {
        result = minuend;
    } else {
        if (big_decimal_get_sign(subtrahend)) {
            subtrahend = big_decimal_set_sign(subtrahend, 0);
        } else {
            subtrahend = big_decimal_set_sign(subtrahend, 1);
        }
        result = big_decimal_add(minuend, subtrahend);
    }
    return result;
}
