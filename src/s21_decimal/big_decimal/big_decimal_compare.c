//
// Created by gubankov on 11.08.22.
//
#include <stdio.h>

#include "big_decimal.h"

// Закомментил строку выравнивания, теперь функция сравнивает только мантиссы
int big_decimal_compare(big_decimal first, big_decimal second) {
    big_decimal_comparison_result result = BIG_DECIMAL_COMPARISON_EQUAL;
    int first_sign = big_decimal_get_sign(first);
    int second_sign = big_decimal_get_sign(second);
    if (big_decimal_is_zero(first) && big_decimal_is_zero(second)) {
    } else if (first_sign && !second_sign) {
        result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
    } else if (!first_sign && second_sign) {
        result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
    } else {
        int first_bit = big_decimal_get_not_zero_bit(first);
        int second_bit = big_decimal_get_not_zero_bit(second);
        if (first_bit > second_bit) {
            result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
        } else if (first_bit < second_bit) {
            result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
        } else {
            for (int i = first_bit; i >= 0; i--) {
                if (big_decimal_is_set_bit(first, i) == big_decimal_is_set_bit(second, i)) {
                    continue;
                } else if (big_decimal_is_set_bit(first, i)) {
                    result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
                } else {
                    result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
                }
                break;
            }
        }
        if (result != BIG_DECIMAL_COMPARISON_EQUAL) {
            if (first_sign) {
                if (result == BIG_DECIMAL_COMPARISON_FIRST_GREATER)
                    result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
                else
                    result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
            }
        }
    }
    return result;
}
