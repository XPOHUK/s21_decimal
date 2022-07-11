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
    float f0 = 79228101123500060288156172288.f;
            // 79228162514264337593543950335.f;
            // 79228157791897854723898736640.f;

    // float f0 = 1234567890.0f;
    float f1 = 1234567500.12f;
    float f2 = -10.980355f;
    float f3 = 0.15625f;
    // float f3 = 0.0f;
    // printf("%.50f\n", f1);
    // printf("%.50f\n", f2);
    // printf("%.50f\n", f3);
    s21_decimal decimal0;
    s21_decimal decimal1;
    s21_decimal decimal2;
    s21_decimal decimal3;

    s21_from_float_to_decimal(f0, &decimal0);
    s21_from_float_to_decimal(f1, &decimal1);
    s21_from_float_to_decimal(f2, &decimal2);
    s21_from_float_to_decimal(f3, &decimal3);

    // s21_print_decimal_bits(s21_decimal_get_one());
    // s21_print_decimal_bits(s21_decimal_get_zero());

    /*float f = 79228162514264337593543950335.f;
    float i = 0.f;
    while(1) {
        float fff = f - i;
        if (fff != f) {
            printf("%.80f\n", fff);
            printf("%.80f\n", fff - f);
            printf("%.80f\n", i);
            break;
        }
        i = i + 1000000000000000.0;
        printf("%f\n", i);
    }*/
// 2361188870934356819968.000000
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
