#ifndef SRC_S21_DECIMAL_BINARY_BINARY_H_
#define SRC_S21_DECIMAL_BINARY_BINARY_H_

#include "./../types.h"

int s21_is_set_bit(int number, int index);
int s21_set_bit(int number, int index);
int s21_inverseBit(int number, int index);
int s21_reset_bit(int number, int index);
int s21_decimal_is_set_bit(s21_decimal decimal, int index);
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index);
int s21_decimal_get_not_zero_bit(s21_decimal decimal);

s21_decimal s21_decimal_binary_and(s21_decimal decimal1, s21_decimal decimal2);
s21_decimal s21_decimal_binary_xor(s21_decimal decimal1, s21_decimal decimal2);
s21_decimal s21_decimal_binary_not(s21_decimal decimal);

s21_decimal s21_decimal_binary_addition(s21_decimal decimal1, s21_decimal decimal2);
s21_decimal s21_decimal_binary_subtraction(s21_decimal decimal1, s21_decimal decimal2);
s21_decimal s21_decimal_binary_division(s21_decimal decimal1, s21_decimal decimal2);

s21_decimal s21_decimal_binary_shift_left(s21_decimal decimal, int shift);
s21_decimal s21_decimal_binary_shift_right(s21_decimal decimal, int shift);
s21_decimal s21_decimal_binary_shift_left_one(s21_decimal decimal);
s21_decimal s21_decimal_binary_shift_right_one(s21_decimal decimal);

#endif  //  SRC_S21_DECIMAL_BINARY_BINARY_H_
