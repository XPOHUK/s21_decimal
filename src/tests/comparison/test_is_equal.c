#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

START_TEST(s21_is_equal_1) {
    s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x0}};
    s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x0}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(s21_is_equal_2) {
    s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x0}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(s21_is_equal_3) {
    s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x80000000}};
    s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x80000000}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(s21_is_equal_4) {
    s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x80000000}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(s21_is_equal_5) {
    s21_decimal value_1 = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};
    s21_decimal value_2 = {{0xCCCCCCC, 0x0, 0x0, 0x0}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, S21_COMPARISON_FALSE);
}
END_TEST

Suite * is_equal_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_equal_suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, s21_is_equal_1);
    tcase_add_test(tc_core, s21_is_equal_2);
    tcase_add_test(tc_core, s21_is_equal_3);
    tcase_add_test(tc_core, s21_is_equal_4);
    tcase_add_test(tc_core, s21_is_equal_5);

    suite_add_tcase(s, tc_core);

    return s;
}
