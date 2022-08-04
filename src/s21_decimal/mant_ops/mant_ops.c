/**
* @brief
*/
#include "mant_ops.h"

int s21_decimal_mant_is_zero(s21_decimal decimal) {
    return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0;
}

int s21_decimal_mant_compare(s21_decimal x, s21_decimal y) {
    int res = 0;

    for (int i = MAX_BLOCK_NUMBER - 1; i >= 0; i--) {
        int bit_x = s21_decimal_is_set_bit(x, i);
        int bit_y = s21_decimal_is_set_bit(y, i);

        if (bit_x != bit_y) {
            if (bit_x) {
                res = 1;
            } else {
                res = -1;
            }
            break;
        }
    }
    return res;
}