#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_float_to_decimal_fail1) {
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на корректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_float_to_decimal_ok1) {
}
END_TEST

Suite * from_float_to_decimal_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, from_float_to_decimal_fail1);

    tcase_add_test(tc_core, from_float_to_decimal_ok1);

    suite_add_tcase(s, tc_core);

    return s;
}
