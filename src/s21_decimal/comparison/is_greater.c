#include "../../s21_decimal.h"
#include "./comparison.h"
#include "../binary/binary.h"
#include "./../helpers/helpers.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;

    int value_1_sign = s21_decimal_get_sign(value_1);
    int value_2_sign = s21_decimal_get_sign(value_2);

    if (value_1_sign > value_2_sign) {
        code = S21_COMPARISON_FALSE;
    } else if (value_1_sign < value_2_sign) {
        code = S21_COMPARISON_TRUE;
    } else if (value_1_sign == value_2_sign) {
        //  функция для выравнивания степеней(&value_1, &value_2);
        for (int i = 95; i >= 0; i--) {
            int value_1_bit = s21_decimal_is_set_bit(value_1, i);
            int value_2_bit = s21_decimal_is_set_bit(value_2, i);

            if (value_1_bit > value_2_bit) {
                code = S21_COMPARISON_TRUE;
                break;
            } else if (value_1_bit < value_2_bit) {
                code = S21_COMPARISON_FALSE;
                break;
            } else if (value_1_bit == value_2_bit) {
                code = S21_COMPARISON_FALSE;
                continue;
            }
        }
    }
    return code;
}
