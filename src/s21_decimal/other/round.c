#include "./../arithmetic/arithmetic.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"
/**
 * @file round.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Округляет Decimal до ближайшего целого числа, используется банковское округление.
 * @param value Обрабатываемое значение Decimal.
 * @param result Указатель на значение Decimal, куда запишется результат выполнения функции.
 * @return Код возврата:
 *         0 - OK
 *         1 - Ошибка конвертации
 */


int s21_round(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    // Если указатель на decimal является NULL.
    if (!result) {
        code = S21_OTHER_ERROR;
        // Проверяем, что value является корректным decimal.
    } else if (!s21_is_correct_decimal(value)) {
        code = S21_OTHER_ERROR;
        *result = s21_decimal_get_zero();
        // В остальных случаях производим округление.
    } else {
        s21_decimal one = s21_decimal_get_one();
        s21_decimal five = s21_decimal_get_five();
        s21_decimal remainder = {0};
        int value_sign = s21_decimal_get_sign(value);

        s21_clear_decimal(result);
        if (value_sign) {
            s21_negate(value, &value);
        }

        s21_truncate(value, result);
        s21_mod(value, one, &remainder);
        s21_decimal_set_power(&five, 1);

        if (s21_is_greater(remainder, five)) {
            s21_add(*result, one, result);
        } else if (s21_is_equal(five, remainder)) {
            if (s21_is_even_or_odd(*result) == 1) {
                s21_add(*result, one, result);
            }
        }
        if (value_sign) {
            s21_negate(*result, result);
        }
    }
    return code;
}
