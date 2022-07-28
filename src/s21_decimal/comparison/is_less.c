#include "./comparison.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;

    if (value_1.bits[0] == value_2.bits[0])
        code = S21_COMPARISON_TRUE;

    return code;
}
