#include "../../s21_decimal.h"

/**
 * @brief конвертирует int src в decimal dst
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый int
 * @param dst указатель на decimal, в который будет записан результат конвертации
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации 
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    s21_conversion_result result = S21_CONVERSION_OK;
    if (!dst) {
        result = S21_CONVERSION_ERROR;
    } else {
        s21_clear_decimal(dst);

        int sign;
        if (src < 0) {
            sign = 1;
            dst->bits[0] = -src;
        } else {
            sign = 0;
            dst->bits[0] = src;
        }

        s21_decimal_set_sign(dst, sign);
    }

    return result;
}
