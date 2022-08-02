#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>

#include "./../s21_decimal.h"
#include "./_helpers/_debug.h"

// Отображение отладочной информации в тестах
// #define __DEBUG 1

Suite *from_int_to_decimal_suite(void);
Suite *from_float_to_decimal_suite(void);

Suite *from_decimal_to_int_suite0(void);
Suite *from_decimal_to_int_suite1(void);
Suite *from_decimal_to_int_suite2(void);
Suite *from_decimal_to_int_suite3(void);

Suite *from_decimal_to_float_suite0(void);
Suite *from_decimal_to_float_suite1(void);
Suite *from_decimal_to_float_suite2(void);
Suite *from_decimal_to_float_suite3(void);
Suite *from_decimal_to_float_suite4(void);
Suite *from_decimal_to_float_suite5(void);
Suite *from_decimal_to_float_suite6(void);
Suite *from_decimal_to_float_suite7(void);
Suite *from_decimal_to_float_suite8(void);

Suite *is_greater_suite(void);
Suite *is_equal_suite(void);

Suite *truncate_suite0(void);
Suite *truncate_suite1(void);
Suite *truncate_suite2(void);

Suite *negate_suite(void);

#define TEST_CONVERSION_OK 0
#define TEST_CONVERSION_ERROR 1

void test_from_int_to_decimal(int number, s21_decimal decimal_check);
void test_from_float_to_decimal(float f);
void test_remove_trailing_zeros(char *str);
void test_from_decimal_to_int(s21_decimal decimal, int check);
void test_from_decimal_to_int_fail(s21_decimal decimal);
void test_from_decimal_to_float(s21_decimal decimal, int check);
void test_from_decimal_to_float_fail(s21_decimal decimal);

typedef union float_cast_test {
    float f;
    struct {
        uint32_t mantisa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    } parts;
    uint32_t bytes;
    int int32_bytes;
} float_cast_test;

#define TEST_OTHER_OK 0
#define TEST_OTHER_ERROR 1

void test_truncate(s21_decimal decimal, s21_decimal decimal_check);

Suite *binary_division_suite1(void);
Suite *binary_division_suite2(void);
Suite *binary_division_suite3(void);
Suite *binary_division_suite4(void);
Suite *binary_division_suite5(void);
Suite *binary_division_suite6(void);

Suite *debug0(void);
Suite *debug1(void);
Suite *debug2(void);
Suite *debug3(void);

void test_binary_division(s21_decimal dividend, s21_decimal divisor, s21_decimal quotient,
                          s21_decimal remainder);
void test_debug(s21_decimal decimal, char *check);

// Количество случайных тестов одного типа
#define NUM_RANDOM_TEST 25

double s21_random_double(double min, double max);
int s21_random_int(int min, int max);

#endif  // SRC_TESTS_TEST_H_
