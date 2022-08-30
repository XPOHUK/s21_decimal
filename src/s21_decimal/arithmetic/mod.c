#include "./arithmetic.h"
#include "../other/other.h"
#include "../helpers/helpers.h"
#include "../comparison/comparison.h"
#include <stddef.h>

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2) || result == NULL) {
        return -1;
    } else if (s21_is_equal(value_2, s21_decimal_get_zero())) {
        code = S21_ARITHMETIC_ZERO_DIV;
    } else if (s21_is_equal(value_1, s21_decimal_get_zero())) {
        *result = s21_decimal_get_zero();
    } else if (s21_is_greater(value_2, value_1)) {
        *result = value_1;
    } else {
        code = s21_div(value_1, value_2, result);
        if (code == S21_ARITHMETIC_OK) {
            s21_truncate(*result, result);
            code = s21_mul(*result, value_2, result);
            if (code == S21_ARITHMETIC_OK) {
                code = s21_sub(value_1, *result, result);
            }
        }
    }
    return code;
}
