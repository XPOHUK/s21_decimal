#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};
  s21_decimal value_2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  s21_decimal_set_sign(&value_1, 1);
  s21_decimal_set_sign(&value_2, 1);

  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, S21_COMPARISON_FALSE);
}
END_TEST

Suite * is_less_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_less_suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, s21_is_less_1);

    suite_add_tcase(s, tc_core);

    return s;
}
