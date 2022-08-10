#include "./arithmetic.h"
#include "../helpers/helpers.h"
#include "../big_decimal/big_decimal.h"

#include <stddef.h>
/**
 * @brief Функция принимает на входе два числа в формате Decimal и указатель для записи результата
 * Отрицательные числа записаны в прямом коде и в отдельном бите выставлен знак.
 * @param value_1 Первое слагаемое.
 * @param value_2 Второе слагаемое.
 * @param result Указатель для записи суммы.
 * @return Код возврата.
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    s21_decimal res = s21_decimal_get_zero();
    if (s21_decimal_get_sign(value_1)) {
        if (s21_decimal_get_sign(value_2)) {
            s21_decimal_set_sign(&value_1, 0);
            s21_decimal_set_sign(&value_2, 0);
            code = s21_add(value_1, value_2, &res);
            if (code == S21_ARITHMETIC_OK)
        } else {
            code = s21_add(value_2, value_1, &res);
        }
    } else {
        big_decimal big_val1 = decimal_to_big_decimal(value_1);
        big_decimal big_val2 = decimal_to_big_decimal(value_2);
        big_decimal res = big_decimal_add(big_val1, big_val2);
    }
    return code;
}
