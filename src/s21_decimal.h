#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include "./s21_decimal/_debug/_debug.h"
#include "./s21_decimal/binary/binary.h"

int s21_is_correct_decimal(s21_decimal decimal);
int s21_decimal_get_sign(s21_decimal decimal);
int s21_decimal_get_power(s21_decimal decimal);
int s21_decimal_get_empty1(s21_decimal decimal);
int s21_decimal_get_empty2(s21_decimal decimal);

s21_decimal s21_create_matrix_from_array(int data1, int data2, int data3, int data4);
s21_decimal s21_create_matrix_from_data(int sign, int power, int data1, int data2, int data3);

#endif  //  SRC_S21_DECIMAL_H_
