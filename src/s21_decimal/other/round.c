#include "./other.h"
#include "./../arithmetic/arithmetic.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    // Если указатель на decimal является NULL.
    if (!result) {
        code = S21_OTHER_ERROR;
    // Проверяем, что value является корректным decimal.
    } else if (!s21_is_correct_decimal(value)) {
        code = S21_OTHER_ERROR;
        *result = s21_decimal_get_zero();
    // В остальных случаях производим округление.
    } else {
        s21_decimal one = s21_decimal_get_one();
        s21_decimal five = s21_decimal_get_five();
        s21_decimal mod = {0};
        int value_sign = s21_decimal_get_sign(value);

        s21_clear_decimal(result);
        if (value_sign) {
            s21_negate(value, &value);
        }
        s21_truncate(value, result);
        s21_mod(value, one, &mod);
        s21_decimal_set_power(&five, 1);
        if (s21_is_less_or_equal(five, mod)) {
        s21_add(*result, one, result);
        }
        if (value_sign) {
        s21_negate(*result, result);
        }
    }
    return code;
}
