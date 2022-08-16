//
// Created by gubankov on 11.08.22.
//
#include "big_decimal.h"
#include <stdio.h>

int big_decimal_compare(big_decimal first, big_decimal second) {
    printf("in compare");
    big_decimal_comparison_result result;
    big_decimal_balance_exp(&first, &second);
    int first_sign = big_decimal_get_sign(first);
    int second_sign = big_decimal_get_sign(second);
    int first_bit = big_decimal_get_not_zero_bit(first);
    int second_bit = big_decimal_get_not_zero_bit(second);
    if (first_sign == second_sign) {  // Если знаки равны
        if (first_bit == second_bit) {  // И если равны мантиссы
            result = BIG_DECIMAL_COMPARISON_EQUAL;
        } else {  // Если же мантиссы не равны
            if (first_bit > second_bit) {  // Если первая мантисса больше
                if (first_sign)  // И если знаки отрицательные
                    result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
                else  // Если знаки положительные
                    result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
            } else {  // Если же первая мантисса меньше
                if (first_sign)  // И если знаки отрицательные
                    result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
                else
                    result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
            }
        }
    } else if (first_sign != second_sign) {  // Если знаки не равны
        if (first_sign)  // Если первое число отрицательное
            result = BIG_DECIMAL_COMPARISON_SECOND_GREATER;
        else  // Если второе число отрицательное
            result = BIG_DECIMAL_COMPARISON_FIRST_GREATER;
    }
    return result;
}
