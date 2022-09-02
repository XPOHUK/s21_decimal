#include "./../arithmetic/arithmetic.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"
/**
 * @file floor.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Округляет указанное Decimal число до ближайшего целого числа в сторону
 * отрицательной бесконечности.
 * @param value Обрабатываемое значение Decimal.
 * @param result Указатель на значение Decimal, куда запишется результат
 * выполнения функции.
 * @return Код возврата:
 *         0 - OK
 *         1 - Ошибка конвертации
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
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
    int value_sign = s21_decimal_get_sign(value);

    s21_clear_decimal(result);
    if (value_sign) {
      s21_negate(value, &value);
    }
    s21_truncate(value, result);
    if (value_sign && s21_is_not_equal(value, *result)) {
      s21_add(*result, one, result);
    }
    if (value_sign) {
      s21_negate(*result, result);
    }
  }
  return code;
}
