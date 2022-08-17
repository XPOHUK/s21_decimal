#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

#define __DEBUG
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_division_ok1) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 79228162514264337593543950335
    s21_decimal divisor = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Chastnoe
    // 1
    s21_decimal quotient = {{0x1, 0x0, 0x0, 0x0}};


    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok2) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 79228162514264337593543950334
    s21_decimal divisor = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Chastnoe
    // 1
    s21_decimal quotient = {{0x1, 0x0, 0x0, 0x0}};


    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok3) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 52818775009509558395695966890
    s21_decimal divisor = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // Chastnoe
    // 1
    s21_decimal quotient = {{0xF, 0x0, 0x0, 0x10000}};

    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok4) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 52818775009509558392832655360
    s21_decimal divisor = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // Chastnoe
    s21_decimal quotient = {{0xC877B58D, 0x5D378391, 0x3077B58D, 0x1C0000}};

    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok5) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 52818774997211729016086244010
    s21_decimal divisor = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    // Chastnoe
    // 1
    s21_decimal quotient = {{0xF5378391, 0x8DAF391E, 0x3077B58D, 0x1C0000}};

    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok6) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 52818774997211729013222932480
    s21_decimal divisor = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    // Chastnoe
    // 1
    s21_decimal quotient = {{0x25AF391F, 0x8DAF391F, 0x3077B58D, 0x1C0000}};

    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok7) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 12297829382473034410
    s21_decimal divisor = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    // Chastnoe
    // 6442450944
    s21_decimal quotient = {{0xD02AB486, 0xCEDC0000, 0xD02AB486, 0x130000}};


    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_my) {
        // Delimoe
        // 155
        s21_decimal dividend = {{0x0000009B, 0x0, 0x0, 0x0}};
        // Delitel
        // 5
        s21_decimal divisor = {{0x00000005, 0x0, 0x0, 0x0}};
        // Chastnoe
        // 31
        s21_decimal quotient = {{0x0000001F, 0x0, 0x0, 0x0}};


        test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok8) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 12297829379609722880
    s21_decimal divisor = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    // Chastnoe
    // 6442450945
    s21_decimal quotient = {{0x9F06B487, 0x9F06B487, 0xD02AB487, 0x130000}};


    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok9) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 2863311530
    s21_decimal divisor = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    // Chastnoe
    // 27670116117006778369
    s21_decimal quotient = {{0xF, 0xF, 0xF, 0x10000}};

    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_ok10) {
    // Delimoe
    // 79228162514264337593543950335
    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Delitel
    // 26409387504754779197847983445
    s21_decimal divisor = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // Chastnoe
    // 3
    s21_decimal quotient = {{0x3, 0x0, 0x0, 0x0}};


    test_division(dividend, divisor, quotient);
}

START_TEST(test_division_11) {
        // Delimoe
        // 15251250625031250156250078125
        s21_decimal dividend = {{0x84DA1BAD, 0x09FB363F, 0x314789F1, 0x0}};
        // Delitel
        // 19807040628566084398385987584
        s21_decimal divisor = {{0x0, 0x0, 0x40000000, 0x0}};
        // Chastnoe
        // 3
        s21_decimal quotient = {{0x327CC9E2, 0x9F722C30, 0x18E1382D, 0x1C0000}};

        test_division(dividend, divisor, quotient);
}


Suite * division_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("division1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_division_ok1);
    tcase_add_test(tc_core, test_division_ok2);
    tcase_add_test(tc_core, test_division_ok3);
    tcase_add_test(tc_core, test_division_ok4);
    tcase_add_test(tc_core, test_division_ok5);
    tcase_add_test(tc_core, test_division_ok6);
    tcase_add_test(tc_core, test_division_ok7);
    tcase_add_test(tc_core, test_division_my);
    tcase_add_test(tc_core, test_division_ok8);
    tcase_add_test(tc_core, test_division_ok9);
    tcase_add_test(tc_core, test_division_ok10);
    tcase_add_test(tc_core, test_division_11);

    suite_add_tcase(s, tc_core);
    return s;
}



void test_division(s21_decimal dividend, s21_decimal divisor, s21_decimal quotient) {

    s21_decimal result;
    s21_div(dividend, divisor, &result);

    #if defined(__DEBUG)
    s21_print_decimal_bits(dividend);
    s21_print_decimal_string(dividend);
    s21_print_decimal_bits(divisor);
    s21_print_decimal_string(divisor);
    printf("\n");
    s21_print_decimal_bits(quotient);
    s21_print_decimal_string(quotient);
    s21_print_decimal_bits(result);
    s21_print_decimal_string(result);
    printf("\n");
    #endif

    ck_assert_int_eq(s21_is_equal(result, quotient), 1);
    // ck_assert_int_eq(s21_is_equal(result_remainder, remainder), 1);
    ck_assert_int_eq(s21_decimal_get_sign(result), s21_decimal_get_sign(quotient));
    // ck_assert_int_eq(s21_decimal_get_sign(result_remainder), s21_decimal_get_sign(remainder));
}
