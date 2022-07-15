#include "./binary.h"
#include "./../helpers/helpers.h"
#include "./../comparison/comparison.h"
#include "./../_debug/_debug.h"
#include <stdio.h>
#include <stdlib.h>

s21_decimal s21_decimal_binary_addition(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = decimal1;
    s21_decimal tmp = decimal2;

    while (!s21_decimal_binary_equal_zero(tmp)) {
        s21_decimal overflow_bits = s21_decimal_binary_and(result, tmp);
        overflow_bits = s21_decimal_binary_shift_left(overflow_bits, 1);
        result = s21_decimal_binary_xor(result, tmp);
        tmp = overflow_bits;
    }

    return result;
}

s21_decimal s21_decimal_binary_subtraction(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result;
    decimal2 = s21_decimal_binary_not(decimal2);
    decimal2 = s21_decimal_binary_addition(decimal2, s21_decimal_get_one());
    result = s21_decimal_binary_addition(decimal1, decimal2);

    return result;
}

// делимое - dividend
// делитель - divisor
// частное - quotient
// остаток - remainder
// деление двоичных чисел методом без восстановления остатка
s21_decimal s21_decimal_binary_division(s21_decimal decimal1, s21_decimal decimal2, s21_decimal *remainder) {
    s21_decimal result;

    s21_decimal partial_remainder = s21_decimal_get_zero();
    s21_decimal quotient = s21_decimal_get_zero();

    if (s21_decimal_binary_equal_zero(decimal1)) {
        quotient = s21_decimal_get_zero();
        partial_remainder = s21_decimal_get_zero();
    } else if (s21_decimal_binary_compare(decimal1, decimal2) == -1) {
        quotient = s21_decimal_get_zero();
        partial_remainder = decimal1;
    } else {
        int left1 = s21_decimal_get_not_zero_bit(decimal1);
        int left2 = s21_decimal_get_not_zero_bit(decimal2);
        int shift = left1 - left2;

        s21_decimal shifted_divisor = s21_decimal_binary_shift_left(decimal2, shift);
        s21_decimal dividend = decimal1;

        int need_subtraction = 1;

        while (shift >= 0) {
            if (need_subtraction == 1) {
                partial_remainder = s21_decimal_binary_subtraction(dividend, shifted_divisor);
            } else {
                partial_remainder = s21_decimal_binary_addition(dividend, shifted_divisor);
            }

            quotient = s21_decimal_binary_shift_left(quotient, 1);

            if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1) == 0) {
                quotient = s21_decimal_set_bit(quotient, 0);
            }

            dividend = s21_decimal_binary_shift_left(partial_remainder, 1);

            if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1) == 0) {
                need_subtraction = 1;
            } else {
                need_subtraction = 0;
            }
            --shift;
        }

        if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1)) {
            partial_remainder = s21_decimal_binary_addition(partial_remainder, shifted_divisor);
        }

        partial_remainder = s21_decimal_binary_shift_right(partial_remainder, left1 - left2);
    }

    result = quotient;

    if (remainder != NULL) {
        *remainder = partial_remainder;
    }

    return result;
}
