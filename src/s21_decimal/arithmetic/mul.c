#include "./arithmetic.h"
#include "../helpers/helpers.h"
#include "../comparison/comparison.h"
#include "../big_decimal/big_decimal.h"
#include <stddef.h>

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    if (result == NULL || !s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        return -1;
    } else if (s21_is_equal(value_1, s21_decimal_get_zero()) || s21_is_equal(value_2, s21_decimal_get_zero())) {
        *result = s21_decimal_get_zero();
    } else {
        big_decimal val_1_big = decimal_to_big_decimal(value_1);
        big_decimal val_2_big = decimal_to_big_decimal(value_2);
        big_decimal res = big_decimal_get_zero();
        code = big_decimal_mul(val_1_big, val_2_big, &res);
        if (code == S21_ARITHMETIC_OK) {
            code = big_decimal_round_to_decimal(res, result);
        }
    }
    return code;
}
