//
// Created by gubankov on 30.07.22.
//
#include "./mant_ops.h"
#include "../helpers/helpers.h"

/**
 * @brief Функция складывает мантиссы двух decimal. Экспонента и знак не учитываются.
 * @param a Первое слагаемое
 * @param b Второе слагаемое
 * @return Новый decimal. В случае переполнения у результата будет отрицательный знак
 * @author Rambton Ovtime (rambtono@student.21-school.ru)
 */
s21_decimal s21_decimal_add_mant(s21_decimal a, s21_decimal b) {
    s21_decimal res = s21_decimal_get_zero();
    int dig = 0;
    for (int i = 0; i < 96; i++) {
        int a_bit = s21_decimal_is_set_bit(a, i);
        int b_bit = s21_decimal_is_set_bit(b, i);
        if (a_bit ^ b_bit ^ dig)
            s21_decimal_set_bit(res, i);
        dig = (a_bit & b_bit || a_bit & dig || b_bit & dig);
    }
    if (dig)
        s21_decimal_set_bit(res, 127);
    return res;
}