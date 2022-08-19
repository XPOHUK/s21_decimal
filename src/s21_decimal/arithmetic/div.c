#include "./arithmetic.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include "../big_decimal/big_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    if (result == NULL || !s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        return -1;
    }
    *result = s21_decimal_get_zero();
    big_decimal val_1_big = decimal_to_big_decimal(value_1);
    big_decimal val_2_big = decimal_to_big_decimal(value_2);
    big_decimal res;
    code = big_decimal_div(val_1_big, val_2_big, &res);
    *result = big_decimal_to_decimal(res);
    return code;
}
