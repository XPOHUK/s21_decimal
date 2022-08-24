//
// Created by gubankov on 06.08.22.
//
#include "big_decimal.h"
#include "../binary/binary.h"
#include "../mant_ops/mant_ops.h"
#include "../helpers/helpers.h"
#include "../arithmetic/arithmetic.h"
#include "../../tests/_helpers/_debug.h"
#include <stdio.h>
/**
 * @brief Функция по возможности округляет big_decimal до decimal.
 *
 * @param in
 * @param res
 * @return
 */
int big_decimal_round_to_decimal(big_decimal in, s21_decimal* res) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    // printf("before round: \n");
    // s21_print_big_decimal_bits(in);
    // Выясняем на сколько битов надо округлить
    int bits_to_round = big_decimal_get_not_zero_bit(in) - 95;
    // printf("bits to round: %d\n", bits_to_round);
    if (bits_to_round > 0) {
        // Опытным путём получено, что если поделить это количество на 3 и отбросить остаток, то получим верхний уровень
        // округления в десятичных знаках. Но сначала можно проверить нижний -- возможно впишется в разрядную сетку.
        // Теория проверена на бумаге до bits_to_round < 24
        big_decimal divisor;
        int ten_exp = (bits_to_round - 1)/ 3 - 2;
        if (ten_exp < 1) {
        ten_exp = 1;
        } else if (ten_exp > 28) {
            ten_exp = 28;
        }
        divisor = decimal_to_big_decimal(all_ten_pows[ten_exp]);
        // printf("divisor:\n");
        // s21_print_big_decimal_bits(divisor);
        // Используем деление нацело с остатком
        big_decimal result = big_decimal_get_zero();
        big_decimal remainder = big_decimal_get_zero();
        // Кажется нужно убрать кспоненту
        big_decimal in_wo_exp = in;
        big_decimal_set_exp(&in_wo_exp, 0);
        big_decimal_div_big_int(in_wo_exp, divisor, &result, &remainder);
        // printf("result: \n");
        // s21_print_big_decimal_bits(result);
        // printf("remainder: \n");
        // s21_print_big_decimal_bits(remainder);
        while ((int)big_decimal_get_not_zero_bit(result) - 95 > 0) {
            ten_exp++;
            divisor = decimal_to_big_decimal(all_ten_pows[ten_exp]);
            // printf("divisor after raise ten exp:\n");
            // s21_print_big_decimal_bits(divisor);
            // result = big_decimal_get_zero();
            // remainder = big_decimal_get_zero();
            big_decimal_div_big_int(in_wo_exp, divisor, &result, &remainder);
            // printf("result after raise ten exp: \n");
            // s21_print_big_decimal_bits(result);
            // printf("remainder after raise ten exp: \n");
            // s21_print_big_decimal_bits(remainder);
        }

        if (big_decimal_get_exp(in) < ten_exp) {
            // Если экспонента числа меньше, чем надо округлить, то имеем очень большое число, результат 1
            if (big_decimal_get_sign(in)) {
                code = S21_ARITHMETIC_SMALL;
            } else {
                code = S21_ARITHMETIC_BIG;
            }
        } else if (big_decimal_get_exp(in) - ten_exp > 28) {
            // Если после деления экспонента числа осталась более 28, то имеем очень малое число, результат 2
            // Тут на самом деле не совсем уверен...
            code = S21_ARITHMETIC_SMALL;
        } else {
            // Теперь, оценив остаток от деления можно провести округление
            // Получить первую округляемую цифру
        // printf("result: \n");
        // s21_print_big_decimal_bits(result);
            big_decimal first = big_decimal_get_zero();
            big_decimal tmp_remainder = big_decimal_get_zero();
            divisor = decimal_to_big_decimal(all_ten_pows[ten_exp - 1]);
            // printf("blia\n");
            // printf("result before round\n");
            // s21_print_big_decimal_bits(result);
            // s21_print_big_decimal_bits(remainder);
            // s21_print_big_decimal_bits(divisor);
            big_decimal_div_big_int(remainder, divisor, &first, &tmp_remainder);
            // printf("first:\n");
            // s21_print_big_decimal_bits(first);
            if (first.parts[0] > 5 ||
                (first.parts[0] == 5 &&
                 (!big_decimal_is_zero(tmp_remainder) || big_decimal_is_set_bit(result, 0)))) {
                result = big_decimal_incr(result);
                // Крайний случай: переполнение decimal при инкременте
                if (big_decimal_is_set_bit(result, 96)) {
                    if (big_decimal_get_sign(in)) {
                        code = S21_ARITHMETIC_SMALL;
                    } else {
                        code = S21_ARITHMETIC_BIG;
                    }
                }
            }
            // Не забыть проставить экспоненту
        // printf("result before set exp: \n");
        // s21_print_big_decimal_bits(result);
            big_decimal_set_exp(&result, big_decimal_get_exp(in) - ten_exp);
        }
        // Конвертировать в decimal
        if (code == S21_ARITHMETIC_OK) {
            *res = big_decimal_to_decimal(result);
        }
    } else {
        *res = big_decimal_to_decimal(in);
    }
    return code;
}
