#include <stddef.h>
#include <stdio.h>

#include "../../tests/_helpers/_debug.h"
#include "../big_decimal/big_decimal.h"
#include "../helpers/helpers.h"
#include "./arithmetic.h"
/**
 * @brief Функция принимает на входе два числа в формате Decimal и указатель для
 * записи результата Отрицательные числа записаны в прямом коде и в отдельном
 * бите выставлен знак.
 * @param value_1 Первое слагаемое.
 * @param value_2 Второе слагаемое.
 * @param result Указатель для записи суммы.
 * @return Код возврата.
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2) ||
      result == NULL) {
    return -1;
  }
  s21_arithmetic_result code = S21_ARITHMETIC_OK;
  big_decimal big_decimal1 = decimal_to_big_decimal(value_1);
  big_decimal big_decimal2 = decimal_to_big_decimal(value_2);
  big_decimal big_decimal1_abs = big_decimal_set_sign(big_decimal1, 0);
  big_decimal big_decimal2_abs = big_decimal_set_sign(big_decimal2, 0);
  int value_1_sign = s21_decimal_get_sign(value_1);
  int value_2_sign = s21_decimal_get_sign(value_2);
  big_decimal res = big_decimal_add(big_decimal1, big_decimal2);
  int res_sign = big_decimal_get_sign(res);
  // Оценка результата
  // Если знаки аргументов одинаковые
  // но не совпадают со знаком результата
  if (value_1_sign == value_2_sign && !big_decimal_is_zero(res)) {
    if ((!value_1_sign && res_sign) || (value_1_sign && !res_sign)) {
      if (value_1_sign)
        code = S21_ARITHMETIC_SMALL;
      else
        code = S21_ARITHMETIC_BIG;
    }
  } else if (value_1_sign) {  // Если первый аргумент отрицательный
    if (big_decimal_compare(big_decimal2_abs,
                            big_decimal1_abs)) {  // и по модулю меньше второго
      // знак результата должен быть положительный
      if (res_sign) {
        // знак результата отрицательный, неудача
      }
    } else if (big_decimal_compare(big_decimal1_abs,
                                   big_decimal2_abs)) {  // если же больше
      // знак результата должен быть отрицательный
      if (!res_sign) {
        // знак результата положительный, неудача
      }
    } else {  // в этом случае результат должен быть 0
    }
  } else {  // Если второй аргумент отрицательный
    if (big_decimal_compare(big_decimal1_abs,
                            big_decimal2_abs)) {  // и по модулю меньше первого
      // знак результата должен быть положительный
      if (res_sign) {
        // знак результата отрицательный, неудача
      }
    } else if (big_decimal_compare(big_decimal2_abs,
                                   big_decimal1_abs)) {  // если же больше
      // знак результата должен быть отрицательный
      if (!res_sign) {
        // знак результата положительный, неудача
      }
    }
  }
  // Если код результата остался ОК, то можно попробовать округлить до decimal
  if (code == S21_ARITHMETIC_OK && !big_decimal_is_zero(res)) {
    int sign = big_decimal_get_sign(res);
    if (sign) {
      int exp = big_decimal_get_exp(res);
      res = big_decimal_to_twos_complement(res);
      big_decimal_set_exp(&res, exp);
    }
    code = big_decimal_round_to_decimal(res, result);
  } else if (big_decimal_is_zero(res)) {
    *result = s21_decimal_get_zero();
  }
  return code;
}
