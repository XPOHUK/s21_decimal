#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../s21_decimal.h"
#include "./../s21_decimal/_debug.h"
#include "./test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на корректные decimal
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_debug1) {
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    char check[1024] = "0";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug2) {
    s21_decimal decimal = {{0x3B9ACA00, 0x0, 0x0, 0x0}};
    char check[1024] = "1000000000";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug3) {
    s21_decimal decimal = {{0x0, 0x3B9ACA00, 0x0, 0x0}};
    char check[1024] = "4294967296000000000";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug4) {
    s21_decimal decimal = {{0x0, 0x0, 0x3B9ACA00, 0x0}};
    char check[1024] = "18446744073709551616000000000";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug5) {
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162514264337593543950335";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug6) {
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162514264337593543950335";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug7) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000004294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug8) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x100000}};
    char check[1024] = "0.0000004294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug9) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0xB0000}};
    char check[1024] = "0.04294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug10) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0xA0000}};
    char check[1024] = "0.4294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug11) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    char check[1024] = "4.294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug12) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-4.294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug13) {
    s21_decimal decimal = {{-1, 0x0, 0x0, 0x10000}};
    char check[1024] = "429496729.5";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug14) {
    s21_decimal decimal = {{0xF0000, 0xF0000, 0xF0000, 0xF0000}};
    char check[1024] = "18133887298.441562272235520";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug15) {
    // Вообще тут -0.000000000, но мы не делаем разницы между 0 и -0 в т.ч. и в to_string
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80090000}};
    char check[1024] = "0.000000000";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug16) {
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000000000000000";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug17) {
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000000000000001";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug18) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000004294967295";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug19) {
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000004294967296";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug20) {
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000018446744069414584320";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug21) {
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x1C0000}};
    char check[1024] = "0.0000000018446744073709551616";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug22) {
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162495817593519834398720";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug23) {
    s21_decimal decimal = {{0xFFFFFFFF, 0x1, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000008589934591";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug24) {
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000018446744073709551615";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug25) {
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x1, 0x1C0000}};
    char check[1024] = "0.0000000036893488147419103231";

    test_debug(decimal, check);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные decimal
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Степень от 0 до 28
// Для положительных чисел int[3] может быть:
// от 0x0 до 0x1C0000   (unsigned int)
// от 0x0 до 0x1C0000   (int)
// от 00000000 00000000 00000000 00000000 - степень 0
// до 00000000 00000000 00000000 00011100 - степень 28
//
// Для отрицательных чисел int[3] может быть:
// от 0x80000000 до 0x8000001C   (unsigned int)
// от -2147483648 до -2147483620 (int)
// от 10000000 00000000 00000000 00000000 - степень 0
// от 10000000 00000000 00000000 00011100 - степень 28
//
// Остальные значения не являются корректными

START_TEST(test_debug_fail1) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail2) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail4) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail5) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail6) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail7) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail8) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

Suite * debug_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_debug1);
    tcase_add_test(tc_core, test_debug2);
    tcase_add_test(tc_core, test_debug3);
    tcase_add_test(tc_core, test_debug4);
    tcase_add_test(tc_core, test_debug5);
    tcase_add_test(tc_core, test_debug6);
    tcase_add_test(tc_core, test_debug7);
    tcase_add_test(tc_core, test_debug8);
    tcase_add_test(tc_core, test_debug9);
    tcase_add_test(tc_core, test_debug10);
    tcase_add_test(tc_core, test_debug11);
    tcase_add_test(tc_core, test_debug12);
    tcase_add_test(tc_core, test_debug13);
    tcase_add_test(tc_core, test_debug14);
    tcase_add_test(tc_core, test_debug15);
    tcase_add_test(tc_core, test_debug16);
    tcase_add_test(tc_core, test_debug17);
    tcase_add_test(tc_core, test_debug18);
    tcase_add_test(tc_core, test_debug19);
    tcase_add_test(tc_core, test_debug20);
    tcase_add_test(tc_core, test_debug21);
    tcase_add_test(tc_core, test_debug22);
    tcase_add_test(tc_core, test_debug23);
    tcase_add_test(tc_core, test_debug24);
    tcase_add_test(tc_core, test_debug25);

    tcase_add_test(tc_core, test_debug_fail1);
    tcase_add_test(tc_core, test_debug_fail2);
    tcase_add_test(tc_core, test_debug_fail3);
    tcase_add_test(tc_core, test_debug_fail4);
    tcase_add_test(tc_core, test_debug_fail5);
    tcase_add_test(tc_core, test_debug_fail6);
    tcase_add_test(tc_core, test_debug_fail7);
    tcase_add_test(tc_core, test_debug_fail8);

    suite_add_tcase(s, tc_core);

    return s;
}

void test_debug(s21_decimal decimal, char *check) {
    #if defined(__DEBUG)
    s21_print_decimal_bits(decimal);
    s21_print_decimal_string(decimal);
    printf("%s\n", check);
    #endif

    char res[1024];
    s21_decimal_to_string(decimal, res);
    ck_assert_str_eq(check, res);
}
