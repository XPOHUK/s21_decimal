#include "./../helpers/helpers.h"
#include "./binary.h"

/**
 * @brief Функция бинарного вычитания двоичных чисел.
 *
 * Функция берет двоичное представление всех 128 бит числа decimal1 и вычитает
 * из него двоичное представление всех 128 бит числа decimal2
 *
 * A:   1 0 1 0 0 1 1 1
 * B: - 0 0 0 1 0 0 0 1
 *      ---------------
 * C: = 1 0 0 1 0 1 1 0
 *
 * Вычитание делается через сложение:
 * A - B = A + -B
 *
 * Для этого B необходимо представить в дополнительном коде:
 * 1) Вначале получим обратный код. Для этого просто проинвертируем каждый
 * разряд регистра (заменим 0 на 1, а 1 на 0): B: 0 0 0 1 0 0 0 1 ~B: 1 1 1 0 1
 * 1 1 0 2) Прибавим к числу в обратном коде единицу и получим дополнительный
 * код: ~B:   1 1 1 0 1 1 1 0 ~B+1: 1 1 1 0 1 1 1 1
 *
 * Теперь производим сложение:
 * A:       1 0 1 0 0 1 1 1
 * ~B+1:  + 1 1 1 0 1 1 1 1
 *          ---------------
 * C:     = 1 0 0 1 0 1 1 0
 *
 * Итого разность:
 * 1 0 0 1 0 1 1 0
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal1 Уменьшаемое
 * @param decimal2 Вычитаемое
 * @return s21_decimal Разность чисел decimal1 и decimal2
 */
s21_decimal s21_decimal_binary_subtraction(s21_decimal decimal1,
                                           s21_decimal decimal2) {
  s21_decimal result;
  decimal2 = s21_decimal_binary_not(decimal2);
  decimal2 = s21_decimal_binary_addition(decimal2, s21_decimal_get_one());
  result = s21_decimal_binary_addition(decimal1, decimal2);

  return result;
}
