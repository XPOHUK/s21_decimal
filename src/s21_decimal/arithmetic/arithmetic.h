#ifndef SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_
#define SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_

#include "../mant_ops/mant_ops.h"
#include "./../types.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int raise_exp(s21_decimal decimal, s21_decimal *result);

/**
 * @brief коды ошибок арифметических операторов
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 */
typedef enum s21_arithmetic_result {
  S21_ARITHMETIC_OK = 0,
  S21_ARITHMETIC_BIG = 1,
  S21_ARITHMETIC_SMALL = 2,
  S21_ARITHMETIC_ZERO_DIV = 3
} s21_arithmetic_result;

#endif  //  SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_
