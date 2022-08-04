//
// Created by gubankov on 30.07.22.
//
#include "./mant_ops.h"
#include "../helpers/helpers.h"
#include "../../tests/_helpers/_debug.h"
#include <stdio.h>

/**
 * @brief Функция складывает мантиссы двух decimal с учётом знака.
 * @param a Первое слагаемое
 * @param b Второе слагаемое
 * @return Новый decimal. В случае переполнения у результата будет неправильный? знак
 * @author Rambton Ovtime (rambtono@student.21-school.ru)
 */
s21_decimal s21_decimal_add_mant(s21_decimal a, s21_decimal b) {
    fprintf(stdout, "tut21\n");
    fprintf(stdout, "tut22\n");
    fprintf(stdout, "A, B and sum res in bits:\n");
    s21_decimal res = s21_decimal_get_zero();
    int carry = 0;
    s21_print_decimal_bits(a);
    s21_print_decimal_bits(b);
    for (int i = 0; i < 96; i++) {
        int a_bit = s21_decimal_is_set_bit(a, i);
        int b_bit = s21_decimal_is_set_bit(b, i);
        if (a_bit ^ b_bit ^ carry)
            res = s21_decimal_set_bit(res, i);
        carry = ((a_bit & b_bit) | (a_bit & carry) | (b_bit & carry));
    }
    if (carry ^ s21_decimal_get_sign(a) ^ s21_decimal_get_sign(b)) {
        res = s21_decimal_set_bit(res, 127);
    }
    s21_print_decimal_bits(res);
    return res;
}