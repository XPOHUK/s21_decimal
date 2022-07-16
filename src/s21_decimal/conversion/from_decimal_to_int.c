#include <stdio.h>
#include <math.h>
#include "../../s21_decimal.h"
#include "../_debug/_debug.h"
#include "../binary/binary.h"

/**
 * @brief брифы никому не нужны
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src 
 * @param dst 
 * @return int 
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;

    if (!dst || !s21_is_correct_decimal(src)) {
        code = S21_CONVERSION_ERROR;
    } else {
        s21_decimal truncated_decimal = s21_decimal_get_zero();
        s21_other_result code_truncate = s21_truncate(src, &truncated_decimal);

        if (code_truncate == S21_OTHER_OK) {
            // TODO(hubertfu): допилить как функции будут
            /*тут должно быть сравнение с s21_decimal_get_int_max() и s21_decimal_get_int_max()
                но функций сравнения нет
                наверное надо подумать про +1 или про выполнение truncate до проверки
            */

            /**
             * самый простой способ:
             * *dst = truncated_decimal.bits[0];
             * а потом определить знак путем анализа исходного decimal
             * но это работает только для целочисленных типов размера 32бит и менее
             * ниже универсальный способ, который подойдет и для long, например
             */
            *dst = 0;
            for (int i = 0; i < MAX_BLOCK_NUMBER; i++) {
                if (s21_decimal_is_set_bit(truncated_decimal, i) != 0) {
                    *dst += pow(2, i);
                }
            }

            if (s21_decimal_get_sign(src) == 1 && *dst != -2147483648) {
                *dst = -*dst;
            }

        } else {
            code = S21_CONVERSION_ERROR;
        }
    }

    return code;
}
