#include "./../big_decimal/big_decimal.h"
#include "./comparison.h"
/**
 * @file is_equal.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Возвращает значение, определяющее, равны ли два значения Decimal.
 * Сравниваются младшие, средние, старшие и служебные биты двух значений Decimal.
 * @param value_1 Первое сравниваемое значение.
 * @param value_2 Второе сравниваемое значение.
 * @return Код возврата:
 *         0 - FALSE
 *         1 - TRUE
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;
    big_decimal big_decimal_1 = decimal_to_big_decimal(value_1);
    big_decimal big_decimal_2 = decimal_to_big_decimal(value_2);

    if (big_decimal_get_exp(big_decimal_1) != big_decimal_get_exp(big_decimal_2)) {
        big_decimal_balance_exp(&big_decimal_1, &big_decimal_2);
    }

    if (big_decimal_1.parts[0] == big_decimal_2.parts[0] &&
        big_decimal_1.parts[1] == big_decimal_2.parts[1] &&
        big_decimal_1.parts[2] == big_decimal_2.parts[2] &&
        big_decimal_1.parts[3] == big_decimal_2.parts[3] &&
        big_decimal_1.parts[4] == big_decimal_2.parts[4] &&
        big_decimal_1.parts[5] == big_decimal_2.parts[5] &&
        big_decimal_1.parts[6] == big_decimal_2.parts[6]) {
        code = S21_COMPARISON_TRUE;
    }
    return code;
}
