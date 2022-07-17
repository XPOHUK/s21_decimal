#ifndef SRC_S21_DECIMAL_COMPARISON_COMPARISON_H_
#define SRC_S21_DECIMAL_COMPARISON_COMPARISON_H_

#include "./../types.h"

int s21_is_less(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_greater(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_not_equal(s21_decimal decimal1, s21_decimal decimal2);

#endif  //  SRC_S21_DECIMAL_COMPARISON_COMPARISON_H_
