#include "./arithmetic.h"
#include "../other/other.h"
#include "../helpers/helpers.h"
#include "../comparison/comparison.h"
#include <stddef.h>
#include <stdio.h>

#include "../../tests/_helpers/_debug.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    int res_sign = s21_decimal_get_sign(value_1);
    s21_decimal val1mod = value_1;
    s21_decimal val2mod = value_2;
    s21_decimal_set_sign(&val1mod, 0);
    s21_decimal_set_sign(&val2mod, 0);
    if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2) || result == NULL) {
        return -1;
    } else if (s21_is_equal(value_2, s21_decimal_get_zero())) {
        code = S21_ARITHMETIC_ZERO_DIV;
    } else if (s21_is_equal(value_1, s21_decimal_get_zero())) {
        *result = s21_decimal_get_zero();
    } else if (s21_is_greater(val2mod, val1mod)) {
        *result = value_1;
    } else {
        big_decimal res = big_decimal_get_zero();
        big_decimal remainder = big_decimal_get_zero();
        big_decimal dividend = decimal_to_big_decimal(val1mod);
        big_decimal divisor = decimal_to_big_decimal(val2mod);
        code = big_decimal_div_big_int(dividend, divisor, &res, &remainder);
        if (code == S21_ARITHMETIC_OK) {
            int temp_exp = big_decimal_get_exp(dividend) - big_decimal_get_exp(divisor);
            while (temp_exp > 0) {
                big_decimal tmp_rem = big_decimal_get_zero();
                big_decimal_div_big_int(res, decimal_to_big_decimal(s21_decimal_get_ten()), &res, &tmp_rem);
                temp_exp--;
            }
            while (temp_exp < 0) {
                big_decimal_mul(res, decimal_to_big_decimal(s21_decimal_get_ten()), &res);
                big_decimal_mul(remainder, decimal_to_big_decimal(s21_decimal_get_ten()), &remainder);
                big_decimal temp_res = big_decimal_get_zero();
                big_decimal_div_big_int(remainder, divisor, &temp_res, &remainder);
                res = big_decimal_add(res, temp_res);
                temp_exp++;
            }
            code = big_decimal_mul(res, divisor, &res);
            if (code == S21_ARITHMETIC_OK) {
                res = big_decimal_sub(dividend, res);
            }
        }
        if (res_sign) {
            res = big_decimal_set_sign(res, 1);
        }
        *result = big_decimal_to_decimal(res);
    }
    return code;
}
