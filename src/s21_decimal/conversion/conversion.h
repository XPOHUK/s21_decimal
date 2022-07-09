#ifndef SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_
#define SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_

#include "./../types.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);

typedef enum {
    S21_CONVERSION_OK = 0,
    S21_CONVERSION_ERROR = 1
} s21_conversion_result;

#endif  //  SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_
