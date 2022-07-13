#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_truncate_fail1) {
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на корректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_truncate_ok1) {
    // 1234567890.0123456789
    s21_decimal decimal = {{0xA8E4D515, 0xAB54A98C, 0x0, 0xA0000}};
    // 1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

Suite * from_truncate_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, from_truncate_fail1);

    tcase_add_test(tc_core, from_truncate_ok1);

    suite_add_tcase(s, tc_core);

    return s;
}

void test_truncate(s21_decimal decimal, s21_decimal decimal_check) {
    s21_decimal result;

    #if defined(__DEBUG)
    // s21_print_decimal_bits(decimal);
    // s21_print_decimal_bits(decimal_check);
    #endif

    int res = s21_truncate(decimal, &result);

    #if defined(__DEBUG)
    // s21_print_decimal_bits(result);
    #endif

    ck_assert_int_eq(res, S21_OTHER_OK);
    ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
    ck_assert_int_eq(s21_decimal_get_sign(result), s21_decimal_get_sign(decimal_check));
}