#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_decimal_to_int_fail1) {
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на корректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_decimal_to_int_ok1) {
    s21_decimal decimal = {{8, 0, 0, 0}};
    int check = 8;

    test_from_decimal_to_int(decimal, check);
    

}
END_TEST

Suite * from_decimal_to_int_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_from_decimal_to_int_fail1);

    tcase_add_test(tc_core, test_from_decimal_to_int_ok1);

    suite_add_tcase(s, tc_core);

    return s;
}

void test_from_decimal_to_int(s21_decimal decimal, int check) {
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(result, check);
    ck_assert_int_eq(code, S21_CONVERSION_OK);
}