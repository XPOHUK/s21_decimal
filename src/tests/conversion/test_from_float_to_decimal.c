#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./test_from_float_to_decimal.h"
#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на ненормальные float
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_float_to_decimal_unnormal1) {
    float f = 0.0;
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_OK);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(from_float_to_decimal_unnormal2) {
    float f = -0.0;
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_OK);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(from_float_to_decimal_unnormal3) {
    float f = INFINITY;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_unnormal4) {
    float f = -INFINITY;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_unnormal5) {
    float f = NAN;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_unnormal6) {
    float f = -NAN;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_float_to_decimal_incorrect1) {
    float f = 1.0f;
    int code = s21_from_float_to_decimal(f, NULL);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_fail_big) {
    float f = fails_big[_i];
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_fail_big_negate) {
    float f = -fails_big[_i];
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_fail_small) {
    float f = fails_small[_i];
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(from_float_to_decimal_fail_small_negate) {
    float f = -fails_small[_i];
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на корректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_float_to_decimal_ok_big) {
    float f = oks_big[_i];

    test_from_float_to_decimal(f);
}
END_TEST

START_TEST(from_float_to_decimal_ok_big_negate) {
    float f = -oks_big[_i];

    test_from_float_to_decimal(f);
}
END_TEST

START_TEST(from_float_to_decimal_ok_small) {
    float f = oks_small[_i];

    test_from_float_to_decimal(f);
}
END_TEST

START_TEST(from_float_to_decimal_ok_small_negate) {
    float f = -oks_small[_i];

    test_from_float_to_decimal(f);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на рандомные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_float_to_decimal_ok_random1) {
    float f = s21_random_double(1e-10, 1.0);
    test_from_float_to_decimal(f);
    test_from_float_to_decimal(-f);
}
END_TEST

START_TEST(from_float_to_decimal_ok_random2) {
    float f = s21_random_double(1.0, 1e10);
    test_from_float_to_decimal(f);
    test_from_float_to_decimal(-f);
}
END_TEST

START_TEST(from_float_to_decimal_ok_random3) {
    float f = s21_random_double(1e10, 1e20);
    test_from_float_to_decimal(f);
    test_from_float_to_decimal(-f);
}
END_TEST

Suite *from_float_to_decimal_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal");
    tc_core = tcase_create("Core");

    tcase_add_loop_test(tc_core, from_float_to_decimal_fail_big, 0, sizeof(fails_big) / sizeof(*fails_big));
    tcase_add_loop_test(tc_core, from_float_to_decimal_fail_big_negate, 0,
                        sizeof(fails_big) / sizeof(*fails_big));
    tcase_add_loop_test(tc_core, from_float_to_decimal_fail_small, 0,
                        sizeof(fails_small) / sizeof(*fails_small));
    tcase_add_loop_test(tc_core, from_float_to_decimal_fail_small_negate, 0,
                        sizeof(fails_small) / sizeof(*fails_small));

    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_big_negate, 0, sizeof(oks_big) / sizeof(*oks_big));
    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_big, 0, sizeof(oks_big) / sizeof(*oks_big));
    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_small, 0, sizeof(oks_small) / sizeof(*oks_small));
    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_small_negate, 0,
                        sizeof(oks_small) / sizeof(*oks_small));

    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_random1, 0, NUM_RANDOM_TEST);
    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_random2, 0, NUM_RANDOM_TEST);
    tcase_add_loop_test(tc_core, from_float_to_decimal_ok_random3, 0, NUM_RANDOM_TEST);

    tcase_add_test(tc_core, from_float_to_decimal_incorrect1);
    tcase_add_test(tc_core, from_float_to_decimal_unnormal1);
    tcase_add_test(tc_core, from_float_to_decimal_unnormal2);
    tcase_add_test(tc_core, from_float_to_decimal_unnormal3);
    tcase_add_test(tc_core, from_float_to_decimal_unnormal4);
    tcase_add_test(tc_core, from_float_to_decimal_unnormal5);
    tcase_add_test(tc_core, from_float_to_decimal_unnormal6);

    suite_add_tcase(s, tc_core);

    return s;
}

void test_from_float_to_decimal(float f) {
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    char str_float[128];
    char str_decimal[128];
    sprintf(str_float, "%.28f", f);
    s21_decimal_to_string(result, str_decimal);

    #if defined(__DEBUG)
    // printf("---------------------------------\n");
    // printf("Float:   %s\n", str_float);
    printf("%sM,\n", str_decimal);
    #endif
    char str_decimal_copy[128];
    strcpy(str_decimal_copy, str_decimal);
    test_remove_trailing_zeros(str_float);
    test_remove_trailing_zeros(str_decimal);

    #if defined(__DEBUG)
    // printf("remove_trailing_zeros:\n");
    // printf("Float:   %s\n", str_float);
    if (strcmp(str_decimal, str_decimal_copy) != 0)
        printf("%sM,\n", str_decimal);
    // printf("-------------------------------\n");
    #endif

    ck_assert_int_eq(code, TEST_CONVERSION_OK);
    ck_assert_str_eq(str_float, str_decimal);
}

void test_remove_trailing_zeros(char *str) {
    if (strchr(str, '.') != NULL) {
        int stop = 0;
        size_t i = strlen(str);
        while (!stop) {
            if (str[i - 1] == '0') {
                str[i - 1] = '\0';
            } else if (str[i - 1] == '.') {
                str[i - 1] = '\0';
                stop = 1;
            } else {
                stop = 1;
            }
            --i;
        }
    }
}
