#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>

#include "./../s21_decimal.h"

// Отображение отладочной информации в тестах
// #define __DEBUG 1

Suite * debug_suite(void);
Suite * from_int_to_decimal_suite(void);
Suite * from_float_to_decimal_suite(void);

Suite * from_decimal_to_int_suite0(void);
Suite * from_decimal_to_int_suite1(void);
Suite * from_decimal_to_int_suite2(void);
Suite * from_decimal_to_int_suite3(void);

Suite * from_truncate_suite(void);

void test_debug(s21_decimal decimal, char *check);
void test_from_int_to_decimal(int number, s21_decimal decimal_check);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);
void test_from_decimal_to_int(s21_decimal decimal, int check);
void test_from_decimal_to_int_fail(s21_decimal decimal);

Suite * binary_division_suite1(void);
Suite * binary_division_suite2(void);
Suite * binary_division_suite3(void);
Suite * binary_division_suite4(void);
Suite * binary_division_suite5(void);
Suite * binary_division_suite6(void);

void test_binary_division(
    s21_decimal dividend, s21_decimal divisor, s21_decimal quotient, s21_decimal remainder);

#endif  // SRC_TESTS_TEST_H_
