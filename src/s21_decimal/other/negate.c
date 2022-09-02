#include "./../helpers/helpers.h"
#include "./other.h"
/**
 * @file negate.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Возвращает результат умножения заданного значения Decimal на минус
 * единицу.
 * @param value Обрабатываемое значение Decimal.
 * @param result Указатель на значение Decimal, куда запишется результат
 * выполнения функции.
 * @return Код возврата:
 *         0 - OK
 *         1 - Ошибка конвертации
 */
int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;

  // Если указатель на decimal является NULL.
  if (!result) {
    code = S21_OTHER_ERROR;
    // Проверяем, что value является корректным decimal.
  } else if (!s21_is_correct_decimal(value)) {
    code = S21_OTHER_ERROR;
    *result = s21_decimal_get_zero();
    // В остальных случаях производим конвертацию.
  } else {
    *result = value;
    s21_decimal_set_sign(result, !s21_decimal_get_sign(value));
  }
  return code;
}
