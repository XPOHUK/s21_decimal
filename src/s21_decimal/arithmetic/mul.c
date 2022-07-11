#include "./../types.h"
#include "./arithmetic.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    result->bits[0] = value_1.bits[0] + value_2.bits[0];
    return code;
}
