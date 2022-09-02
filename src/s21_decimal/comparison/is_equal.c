#include "../big_decimal/big_decimal.h"
#include "./../big_decimal/big_decimal.h"
#include "./comparison.h"
/**
 * @file is_equal.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Возвращает значение, определяющее, равны ли два значения Decimal.
 * Сравниваются младшие, средние, старшие и служебные биты двух значений
 * Decimal.
 * @param value_1 Первое сравниваемое значение.
 * @param value_2 Второе сравниваемое значение.
 * @return Код возврата:
 *         0 - FALSE
 *         1 - TRUE
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_result code = S21_COMPARISON_FALSE;

  if (value_1.bits[0] == value_2.bits[0] && value_1.bits[0] == 0 &&
      value_1.bits[1] == value_2.bits[1] && value_1.bits[1] == 0 &&
      value_1.bits[2] == value_2.bits[2] && value_1.bits[2] == 0) {
    code = S21_COMPARISON_TRUE;
  }

  big_decimal value_1_big = decimal_to_big_decimal(value_1);
  big_decimal value_2_big = decimal_to_big_decimal(value_2);
  big_decimal_balance_exp(&value_1_big, &value_2_big);
  value_1 = big_decimal_to_decimal(value_1_big);
  value_2 = big_decimal_to_decimal(value_2_big);

  if (value_1.bits[0] == value_2.bits[0] &&
      value_1.bits[1] == value_2.bits[1] &&
      value_1.bits[2] == value_2.bits[2] &&
      value_1.bits[3] == value_2.bits[3]) {
    code = S21_COMPARISON_TRUE;
  }
  return code;
}
