#include "./comparison.h"
#include "./../helpers/helpers.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;

    // if (s21_decimal_get_power(value_1) != s21_decimal_get_power(value_2)) {
    //     функция для выравнивания степеней(&value_1, &value_2);
    // }

    if (value_1.bits[0] == value_2.bits[0] &&
        value_1.bits[1] == value_2.bits[1] &&
        value_1.bits[2] == value_2.bits[2] &&
        value_1.bits[3] == value_2.bits[3]) {
        code = S21_COMPARISON_TRUE;
    }
    return code;
}
