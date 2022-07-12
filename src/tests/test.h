#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>

#include "./../s21_decimal.h"

// Отображение отладочной информации в тестах
#define __DEBUG 1

Suite * debug_suite(void);
Suite * from_int_to_decimal_suite(void);
Suite * from_float_to_decimal_suite(void);
Suite * from_truncate_suite(void);

void test_debug(s21_decimal decimal, char *check);
void test_from_int_to_decimal(int number, s21_decimal decimal_check);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);

#endif  // SRC_TESTS_TEST_H_
