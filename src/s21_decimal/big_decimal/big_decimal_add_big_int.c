//
// Created by gubankov on 08.08.22.
//

#include <stdio.h>

#include "../../tests/_helpers/_debug.h"
#include "big_decimal.h"

/**
 * @brief Функция принимает на входе два big_decimal, но экспоненту игнорирует и
 * ни как не обрабатывает. Поэтому фактически это обработка двух больших целых
 * чисел в прямом коде со знаком. Отсюда и название. Возможное переполнение
 * попадает в знаковый бит. Оценивать результат уже в вызывающей функции.
 * @param first -- первое положительное или отрицательное целое в прямом коде
 * @param second -- второе положительное или отрицательное целое в прямом коде
 * @return целое в прямом или доп.коде
 */
big_decimal big_decimal_add_big_int(big_decimal first, big_decimal second) {
  int exp = big_decimal_get_exp(first);
  if (big_decimal_get_sign(first)) {
    first = big_decimal_to_twos_complement(first);
  }
  big_decimal result = first;
  if (big_decimal_get_sign(second))
    second = big_decimal_to_twos_complement(second);
  while (!big_decimal_is_zero(second)) {
    // Получаем carry
    big_decimal carry = big_decimal_and(result, second);
    big_decimal shifted_carry = big_decimal_shift_left(carry, 1);
    result = big_decimal_xor(result, second);
    second = shifted_carry;
    if (big_decimal_is_zero(second)) {
      result = big_decimal_xor(result, second);
    }
  }
  big_decimal_set_exp(&result, exp);
  return result;
}
