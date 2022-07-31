#include "./arithmetic.h"
#include "../helpers/helpers.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    int exp_diff = s21_decimal_get_power(value_1) - s21_decimal_get_power(value_2);
    s21_decimal balanced_exp1 = s21_decimal_get_zero();
    s21_decimal balanced_exp2 = s21_decimal_get_zero();

    if (exp_diff > 0) {
        raised_exp = value_2;
        for (int i = 0; i < exp_diff; i++)
            raised_exp = raise_exp(raised_exp, &overflow);
    }
    result->bits[0] = value_1.bits[0] + value_2.bits[0];
    return code;
}
