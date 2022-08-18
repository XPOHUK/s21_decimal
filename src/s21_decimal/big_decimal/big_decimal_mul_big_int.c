//
// Created by gubankov on 08.08.22.
//

#include "big_decimal.h"

/**
 * @brief Целочисленное умножение мантисс (соответственно без учёта экспоненты)
 * @param first
 * @param second
 * @return
 */
int big_decimal_mul_big_int(big_decimal first, big_decimal second, big_decimal* result) {
    big_decimal multipliable;
    big_decimal multiplier;
    big_decimal_set_exp(&multiplier, 0);
    big_decimal_set_exp(&multipliable, 0);
    if (big_decimal_get_not_zero_bit(first) > big_decimal_get_not_zero_bit(second)) {
        multipliable = first;
        multiplier = second;
    } else {
        multipliable = second;
        multiplier = first;
    }
    int sign = big_decimal_get_sign(multipliable) ^ big_decimal_get_sign(multiplier);
    multipliable = big_decimal_set_sign(multipliable, 0);
    multiplier = big_decimal_set_sign(multiplier, 0);
    big_decimal sum = big_decimal_get_zero();
    int count = big_decimal_get_not_zero_bit(multiplier);
    for (register int i = 0; i <= count; i++) {
        if (big_decimal_is_set_bit(multiplier, i)) {
            sum = big_decimal_add_big_int(sum, big_decimal_shift_left(multipliable, i));
        }
    }
    // Если у sum появился знак, значит произошло переполнение.
    return big_decimal_set_sign(sum, sign);
}
