#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_conversion_result result = S21_CONVERSION_OK;
    if (!dst) {
        result = S21_CONVERSION_ERROR;
    } else {
        int sign;
        if (src < 0) {
            sign = 1;
            dst->bits[0] = -src;
        } else {
            sign = 0;
            dst->bits[0] = src;
        }

        s21_set_sign(dst, sign);
    }

    return result;
}
