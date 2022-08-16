#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

#define __DEBUG
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_addition_big) {
    // First arg
    // 79228162514264337593543950335
    s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Second arg
    // 79228162514264337593543950335
    s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // Sum
    // 1
    s21_decimal res = {{0x1, 0x0, 0x0, 0x0}};

    test_addition(first, second, res, 1);
}

START_TEST(test_addition_ok2) {
    // First arg
    // 15.95
    s21_decimal first = {{0x63B, 0x0, 0x0, 0x00020000}};
    // Second arg
    // 0.008
    s21_decimal second = {{0x8, 0x0, 0x0, 0x30000}};
    // Result
    // 15.958
    s21_decimal res = {{0x3E56, 0x0, 0x0, 0x30000}};
    test_addition(first, second, res, 0);
}

START_TEST(test_addition_ok3) {
    // First arg
    // 15.95
    s21_decimal first = {{0x63B, 0x0, 0x0, 0x00020000}};
    // Second arg
    // -0.008
    s21_decimal second = {{0x8, 0x0, 0x0, 0x80030000}};
    // Result
    // 15.942
    s21_decimal res = {{0x3E46, 0x0, 0x0, 0x30000}};
    test_addition(first, second, res, 0);
}

START_TEST(test_addition_ok4) {
    // First arg
    // -15.95
    s21_decimal first = {{0x63B, 0x0, 0x0, 0x80020000}};
    // Second arg
    // -0.008
    s21_decimal second = {{0x8, 0x0, 0x0, 0x80030000}};
    // Result
    // -15.958
    s21_decimal res = {{0x3E56, 0x0, 0x0, 0x80030000}};
    test_addition(first, second, res, 0);
}

//START_TEST(test_addition_ok5) {
//    // Delimoe
//    // 79228162514264337593543950335
//    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//    // Delitel
//    // 52818774997211729016086244010
//    s21_decimal divisor = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
//    // Chastnoe
//    // 1
//    s21_decimal quotient = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x001C0000}};
//
//    test_division(dividend, divisor, quotient);
//}
//
//START_TEST(test_addition_ok6) {
//    // Delimoe
//    // 79228162514264337593543950335
//    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//    // Delitel
//    // 52818774997211729013222932480
//    s21_decimal divisor = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
//    // Chastnoe
//    // 1
//    s21_decimal quotient = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x001C0000}};
//
//    test_division(dividend, divisor, quotient);
//}
//
//START_TEST(test_addition_ok7) {
//    // Delimoe
//    // 79228162514264337593543950335
//    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//    // Delitel
//    // 12297829382473034410
//    s21_decimal divisor = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
//    // Chastnoe
//    // 6442450944
//    s21_decimal quotient = {{0x80000000, 0x1, 0x0, 0x0}};
//
//
//    test_division(dividend, divisor, quotient);
//}
//
//START_TEST(test_addition_ok8) {
//    // Delimoe
//    // 79228162514264337593543950335
//    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//    // Delitel
//    // 12297829379609722880
//    s21_decimal divisor = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
//    // Chastnoe
//    // 6442450945
//    s21_decimal quotient = {{0x80000001, 0x1, 0x0, 0x0}};
//
//
//    test_division(dividend, divisor, quotient);
//}
//
//START_TEST(test_addition_ok9) {
//    // Delimoe
//    // 79228162514264337593543950335
//    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//    // Delitel
//    // 2863311530
//    s21_decimal divisor = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
//    // Chastnoe
//    // 27670116117006778369
//    s21_decimal quotient = {{0x80000001, 0x80000001, 0x1, 0x0}};
//
//
//    test_division(dividend, divisor, quotient);
//}
//
//START_TEST(test_addition_ok10) {
//    // Delimoe
//    // 79228162514264337593543950335
//    s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//    // Delitel
//    // 26409387504754779197847983445
//    s21_decimal divisor = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
//    // Chastnoe
//    // 3
//    s21_decimal quotient = {{0x3, 0x0, 0x0, 0x0}};
//
//
//    test_division(dividend, divisor, quotient);
//}

//START_TEST(test_addition_ok11) {
//        // Delimoe
//        // 15251250625031250156250078125
//        s21_decimal dividend = {{0x84DA1BAD, 0x09FB363F, 0x314789F1, 0x0}};
//        // Delitel
//        // 19807040628566084398385987584
//        s21_decimal divisor = {{0x0, 0x0, 0x40000000, 0x0}};
//        // Chastnoe
//        // 3
//        s21_decimal quotient = {{0x3, 0x0, 0x0, 0x0}};
//
//
//        test_division(dividend, divisor, quotient);
//}

// START_TEST(test_addition_ok12) {
//         // First arg
//         // 155
//         s21_decimal first = {{0x0000009B, 0x0, 0x0, 0x0}};
//         // Second arg
//         // 5
//         s21_decimal second = {{0x00000005, 0x0, 0x0, 0x0}};
//         // Sum
//         // 160
//         s21_decimal res = {{0x000000A0, 0x0, 0x0, 0x0}};
// 
//         test_addition(first, second, res, 0);
// }


Suite * addition_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("addition1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_addition_big);
    tcase_add_test(tc_core, test_addition_ok2);
    tcase_add_test(tc_core, test_addition_ok3);
    tcase_add_test(tc_core, test_addition_ok4);
//    tcase_add_test(tc_core, test_addition_ok5);
//    tcase_add_test(tc_core, test_addition_ok6);
//    tcase_add_test(tc_core, test_addition_ok7);
//    tcase_add_test(tc_core, test_addition_ok8);
//    tcase_add_test(tc_core, test_addition_ok9);
//    tcase_add_test(tc_core, test_addition_ok10);
//    tcase_add_test(tc_core, test_addition_ok11);
//     tcase_add_test(tc_core, test_addition_ok12);
    suite_add_tcase(s, tc_core);
    return s;
}



void test_addition(s21_decimal first, s21_decimal second, s21_decimal res, int code) {

    s21_decimal result;
    int res_code = s21_add(first, second, &result);

    #if defined(__DEBUG)
    s21_print_decimal_bits(first);
    s21_print_decimal_string(first);
    s21_print_decimal_bits(second);
    s21_print_decimal_string(second);
    printf("\n");
    s21_print_decimal_bits(result);
    s21_print_decimal_string(result);
    printf("\n");
    #endif

    if (code == 0) {
        ck_assert_int_eq(s21_is_equal(result, res), 1);
    } else {
        ck_assert_int_eq(code, res_code);
    }
    ck_assert_int_eq(s21_decimal_get_sign(result), s21_decimal_get_sign(res));
}
