#ifndef SRC_S21_DECIMAL_HELPERS_HELPERS_H_
#define SRC_S21_DECIMAL_HELPERS_HELPERS_H_

#include "./../types.h"

int s21_is_correct_decimal(s21_decimal decimal);
int s21_decimal_get_sign(s21_decimal decimal);
int s21_decimal_get_power(s21_decimal decimal);
int s21_decimal_get_empty1(s21_decimal decimal);
int s21_decimal_get_empty2(s21_decimal decimal);
void s21_decimal_set_sign(s21_decimal *decimal, int sign);
void s21_decimal_set_power(s21_decimal *decimal, int power);

s21_decimal s21_create_decimal_from_array(int data1, int data2, int data3, int data4);
s21_decimal s21_create_decimal_from_data(int sign, int power, int data1, int data2, int data3);
s21_decimal s21_create_decimal_from_strings(char *str1, char *str2, char *str3, char *str4);
int s21_decimal_set_bits_from_string(int *bits, char *str);
void s21_clear_decimal(s21_decimal *decimal);
s21_decimal s21_decimal_get_one(void);
s21_decimal s21_decimal_get_zero(void);

#endif  //  SRC_S21_DECIMAL_HELPERS_HELPERS_H_
