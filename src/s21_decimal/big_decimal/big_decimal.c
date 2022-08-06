//
// Created by gubankov on 06.08.22.
//

#include "big_decimal.h"
#include "../helpers/helpers.h"
#include "../binary/binary.h"

int big_decimal_is_set_bit(big_decimal in, int index) {
    int result;
    if (index < 96) {
        result = s21_decimal_is_set_bit(in.low, index);
    } else {
        result = s21_decimal_is_set_bit(in.over, index - 96);
    }
    return result;
}

big_decimal big_decimal_set_bit(big_decimal in, int index) {
    if (index < 96) {
        in = s21_decimal_set_bit(in.low, index);
    } else {
        in = s21_decimal_set_bit(in.over, index - 96);
    }
    return in;

}

big_decimal big_decimal_flip_bit(big_decimal in, int index) {
    if (index < 96) {
        s21_decimal bit = s21_decimal_set_bit(s21_decimal_get_zero(), index);
        in.low = s21_decimal_binary_xor(in.low, bit);
    } else {
        s21_decimal bit = s21_decimal_set_bit(s21_decimal_get_zero(), index - 96);
        in.over = s21_decimal_binary_xor(in.over, bit);
    }
    return in;
}

int big_decimal_get_sign(big_decimal in) {
    return s21_decimal_get_sign(in.low);
}

big_decimal big_decimal_set_sign(big_decimal in, int sign) {
    s21_decimal_set_sign(&(in.low), sign);
    return in;
}

big_decimal big_decimal_get_zero(void) {
    big_decimal result;
    result.low = s21_decimal_get_zero();
    result.over = s21_decimal_get_zero();
}

big_decimal big_decimal_to_twos_complement(big_decimal direct_code) {
    big_decimal reverted = big_decimal_not(direct_code);
    return big_decimal_incr(reverted);
}