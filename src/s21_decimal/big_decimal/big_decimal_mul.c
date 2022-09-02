/**
 * @file big_decimal_mul.c
 * @brief Умножение больших чисел
 * @author Dmitriy Gubankov
 * @version 0.1
 * @date 2022-08-18
 */

#include "../arithmetic/arithmetic.h"
#include "big_decimal.h"

int big_decimal_mul(big_decimal first, big_decimal second,
                    big_decimal* result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;
  code = big_decimal_mul_big_int(first, second, result);
  return code;
}
