//
// Created by gubankov on 08.08.22.
//

#include "big_decimal.h"
#include "../arithmetic/arithmetic.h"
#include "../../tests/_helpers/_debug.h"
#include <stdio.h>

/**
 * @brief Целочисленное умножение мантисс (соответственно без учёта экспоненты)
 * @param first
 * @param second
 * @return
 */
int big_decimal_mul_big_int(big_decimal first, big_decimal second, big_decimal* result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    int mul_sign = big_decimal_get_sign(first) ^ big_decimal_get_sign(second);
    big_decimal multipliable = big_decimal_get_zero();
    big_decimal multiplier = big_decimal_get_zero();
    big_decimal_set_exp(&multiplier, 0);
    big_decimal_set_exp(&multipliable, 0);
    if (big_decimal_get_not_zero_bit(first) > big_decimal_get_not_zero_bit(second)) {
        multipliable = first;
        multiplier = second;
    } else {
        multipliable = second;
        multiplier = first;
    }
    // int sign = big_decimal_get_sign(multipliable) ^ big_decimal_get_sign(multiplier);
    multipliable = big_decimal_set_sign(multipliable, 0);
    multiplier = big_decimal_set_sign(multiplier, 0);
    big_decimal sum = big_decimal_get_zero();
    int count = big_decimal_get_not_zero_bit(multiplier);
    for (register int i = 0; i <= count; i++) {
        if (big_decimal_is_set_bit(multiplier, i)) {
            sum = big_decimal_add_big_int(sum, big_decimal_shift_left(multipliable, i));
        }
    }
    // printf("sum after cycle:\n");
    // s21_print_big_decimal_bits(sum);
    // printf("res exp: %d\n", big_decimal_get_exp(first) + big_decimal_get_exp(second));
    // Если у sum появился знак, значит произошло переполнение.
    if (big_decimal_get_sign(sum)) {
        if (mul_sign) {
            code = S21_ARITHMETIC_SMALL;
        } else {
            code = S21_ARITHMETIC_BIG;
        }
    } else {
        sum = big_decimal_set_sign(sum, mul_sign);
    }
    big_decimal_set_exp(&sum, big_decimal_get_exp(first) + big_decimal_get_exp(second));
    *result = sum;
    // printf("code %d\n", code);
    return code;
}
