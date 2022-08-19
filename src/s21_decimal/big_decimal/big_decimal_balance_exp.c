/**
 * @file big_decimal_balance_exp.c
 * @brief 
 * @author Dmitriy Gubankov
 * @version 0.1
 * @date 2022-08-16
 */
#include <stddef.h>
#include <stdio.h>

#include "big_decimal.h"
#include "../../tests/_helpers/_debug.h"

/**
 * @brief Функция выравнивания экспонент. Принимает на входе два указателя на big_decimal экспоненты которых
 * надо выровнять. Выравнивание производится домножением мантиссы на 10 и увеличением экспоненты на 1 для числа
 * с меньшей экспонентой. Операция производится до тех пор пока экспоненты обоих чисел не сравняются.
 * Подразумевается, что корректные s21_decimal конвертируются в big_decimal и подаются на вход функции. В данном
 * случае, теоретически, переполнения big_decimal при умножении произойти не должно.
 *
 * @param first
 * @param second
 */
void big_decimal_balance_exp(big_decimal* first, big_decimal* second) {
    big_decimal* to_balance = NULL;
    // printf("args in balance: \n");
    // s21_print_big_decimal_bits(*first);
    // s21_print_big_decimal_bits(*second);
    int diff = big_decimal_get_exp(*first) - big_decimal_get_exp(*second);
    // printf("diff exp = %d\n", diff);
    if (diff > 0) {
        to_balance = second;
    } else if (diff < 0) {
        to_balance = first;
        diff *= -1;
    }
    if (to_balance) {
        int sign = big_decimal_get_sign(*to_balance);
        *to_balance = big_decimal_set_sign(*to_balance, 0);
        for (int i = 0; i < diff; i++) {
            big_decimal shifted_one = big_decimal_shift_left(*to_balance, 1);
            big_decimal shifted_three = big_decimal_shift_left(*to_balance, 3);
            *to_balance = big_decimal_add_big_int(shifted_one, shifted_three);
        }
        big_decimal_set_exp(to_balance, big_decimal_get_exp(*to_balance) + diff);
        if (sign) {
            *to_balance = big_decimal_set_sign(*to_balance, 1);
        }
    }
}
