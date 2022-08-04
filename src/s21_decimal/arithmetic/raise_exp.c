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
 * Оба сдвига и их последующее сложение могут вызывать переполнение, в этом случае вернуть сигнал об ошибке.
 * @param decimal
 * @param overflow
 * @return Функция возвращает код
 * @author Rambton Ovtime (rambtono\@student.21-school.ru)
 */
int raise_exp(s21_decimal decimal, s21_decimal* result) {
    s21_arithmetic_result code = S21_ARITHMETIC_BIG;
    s21_decimal shift1, shift3, res;
    s21_decimal over1 = s21_decimal_get_zero();
    s21_decimal over3 = s21_decimal_get_zero();
    // Выполняем сдвиг на 1
    shift1 = s21_decimal_shift_mant_left(decimal, 1, &over1);
    // Если переполнения не было, то продолжаем
    if (s21_decimal_mant_is_zero(over1)) {
        // Выполняем сдвиг на 3
        shift3 = s21_decimal_shift_mant_left(decimal, 3, &over3);
        // Если переполнения нет, продолжаем
        if (s21_decimal_mant_is_zero(over3)) {
            // Сложение
            res = s21_decimal_add_mant(shift1, shift3);
            // Если переполнения нет, увеличиваем значение экспонеты и сохраняем результат
            if (s21_decimal_get_sign(decimal) == s21_decimal_get_sign(res)) {
                s21_decimal_set_power(&res, s21_decimal_get_power(decimal) + 1);
                *result = res;
                code = S21_ARITHMETIC_OK;
            }
        }
    }
    return code;
}