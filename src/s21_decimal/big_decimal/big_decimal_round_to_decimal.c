//
// Created by gubankov on 06.08.22.
//
#include "big_decimal.h"
#include "../binary/binary.h"
#include "../mant_ops/mant_ops.h"
#include "../helpers/helpers.h"
#include "../arithmetic/arithmetic.h"

/**
 * @brief Функция по возможности округляет big_decimal до decimal.
 *
 * @param in
 * @param res
 * @return
 */
int big_decimal_round_to_decimal(big_decimal in, s21_decimal* res) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    // Выясняем на сколько битов надо округлить
    int bits_to_round = s21_decimal_get_not_zero_bit(in.over);
    // Опытным путём получено, что если поделить это количество на 3 и отбросить остаток, то получим верхний уровень
    // округления в десятичных знаках. Но сначала можно проверить нижний -- возможно впишется в разрядную сетку.
    // Теория проверена на бумаге до bits_to_round < 24
    big_decimal divisor = big_decimal_get_zero();
    int ten_exp = bits_to_round / 3 - 1;
    divisor.low = *(all_ten_pows[ten_exp]);
    // Используем деление нацело с остатком
    big_decimal result = big_decimal_get_zero();
    big_decimal remainder = big_decimal_get_zero();
    big_decimal_div(in, divisor, &result, &remainder);
    if (!s21_decimal_mant_is_zero(result.over)) {
        ten_exp++;
        divisor.low = all_ten_pows[ten_exp];
        big_decimal_div(in, divisor, &result, &remainder);
    }

    if (big_decimal_get_exp(in) < ten_exp) {
        // Если экспонента числа меньше, чем надо округлить, то имеем очень большое число, результат 1
        code = S21_ARITHMETIC_BIG;
    } else if (big_decimal_get_exp(in) - ten_exp > 28) {
        // Если после округления экспонента числа осталась более 28, то имеем очень малое число, результат 2
        // Тут на самом деле не совсем уверен...
        code = S21_ARITHMETIC_SMALL;
    } else {
        // Теперь, оценив остаток от деления можно провести округление
        // Получить первую округляемую цифру
        big_decimal first = big_decimal_get_zero();
        big_decimal tmp_remainder = big_decimal_get_zero();
        divisor.low = *(all_ten_pows[ten_exp - 1]);
        big_decimal_div(remainder, divisor, &first, &tmp_remainder);
        if (first.low.bits[0] > 5 ||
            (first.low.bits[0] == 5 &&
             (!big_decimal_is_zero(tmp_remainder) || big_decimal_is_set_bit(result, 0)))) {
            result = big_decimal_incr(result);
        }
        // Не забыть проставить экспоненту
        big_decimal_set_exp(result, big_decimal_get_exp(result) - ten_exp);
    }
    *res = in.low;
    return code;
}