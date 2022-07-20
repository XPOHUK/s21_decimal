#include <stdio.h>
#include <math.h>

#include "./conversion.h"
#include "./../helpers/helpers.h"
#include "./../binary/binary.h"

/**
 * @brief брифы никому не нужны
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src 
 * @param dst 
 * @return int 
 */

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;
    if (!dst || !s21_is_correct_decimal(src)) {
        code = S21_CONVERSION_ERROR;
    } else {
        // TODO(hubertfu): переделать на математику decimal и алгоритм из IEEE 754
        // включая округление
        float tmp = 0.0;

        int sign = s21_decimal_get_sign(src);
        int power = s21_decimal_get_power(src);

        for (int i = 0; i < MAX_BLOCK_NUMBER; i++) {
            if (s21_decimal_is_set_bit(src, i) != 0) {
                tmp += pow(2.0, i);
            }
        }
        // printf("{%f}\n", tmp);

        while (power > 0) {
            tmp /=  10;
            --power;
        }
        // printf("{%f}\n", tmp);

        if (sign) {
            // и пофиг на -0.0
            tmp *= -1.0;
        }
        printf("ld:%f\n", tmp);

        *dst = (float)tmp;
    }

    return code;
}
