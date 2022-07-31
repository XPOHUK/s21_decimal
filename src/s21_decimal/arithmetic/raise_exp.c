#include "arithmetic.h"
#include "../mant_ops/mant_ops.h"
#include "../helpers/helpers.h"

/**
 * @brief Функция увеличивает экспоненту аргумента на 1, а мантиссу, соответственно в 10 раз.
 * Т.к. множитель 10 раскладывается на (2^1 + 2^3), имеем m = m * 10 = m * (2^1 + 2^3) = m * 2^1 + m * 2^3
 * Умножение двоичного числа на 2^n можно выполнить бинарным сдвигом влево на n.
 * Умножение мантиссы на 10 это есть сдвиг мантиссы на 3 влево плюс сдвиг мантиссы на 1 влево.
 *
 * 00000011  3
 *
 * 00000110  со сдвигом на 1
 * 00011000  со сдвигом на 3
 *
 * складываем
 *
 * 00000110 +
 * 00011000 =
 * 00011110   30
 *
 * Т.к. оба сдвига могут вызывать переполнение, передаём в функцию сдвига пустой decimal для сохранения переполнений.
 * Сложение сдвигов также может вызвать переполнение, но не больше чем на один порядок. Его тоже сохраняем.
 * Если были переполнения, то суммируем их и записываем по указателю переданному в аргументах
 * Если в вызывающей функции переполнение не представляет интереса, то в аргументах будет передан null, поэтому
 * делаем предварительную проверку.
 * @param decimal
 * @param overflow
 * @return Функция возвращает новый decimal
 * @author Rambton Ovtime (rambtono\@student.21-school.ru)
 */
s21_decimal raise_exp(s21_decimal decimal, s21_decimal* overflow) {
    s21_decimal shift1, shift3, res;
    s21_decimal over1 = s21_decimal_get_zero();
    s21_decimal over3 = s21_decimal_get_zero();
    shift1 = s21_decimal_shift_mant_left(decimal, 1, &over1);
    shift3 = s21_decimal_shift_mant_left(decimal, 3, &over3);
    res = s21_decimal_add_mant(shift1, shift3);
    s21_decimal_set_power(res, s21_decimal_get_power(decimal) + 1);
    int over_res = s21_decimal_get_sign(res);
    if (overflow) {
        *overflow = s21_decimal_add_mant(over1, over3);
        if (over_res)
            *overflow = s21_decimal_add_mant(*overflow, s21_decimal_get_one());
    }
    return res;
}