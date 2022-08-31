#include "./comparison.h"
#include "./../binary/binary.h"
#include "./../big_decimal/big_decimal.h"
#include "./../helpers/helpers.h"
/**
 * @file is_greater.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Возвращает значение, позволяющее определить, действительно ли
 * заданное значение типа Decimal больше другого заданного значения типа Decimal.
 * Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.
 * @param value_1 Первое сравниваемое значение.
 * @param value_2 Второе сравниваемое значение.
 * @return Код возврата:
 *         0 - FALSE
 *         1 - TRUE
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;
    big_decimal big_decimal_1 = decimal_to_big_decimal(value_1);
    big_decimal big_decimal_2 = decimal_to_big_decimal(value_2);

    big_decimal_balance_exp(&big_decimal_1, &big_decimal_2);
    if (big_decimal_compare(big_decimal_1, big_decimal_2) == BIG_DECIMAL_COMPARISON_FIRST_GREATER) {
        code = S21_COMPARISON_TRUE;
    }
    return code;
}
