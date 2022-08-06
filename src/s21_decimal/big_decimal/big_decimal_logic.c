//
// Created by gubankov on 06.08.22.
//

#include "big_decimal.h"
#include "../binary/binary.h"

/**
 * @brief Функция может использоваться в двух вариантах:
 * 1. Для проверки бита. Если бит N установлен - вернёт 2^N
 * 2. При сложении двух чисел для получения битов carry, т.е. битов переноса.
 * @param first
 * @param second
 * @return
 */
big_decimal big_decimal_and(big_decimal first, big_decimal second) {
    first.low = s21_decimal_binary_and(first.low, second.low);
    first.over = s21_decimal_binary_and(first.over, second.over);
    return first;
}
/**
 * @brief Фуккция может использоваться в двух вариантах:
 * 1. Для переворачивания одного бита числа. Тогда мы получаем то же число, но с перевёрнутым битом и с неизменёнными
 * остальными частями
 * 2. При сложении двух чисел. Тогда в экспоненте и знаке мы получаем "мусор".
 * @param first
 * @param second
 * @return
 */
big_decimal big_decimal_xor(big_decimal first, big_decimal second) {
    first.low = s21_decimal_binary_xor(first.low, second.low);
    first.over = s21_decimal_binary_xor(first.over, second.over);
    return first;
}
/**
 * @brief Функция переворачивает ВСЕ биты числа
 * @param in
 * @return
 */
big_decimal big_decimal_not(big_decimal in) {
    in.low = s21_decimal_binary_not(first.low);
    in.over = s21_decimal_binary_not(in.over);
}