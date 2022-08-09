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
    int bits_to_round = big_decimal_get_not_zero_bit(in) - 95;
    if (bits_to_round > 0) {
        // Опытным путём получено, что если поделить это количество на 3 и отбросить остаток, то получим верхний уровень
        // округления в десятичных знаках. Но сначала можно проверить нижний -- возможно впишется в разрядную сетку.
        // Теория проверена на бумаге до bits_to_round < 24
        big_decimal divisor = big_decimal_get_zero();
        int ten_exp = bits_to_round / 3 - 1;
        divisor = decimal_to_big_decimal(all_ten_pows[ten_exp]);
        // Используем деление нацело с остатком
        big_decimal result = big_decimal_get_zero();
        big_decimal remainder = big_decimal_get_zero();
        big_decimal_div(in, divisor, &result, &remainder);
        // Тут надо переделать например на проверку первого ненулевого бита
        if (big_decimal_get_not_zero_bit(in) - 95 > 0) {
            ten_exp++;
            divisor = decimal_to_big_decimal(all_ten_pows[ten_exp]);
            big_decimal_div(in, divisor, &result, &remainder);
        }

        if (big_decimal_get_exp(in) < ten_exp) {
            // Если экспонента числа меньше, чем надо округлить, то имеем очень большое число, результат 1
            code = S21_ARITHMETIC_BIG;
        } else if (big_decimal_get_exp(in) - ten_exp > 28) {
            // Если после деления экспонента числа осталась более 28, то имеем очень малое число, результат 2
            // Тут на самом деле не совсем уверен...
            code = S21_ARITHMETIC_SMALL;
        } else {
            // Теперь, оценив остаток от деления можно провести округление
            // Получить первую округляемую цифру
            big_decimal first = big_decimal_get_zero();
            big_decimal tmp_remainder = big_decimal_get_zero();
            divisor = decimal_to_big_decimal(all_ten_pows[ten_exp - 1]);
            big_decimal_div(remainder, divisor, &first, &tmp_remainder);
            if (first.parts[0] > 5 ||
                (first.parts[0] == 5 &&
                 (!big_decimal_is_zero(tmp_remainder) || big_decimal_is_set_bit(result, 0)))) {
                result = big_decimal_incr(result);
            }
            // Не забыть проставить экспоненту
            big_decimal_set_exp(&result, big_decimal_get_exp(result) - ten_exp);
        }
        // Конвертировать в decimal
        *res = big_decimal_to_decimal(result);
    }
    return code;
}