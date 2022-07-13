#include "./binary.h"
#include "./../helpers/helpers.h"

s21_decimal s21_decimal_binary_shift_left(s21_decimal decimal, int shift) {
    s21_decimal result = decimal;
    while (shift > 0) {
        result = s21_decimal_binary_shift_left_one(result);
        --shift;
    }

    return result;
}

s21_decimal s21_decimal_binary_shift_right(s21_decimal decimal, int shift) {
    s21_decimal result = decimal;
    while (shift > 0) {
        result = s21_decimal_binary_shift_right_one(result);
        --shift;
    }

    return result;
}

s21_decimal s21_decimal_binary_shift_left_one(s21_decimal decimal) {
    s21_decimal result = s21_decimal_get_zero();

    int b0 = s21_is_set_bit(decimal.bits[0], MAX_BLOCK_BITS - 1);
    result.bits[0] = decimal.bits[0] << 1;

    int b1 = s21_is_set_bit(decimal.bits[1], MAX_BLOCK_BITS - 1);
    result.bits[1] = decimal.bits[1] << 1;

    int b2 = s21_is_set_bit(decimal.bits[2], MAX_BLOCK_BITS - 1);
    result.bits[2] = decimal.bits[2] << 1;

    result.bits[3] = decimal.bits[3] << 1;

    if (b0) {
        result.bits[1] = s21_set_bit(result.bits[1], 0);
    }

    if (b1) {
        result.bits[2] = s21_set_bit(result.bits[2], 0);
    }

    if (b2) {
        result.bits[3] = s21_set_bit(result.bits[3], 0);
    }

    return result;
}

s21_decimal s21_decimal_binary_shift_right_one(s21_decimal decimal) {
    s21_decimal result = s21_decimal_get_zero();

    int b3 = s21_is_set_bit(decimal.bits[3], 0);
    unsigned int result3 = decimal.bits[3];
    result3 = result3 >> 1;
    result.bits[3] = result3;

    int b2 = s21_is_set_bit(decimal.bits[2], 0);
    unsigned int result2 = decimal.bits[2];
    result2 = result2 >> 1;
    result.bits[2] = result2;

    int b1 = s21_is_set_bit(decimal.bits[1], 0);
    unsigned int result1 = decimal.bits[1];
    result1 = result1 >> 1;
    result.bits[1] = result1;

    unsigned int result0 = decimal.bits[0];
    result0 = result0 >> 1;
    result.bits[0] = result0;

    if (b3) {
        result.bits[2] = s21_set_bit(result.bits[2], MAX_BLOCK_BITS - 1);
    }

    if (b2) {
        result.bits[1] = s21_set_bit(result.bits[1], MAX_BLOCK_BITS - 1);
    }

    if (b1) {
        result.bits[0] = s21_set_bit(result.bits[0], MAX_BLOCK_BITS - 1);
    }

    return result;
}
