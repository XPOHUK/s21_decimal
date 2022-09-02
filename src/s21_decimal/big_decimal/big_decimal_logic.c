//
// Created by gubankov on 06.08.22.
//

#include "../binary/binary.h"
#include "big_decimal.h"

/**
 * @brief Функция может использоваться в двух вариантах:
 * 1. Для проверки бита. Если бит N установлен - вернёт 2^N
 * 2. При сложении двух чисел для получения битов carry, т.е. битов переноса.
 * @param first
 * @param second
 * @return
 */
big_decimal big_decimal_and(big_decimal first, big_decimal second) {
  big_decimal result;
  for (int i = 0; i < 7; ++i) {
    result.parts[i] = first.parts[i] & second.parts[i];
  }
  return result;
}

/**
 * @brief Фуккция может использоваться в двух вариантах:
 * 1. Для переворачивания одного бита числа. Тогда мы получаем то же число, но с
 * перевёрнутым битом и с неизменёнными остальными частями
 * 2. При сложении двух чисел. Тогда в экспоненте и знаке мы получаем "мусор".
 * @param first
 * @param second
 * @return
 */
big_decimal big_decimal_xor(big_decimal first, big_decimal second) {
  big_decimal result;
  for (int i = 0; i < 7; ++i) {
    result.parts[i] = first.parts[i] ^ second.parts[i];
  }
  return result;
}

/**
 * @brief Функция переворачивает ВСЕ биты числа
 * @param in
 * @return
 */
big_decimal big_decimal_not(big_decimal in) {
  big_decimal result;
  for (int i = 0; i < 7; ++i) {
    result.parts[i] = ~in.parts[i];
  }
  return result;
}
