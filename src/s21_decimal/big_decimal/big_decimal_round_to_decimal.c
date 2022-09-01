//
// Created by gubankov on 06.08.22.
//
#include <stdio.h>

#include "../../tests/_helpers/_debug.h"
#include "../arithmetic/arithmetic.h"
#include "../binary/binary.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"
#include "big_decimal.h"
/**
 * @brief Функция по возможности округляет big_decimal до decimal.
 *
 * @param in
 * @param res
 * @return
 */
int big_decimal_round_to_decimal(big_decimal in, s21_decimal* res) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    // При умножении кспонента может оказаться выше 28. Соответственно надо пробовать понизить
    if (big_decimal_get_exp(in) > 28) {
        int to_low = big_decimal_get_exp(in) - 28;
        int sign = big_decimal_get_sign(in);
        big_decimal remainder = big_decimal_get_zero();
        big_decimal temp_res1 = big_decimal_get_zero();
        code = big_decimal_div_big_int(big_decimal_set_sign(in, 0),
                                       decimal_to_big_decimal(s21_decimal_get_ten_pow(to_low)), &temp_res1,
                                       &remainder);
        if (code == S21_ARITHMETIC_OK && !big_decimal_is_zero(remainder)) {
            big_decimal temp_res2 = big_decimal_get_zero();
            code = big_decimal_div_big_int(big_decimal_set_sign(in, 0),
                                           decimal_to_big_decimal(s21_decimal_get_ten_pow(to_low - 1)),
                                           &temp_res2, &remainder);
            if (code == S21_ARITHMETIC_OK) {
                // Для вычисления округляемой цифры прид`тся домножить первый результат на 10 и вычесть 'то
                // из второго результата
                big_decimal shifted_one = big_decimal_shift_left(temp_res1, 1);
                big_decimal shifted_three = big_decimal_shift_left(temp_res1, 3);
                big_decimal multied = big_decimal_add_big_int(shifted_one, shifted_three);
                big_decimal digit = big_decimal_add_big_int(temp_res2, big_decimal_set_sign(multied, 1));
                if (digit.parts[0] == 5 &&
                    (!big_decimal_is_zero(remainder) ||
                     (big_decimal_is_zero(remainder) && big_decimal_is_set_bit(temp_res1, 0)))) {
                    temp_res1 = big_decimal_incr(temp_res1);
                } else if (digit.parts[0] > 5) {
                    temp_res1 = big_decimal_incr(temp_res1);
                } else if (big_decimal_is_zero(temp_res1)) {
                    code = S21_ARITHMETIC_SMALL;
                }
                big_decimal_set_exp(&temp_res1, 28);
                temp_res1 = big_decimal_set_sign(temp_res1, sign);
                in = temp_res1;
            }
        }
    }
    // Выясняем на сколько битов надо округлить
    int bits_to_round = big_decimal_get_not_zero_bit(in) - 95;
    if (bits_to_round > 0 && code == S21_ARITHMETIC_OK) {
        // Опытным путём получено, что если поделить это количество на 3 и отбросить остаток,
        // то получим верхний уровень округления в десятичных знаках. Но сначала можно
        // проверить нижний -- возможно впишется в разрядную сетку.
        // Теория проверена на бумаге до bits_to_round < 24
        big_decimal divisor;
        int ten_exp = (bits_to_round - 1) / 3 - 2;
        if (ten_exp < 1) {
            ten_exp = 1;
        } else if (ten_exp > 28) {
            ten_exp = 28;
        }
        divisor = decimal_to_big_decimal(all_ten_pows[ten_exp]);
        // Используем деление нацело с остатком
        big_decimal result = big_decimal_get_zero();
        big_decimal remainder = big_decimal_get_zero();
        // Кажется нужно убрать кспоненту
        big_decimal in_wo_exp = in;
        big_decimal_set_exp(&in_wo_exp, 0);
        big_decimal_div_big_int(in_wo_exp, divisor, &result, &remainder);
        while ((int)big_decimal_get_not_zero_bit(result) - 95 > 0) {
            ten_exp++;
            if (ten_exp > 28) {
                break;
            }
            divisor = decimal_to_big_decimal(all_ten_pows[ten_exp]);
            big_decimal_div_big_int(in_wo_exp, divisor, &result, &remainder);
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
            code = S21_ARITHMETIC_SMALL;
        } else {
            // Теперь, оценив остаток от деления можно провести округление
            // Получить первую округляемую цифру
            big_decimal first = big_decimal_get_zero();
            big_decimal tmp_remainder = big_decimal_get_zero();
            divisor = decimal_to_big_decimal(all_ten_pows[ten_exp - 1]);
            big_decimal_div_big_int(remainder, divisor, &first, &tmp_remainder);
            if (first.parts[0] > 5 || (first.parts[0] == 5 && (!big_decimal_is_zero(tmp_remainder) ||
                                                               big_decimal_is_set_bit(result, 0)))) {
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
