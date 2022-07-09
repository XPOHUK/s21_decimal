#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>

#include "./../s21_decimal.h"

// Отображение отладочной информации в тестах
#define __DEBUG 1

Suite * debug_suite(void);
Suite * from_int_to_decimal_suite(void);
Suite * from_float_to_decimal_suite(void);

void test_debug(s21_decimal decimal, char *check);

#endif  // SRC_TESTS_TEST_H_
