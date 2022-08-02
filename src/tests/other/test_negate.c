#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

START_TEST(s21_negate_1) {
    s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
    s21_decimal_set_sign(&value_1, 1);
    s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
    s21_decimal result;
    int return_value = s21_negate(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, S21_OTHER_OK);
}
END_TEST

START_TEST(s21_negate_2) {
    s21_decimal value_1 = {{1, 1, 1, 0}};
    s21_decimal check = {{1, 1, 1, 0x80000000}};
    s21_decimal result;
    int return_value = s21_negate(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, S21_OTHER_OK);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int error = s21_negate(value, NULL);
  ck_assert_int_eq(error, S21_OTHER_ERROR);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal value = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;
  int error = s21_negate(value, &result);
  ck_assert_int_eq(error, S21_OTHER_ERROR);
}
END_TEST

Suite * negate_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("negate_suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, s21_negate_1);
    tcase_add_test(tc_core, s21_negate_2);
    tcase_add_test(tc_core, s21_negate_3);
    tcase_add_test(tc_core, s21_negate_4);

    suite_add_tcase(s, tc_core);

    return s;
}
