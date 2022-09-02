#include "../../s21_decimal.h"
/**
 * @file is_not_equal.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Возвращает значение, указывающее,
 * имеют ли два объекта Decimal различные значения.
 * @param value_1 Первое сравниваемое значение.
 * @param value_2 Второе сравниваемое значение.
 * @return Код возврата:
 *         0 - FALSE
 *         1 - TRUE
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_result code = S21_COMPARISON_FALSE;

  if (!s21_is_equal(value_1, value_2)) {
    code = S21_COMPARISON_TRUE;
  }
  return code;
}
