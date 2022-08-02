#include "./../helpers/helpers.h"
#include "./other.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    if (!result) {
        code = S21_OTHER_ERROR;
    } else if (!s21_is_correct_decimal(value)) {
        code = S21_OTHER_ERROR;
        *result = s21_decimal_get_zero();
    } else {
        for (int i = 0; i < 4; i++) {
            result->bits[i] = value.bits[i];
        }
        s21_decimal_set_sign(result, !s21_decimal_get_sign(value));
    }
    return code;
}
