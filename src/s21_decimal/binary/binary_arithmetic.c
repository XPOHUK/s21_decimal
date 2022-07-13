#include "./binary.h"
#include "./../helpers/helpers.h"
#include "./../comparison/comparison.h"

s21_decimal s21_decimal_binary_addition(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = decimal1;

    while (!s21_is_equal_full_zero(decimal2)) {
        // printf("\n");
        s21_decimal overflow_bits = s21_decimal_binary_and(result, decimal2);
        // printf("o:");s21_print_decimal_bits(overflow_bits);
        overflow_bits = s21_decimal_binary_shift_left(overflow_bits, 1);
        // printf("o<");s21_print_decimal_bits(overflow_bits);
        // printf("+:");s21_print_decimal_bits(result);
        // printf("+:");s21_print_decimal_bits(decimal2);
        result = s21_decimal_binary_xor(result, decimal2);
        // printf("=:");s21_print_decimal_bits(result);

        decimal2 = overflow_bits;
        // printf("\n");
    }

    return result;
}

s21_decimal s21_decimal_binary_subtraction(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result;
    decimal2 = s21_decimal_binary_not(decimal2);
    // printf("~:");s21_print_decimal_bits(decimal2);
    decimal2 = s21_decimal_binary_addition(decimal2, s21_decimal_get_one());
    // printf("+1");s21_print_decimal_bits(decimal2);

    result = s21_decimal_binary_addition(decimal1, decimal2);
    // int inverse_shifted_b = ~shifted_b;
    // s21_print_bit(inverse_shifted_b, 0); printf("\n");

    // int ones_complement_b = inverse_shifted_b + 1;

    return result;
}

// делимое - dividend
// делитель - divisor
// частное - quotient
// остаток - remainder
// деление двоичных чисел методом без восстановления остатка
s21_decimal s21_decimal_binary_division(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result;

    int left1 = s21_decimal_get_not_zero_bit(decimal1);
    int left2 = s21_decimal_get_not_zero_bit(decimal2);

    // printf("\n{%d}\n", left1);
    // printf("\n{%d}\n", left2);
    // printf("\n{%d}\n", left1 - left2);

    int shift = left1 - left2;

    decimal2 = s21_decimal_binary_shift_left(decimal2, shift);

    // s21_print_decimal_bits(decimal2);

    s21_decimal dividend = decimal1;
    s21_decimal remainder;
    s21_decimal quotient = s21_decimal_get_zero();

    int need_subtraction = 1;

    while (shift >= 0) {
        // printf("\n");
        if (need_subtraction == 1) {
            remainder = s21_decimal_binary_subtraction(dividend, decimal2);
        } else {
            remainder = s21_decimal_binary_addition(dividend, decimal2);
        }

        // printf("re");s21_print_decimal_bits(remainder);

        quotient = s21_decimal_binary_shift_left(quotient, 1);
        // printf("qu");s21_print_decimal_bits(quotient);
        if (s21_decimal_is_set_bit(remainder, MAX_BITS - 1) == 0) {
            quotient = s21_decimal_set_bit(quotient, 0);
            // printf("qu");s21_print_decimal_bits(quotient);
        }

        dividend = s21_decimal_binary_shift_left(remainder, 1);
        // printf("di");s21_print_decimal_bits(dividend);

        if (s21_decimal_is_set_bit(remainder, MAX_BITS - 1) == 0) {
            need_subtraction = 1;
        } else {
            need_subtraction = 0;
        }

        --shift;
        // printf("\n");
    }

    if (s21_decimal_is_set_bit(remainder, MAX_BITS - 1)) {
        remainder = s21_decimal_binary_addition(remainder, decimal2);
    }

    remainder = s21_decimal_binary_shift_right(remainder, left1 - left2);


    // s21_print_bit(ostatok, 0); printf("\n");
    // if (s21_is_set_bit(ostatok, 31)) {
    //     ostatok = ostatok + shifted_b;
    // }
    // s21_print_bit(ostatok, 0); printf("\n");
    // ostatok = ostatok >> k;

    result = quotient;

    // printf("qu");s21_print_decimal_bits(quotient);
    // printf("re");s21_print_decimal_bits(remainder);

    return result;
}
