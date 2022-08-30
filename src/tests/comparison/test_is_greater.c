#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

// #define __DEBUG

START_TEST(s21_is_greater_1) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(s21_is_greater_2) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal_set_sign(&value_1, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(s21_is_greater_3) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal_set_sign(&value_2, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(s21_is_greater_4) {
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_decimal_set_sign(&value_2, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  s21_decimal_set_sign(&value_1, 1);
  s21_decimal_set_sign(&value_2, 1);

  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal value_2 = {{0x3E8, 0x0, 0x0, 0x80000000}};
  s21_decimal_set_sign(&value_1, 1);
  s21_decimal_set_sign(&value_2, 1);

  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, S21_COMPARISON_TRUE);
}
END_TEST

Suite * is_greater_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_greater_suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, s21_is_greater_1);
    tcase_add_test(tc_core, s21_is_greater_2);
    tcase_add_test(tc_core, s21_is_greater_3);
    tcase_add_test(tc_core, s21_is_greater_4);
    tcase_add_test(tc_core, s21_is_greater_5);
    tcase_add_test(tc_core, s21_is_greater_6);

    suite_add_tcase(s, tc_core);

    return s;
}
