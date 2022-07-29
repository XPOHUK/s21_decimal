#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные (ручные)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(from_truncate_fail1) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    int code = s21_truncate(decimal, NULL);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(from_truncate_fail2) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail4) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail5) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail6) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail7) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail8) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(from_truncate_fail9) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;

    int code = s21_truncate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_truncate_ok1) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok2) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok5) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok6) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok7) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok8) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok9) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok10) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok11) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok12) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok13) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok14) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok15) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok16) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok17) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok18) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok19) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok20) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok21) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok22) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok23) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok24) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok25) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok26) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok27) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok28) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok29) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok30) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok31) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok32) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok33) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok34) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok35) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok36) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok37) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok38) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok39) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok40) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok41) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok42) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok43) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok44) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok45) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok46) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok47) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok48) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok49) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok50) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok51) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok52) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok53) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok54) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok55) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok56) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok57) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok58) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok59) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok60) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok61) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok62) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok63) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok64) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok65) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok66) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok67) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok68) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok69) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok70) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok71) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok72) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok73) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok74) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok75) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok76) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok77) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok78) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok79) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok80) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok81) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok82) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok83) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok84) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok85) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok86) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok87) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok88) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok89) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok90) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok91) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok92) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok93) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok94) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok95) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok96) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok97) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok98) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok99) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok100) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok101) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok102) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok103) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok104) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok105) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok106) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok107) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok108) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok109) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok110) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok111) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok112) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok113) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok114) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok115) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok116) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok117) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok118) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok119) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok120) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok121) {
    // 5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok122) {
    // -5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok123) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok124) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok125) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok126) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok127) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok128) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok129) {
    // 5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok130) {
    // -5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok131) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok132) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok133) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok134) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok135) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok136) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok137) {
    // 5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok138) {
    // -5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok139) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok140) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok141) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok142) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok143) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok144) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok145) {
    // 5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok146) {
    // -5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok147) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok148) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok149) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok150) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok151) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok152) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok153) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok154) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok155) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok156) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok157) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok158) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok159) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok160) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok161) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok162) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok163) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok164) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok165) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    // 2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok166) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    // -2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok167) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    // 286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok168) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    // -286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok169) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    // 286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok170) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    // -286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok171) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok172) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok173) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok174) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok175) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919784798344
    s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok176) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919784798344
    s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok177) {
    // 2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok178) {
    // -2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok179) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok180) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok181) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok182) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok183) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok184) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok185) {
    // 2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok186) {
    // -2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok187) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok188) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok189) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // 26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok190) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok191) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450804312200
    s21_decimal decimal_check = {{0x8888888, 0x80000000, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok192) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450804312200
    s21_decimal decimal_check = {{0x8888888, 0x80000000, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok193) {
    // 2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok194) {
    // -2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok195) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok196) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok197) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    // 26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok198) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok199) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok200) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok201) {
    // 2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok202) {
    // -2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok203) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok204) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok205) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // 6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok206) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // -6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok207) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    // 614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok208) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    // -614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok209) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    // 6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok210) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    // -6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok211) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok212) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok213) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    // 6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok214) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // -6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok215) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    // 614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok216) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    // -614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok217) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    // 6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok218) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    // -6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok219) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok220) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok221) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    // 1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok222) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // -1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok223) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    // 143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok224) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    // -143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok225) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    // 143165
    s21_decimal decimal_check = {{0x22F3D, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok226) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    // -143165
    s21_decimal decimal_check = {{0x22F3D, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok227) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok228) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok229) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    // 18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok230) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    // -18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok231) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok232) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    // -1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok233) {
    // 184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000}};
    // 184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok234) {
    // -184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80080000}};
    // -184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok235) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok236) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok237) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    // 18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok238) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    // -18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok239) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok240) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    // -1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok241) {
    // 18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x90000}};
    // 18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok242) {
    // -18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80090000}};
    // -18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok243) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok244) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok245) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    // 18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok246) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    // -18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok247) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok248) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    // -1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok249) {
    // 1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xA0000}};
    // 1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok250) {
    // -1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800A0000}};
    // -1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok251) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok252) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok253) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    // 18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok254) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    // -18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok255) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok256) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    // -1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok257) {
    // 184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xB0000}};
    // 184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok258) {
    // -184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800B0000}};
    // -184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok259) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok260) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok261) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    // 4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok262) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    // -4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok263) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok264) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    // -429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok265) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok266) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    // -42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok267) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    // 429496
    s21_decimal decimal_check = {{0x68DB8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok268) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    // -429496
    s21_decimal decimal_check = {{0x68DB8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok269) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok270) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok271) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok272) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    // -42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok273) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    // 4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok274) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    // -4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok275) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok276) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    // -429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok277) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok278) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    // -42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok279) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    // 4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok280) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    // -4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok281) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok282) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok283) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok284) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    // -42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok285) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok286) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok287) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok288) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok289) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok290) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok291) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok292) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok293) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok294) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok295) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok296) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok297) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok298) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok299) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083577423462
    s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok300) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083577423462
    s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok301) {
    // 39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
    // 39614081266355
    s21_decimal decimal_check = {{0x5F3DF2B3, 0x2407, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok302) {
    // -39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
    // -39614081266355
    s21_decimal decimal_check = {{0x5F3DF2B3, 0x2407, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok303) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok304) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok305) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok306) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok307) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083362675097
    s21_decimal decimal_check = {{0x99999999, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok308) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083362675097
    s21_decimal decimal_check = {{0x99999999, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok309) {
    // 3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0xD0000}};
    // 3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok310) {
    // -3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x800D0000}};
    // -3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok311) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok312) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok313) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    // 39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok314) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok315) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879891945881
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok316) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879891945881
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok317) {
    // 39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0xC0000}};
    // 39614081257132168
    s21_decimal decimal_check = {{0x96F5088, 0x8CBCCC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok318) {
    // -39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x800C0000}};
    // -39614081257132168
    s21_decimal decimal_check = {{0x96F5088, 0x8CBCCC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok319) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok320) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok321) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    // 39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok322) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok323) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879677197516
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok324) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879677197516
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok325) {
    // 396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0xB0000}};
    // 396140812571321687
    s21_decimal decimal_check = {{0x5E592557, 0x57F5FF8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok326) {
    // -396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x800B0000}};
    // -396140812571321687
    s21_decimal decimal_check = {{0x5E592557, 0x57F5FF8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok327) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok328) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok329) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    // 9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok330) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    // -9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok331) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    // 922337203900225945
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok332) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    // -922337203900225945
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok333) {
    // 922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x70000}};
    // 922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok334) {
    // -922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80070000}};
    // -922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok335) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok336) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok337) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    // 9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok338) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    // -9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok339) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    // 922337203685477580
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok340) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    // -922337203685477580
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok341) {
    // 92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000}};
    // 92233720368
    s21_decimal decimal_check = {{0x798EE230, 0x15, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok342) {
    // -92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80080000}};
    // -92233720368
    s21_decimal decimal_check = {{0x798EE230, 0x15, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok343) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok344) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok345) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    // 2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok346) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    // -2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok347) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    // 214748364
    s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok348) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    // -214748364
    s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok349) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    // 21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok350) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    // -21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok351) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    // 214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok352) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    // -214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok353) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    // 21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok354) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    // -21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok355) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok356) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok357) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    // 156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok358) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok359) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok360) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok361) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    // 1560647
    s21_decimal decimal_check = {{0x17D047, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok362) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    // -1560647
    s21_decimal decimal_check = {{0x17D047, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok363) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok364) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok365) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    // 156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok366) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok367) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269529696665
    s21_decimal decimal_check = {{0x99999999, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok368) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269529696665
    s21_decimal decimal_check = {{0x99999999, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok369) {
    // 15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x40000}};
    // 15606476756221269529696
    s21_decimal decimal_check = {{0x27525460, 0x75F7320, 0x34E, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok370) {
    // -15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80040000}};
    // -15606476756221269529696
    s21_decimal decimal_check = {{0x27525460, 0x75F7320, 0x34E, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok371) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok372) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok373) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    // 156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok374) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok375) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    // 15606476752587603503068569
    s21_decimal decimal_check = {{0xCCD9B599, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok376) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603503068569
    s21_decimal decimal_check = {{0xCCD9B599, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok377) {
    // 1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0xB0000}};
    // 1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok378) {
    // -1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x800B0000}};
    // -1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok379) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok380) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok381) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    // 156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok382) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok383) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    // 15606476752587603502222540
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok384) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603502222540
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok385) {
    // 15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x130000}};
    // 15606476
    s21_decimal decimal_check = {{0xEE22CC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok386) {
    // -15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80130000}};
    // -15606476
    s21_decimal decimal_check = {{0xEE22CC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok387) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok388) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok389) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    // 36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok390) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    // -36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok391) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    // 3633666028320153
    s21_decimal decimal_check = {{0xCCD9B599, 0xCE8CC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok392) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    // -3633666028320153
    s21_decimal decimal_check = {{0xCCD9B599, 0xCE8CC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok393) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    // 363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok394) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    // -363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok395) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok396) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok397) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    // 36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok398) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    // -36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok399) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    // 3633666027474124
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCE8CC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok400) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    // -3633666027474124
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCE8CC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok401) {
    // 363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x20000}};
    // 363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok402) {
    // -363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80020000}};
    // -363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok403) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    // 363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok404) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    // -363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok405) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    // 36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok406) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    // -36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok407) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok408) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok409) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    // 8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok410) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    // -8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok411) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    // 846028
    s21_decimal decimal_check = {{0xCE8CC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok412) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    // -846028
    s21_decimal decimal_check = {{0xCE8CC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok413) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    // 84602
    s21_decimal decimal_check = {{0x14A7A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok414) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    // -84602
    s21_decimal decimal_check = {{0x14A7A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok415) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    // 8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok416) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    // -8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok417) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    // 84
    s21_decimal decimal_check = {{0x54, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok418) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    // -84
    s21_decimal decimal_check = {{0x54, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok419) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok420) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok421) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok422) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok423) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok424) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok425) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok426) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok427) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok428) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok429) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok430) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok431) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok432) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok433) {
    // 79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok434) {
    // -79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok435) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok436) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok437) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok438) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok439) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759352412936601
    s21_decimal decimal_check = {{0x19999999, 0x80000000, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok440) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759352412936601
    s21_decimal decimal_check = {{0x19999999, 0x80000000, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok441) {
    // 792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x110000}};
    // 792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok442) {
    // -792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80110000}};
    // -792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok443) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok444) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok445) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok446) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok447) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok448) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok449) {
    // 79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x120000}};
    // 79228162495
    s21_decimal decimal_check = {{0x725DD1BF, 0x12, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok450) {
    // -79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80120000}};
    // -79228162495
    s21_decimal decimal_check = {{0x725DD1BF, 0x12, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok451) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok452) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok453) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok454) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok455) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok456) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok457) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744073709551
    s21_decimal decimal_check = {{0x4BC6A7EF, 0x418937, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok458) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744073709551
    s21_decimal decimal_check = {{0x4BC6A7EF, 0x418937, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok459) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    // 184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok460) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    // -184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok461) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok462) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok463) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok464) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok465) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok466) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok467) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok468) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok469) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok470) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok471) {
    // 18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x90000}};
    // 18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok472) {
    // -18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80090000}};
    // -18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok473) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok474) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok475) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok476) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok477) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    // 4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok478) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    // -4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok479) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok480) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    // -429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok481) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok482) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    // -42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok483) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    // 42949
    s21_decimal decimal_check = {{0xA7C5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok484) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    // -42949
    s21_decimal decimal_check = {{0xA7C5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok485) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok486) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    // -42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok487) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok488) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok489) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok490) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok491) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok492) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok493) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok494) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok495) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok496) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok497) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok498) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok499) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok500) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok501) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok502) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok503) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok504) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok505) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok506) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok507) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    // 12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok508) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    // -12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok509) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    // 123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok510) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    // -123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok511) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    // 1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok512) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    // -1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok513) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    // 12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok514) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    // -12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok515) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    // 123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok516) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    // -123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok517) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    // 1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok518) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    // -1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok519) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    // 1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok520) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    // -1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok521) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    // 12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok522) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    // -12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok523) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok524) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok525) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok526) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok527) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok528) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok529) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    // 999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok530) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    // -999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok531) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    // 9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok532) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    // -9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok533) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    // 99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok534) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    // -99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok535) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    // 999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok536) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    // -999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok537) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    // 9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok538) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    // -9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok539) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    // 99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok540) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    // -99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok541) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    // 999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok542) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    // -999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok543) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    // 9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok544) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    // -9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok545) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok546) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok547) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok548) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok549) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok550) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok551) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok552) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok553) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok554) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok555) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok556) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok557) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok558) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok559) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok560) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok561) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok562) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok563) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok564) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok565) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok566) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok567) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok568) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok569) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok570) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok571) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok572) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok573) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok574) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok575) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok576) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok577) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok578) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok579) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok580) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok581) {
    // -4828.9446644116856801243725283
    s21_decimal decimal = {{0x73087DE3, 0xFBD4E6FD, 0x9C081813, 0x80190000}};
    // -4828
    s21_decimal decimal_check = {{0x12DC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok582) {
    // 4828.9446644116856801243725283
    s21_decimal decimal = {{0x73087DE3, 0xFBD4E6FD, 0x9C081813, 0x190000}};
    // 4828
    s21_decimal decimal_check = {{0x12DC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok583) {
    // -3710418801279584172.6405642925
    s21_decimal decimal = {{0xAE078AAD, 0x96D55CE7, 0x77E3DD6E, 0x800A0000}};
    // -3710418801279584172
    s21_decimal decimal_check = {{0xBA3347AC, 0x337E0E3D, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok584) {
    // 3710418801279584172.6405642925
    s21_decimal decimal = {{0xAE078AAD, 0x96D55CE7, 0x77E3DD6E, 0xA0000}};
    // 3710418801279584172
    s21_decimal decimal_check = {{0xBA3347AC, 0x337E0E3D, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok585) {
    // -7394445631927623396301072144.6
    s21_decimal decimal = {{0x62C306A6, 0x3B1ED145, 0xEEED6BB1, 0x80010000}};
    // -7394445631927623396301072144
    s21_decimal decimal_check = {{0x2379E710, 0xEC4FE1BA, 0x17E48AC4, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok586) {
    // 7394445631927623396301072144.6
    s21_decimal decimal = {{0x62C306A6, 0x3B1ED145, 0xEEED6BB1, 0x10000}};
    // 7394445631927623396301072144
    s21_decimal decimal_check = {{0x2379E710, 0xEC4FE1BA, 0x17E48AC4, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok587) {
    // 78673334607524209336.487129845
    s21_decimal decimal = {{0x851E32F5, 0xE8681902, 0xFE350E9E, 0x90000}};
    // 78673334607524209336
    s21_decimal decimal_check = {{0x10ED22B8, 0x43CFD4FF, 0x4, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok588) {
    // -78673334607524209336.487129845
    s21_decimal decimal = {{0x851E32F5, 0xE8681902, 0xFE350E9E, 0x80090000}};
    // -78673334607524209336
    s21_decimal decimal_check = {{0x10ED22B8, 0x43CFD4FF, 0x4, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok589) {
    // 5896498003307442.2639123774664
    s21_decimal decimal = {{0x9C9C3CC8, 0x9F05EA3E, 0xBE86B034, 0xD0000}};
    // 5896498003307442
    s21_decimal decimal_check = {{0x6CE7EBB2, 0x14F2D5, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok590) {
    // -5896498003307442.2639123774664
    s21_decimal decimal = {{0x9C9C3CC8, 0x9F05EA3E, 0xBE86B034, 0x800D0000}};
    // -5896498003307442
    s21_decimal decimal_check = {{0x6CE7EBB2, 0x14F2D5, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok591) {
    // -5005404.6095855691162623642793
    s21_decimal decimal = {{0x8E7B8CA9, 0xF0D952D2, 0xA1BBBC8B, 0x80160000}};
    // -5005404
    s21_decimal decimal_check = {{0x4C605C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok592) {
    // 5005404.6095855691162623642793
    s21_decimal decimal = {{0x8E7B8CA9, 0xF0D952D2, 0xA1BBBC8B, 0x160000}};
    // 5005404
    s21_decimal decimal_check = {{0x4C605C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok593) {
    // 2986702101489772704227.7352327
    s21_decimal decimal = {{0x9CC2387, 0x80492CBA, 0x60816BB5, 0x70000}};
    // 2986702101489772704227
    s21_decimal decimal_check = {{0x3A94B1E3, 0xE8D16914, 0xA1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok594) {
    // -2986702101489772704227.7352327
    s21_decimal decimal = {{0x9CC2387, 0x80492CBA, 0x60816BB5, 0x80070000}};
    // -2986702101489772704227
    s21_decimal decimal_check = {{0x3A94B1E3, 0xE8D16914, 0xA1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok595) {
    // -6.2733047331905945043269348527
    s21_decimal decimal = {{0x4C46CAF, 0x31C584FB, 0xCAB38F7E, 0x801C0000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok596) {
    // 6.2733047331905945043269348527
    s21_decimal decimal = {{0x4C46CAF, 0x31C584FB, 0xCAB38F7E, 0x1C0000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok597) {
    // -4366962987452527344893808.6684
    s21_decimal decimal = {{0x656E211C, 0x1474F129, 0x8D1AABD3, 0x80040000}};
    // -4366962987452527344893808
    s21_decimal decimal_check = {{0x577C3F70, 0x89B4568D, 0x39CBD, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok598) {
    // 4366962987452527344893808.6684
    s21_decimal decimal = {{0x656E211C, 0x1474F129, 0x8D1AABD3, 0x40000}};
    // 4366962987452527344893808
    s21_decimal decimal_check = {{0x577C3F70, 0x89B4568D, 0x39CBD, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok599) {
    // 42490320706638707602.748688751
    s21_decimal decimal = {{0x64F5496F, 0xFCB780CC, 0x894B2B64, 0x90000}};
    // 42490320706638707602
    s21_decimal decimal_check = {{0x2F9FFB92, 0x4DABF18F, 0x2, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok600) {
    // -42490320706638707602.748688751
    s21_decimal decimal = {{0x64F5496F, 0xFCB780CC, 0x894B2B64, 0x80090000}};
    // -42490320706638707602
    s21_decimal decimal_check = {{0x2F9FFB92, 0x4DABF18F, 0x2, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok601) {
    // -6946305934356114622782.0593671
    s21_decimal decimal = {{0xB5280207, 0x6390A105, 0xE0727EF8, 0x80070000}};
    // -6946305934356114622782
    s21_decimal decimal_check = {{0xD414C93E, 0x8F5C1C30, 0x178, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok602) {
    // 6946305934356114622782.0593671
    s21_decimal decimal = {{0xB5280207, 0x6390A105, 0xE0727EF8, 0x70000}};
    // 6946305934356114622782
    s21_decimal decimal_check = {{0xD414C93E, 0x8F5C1C30, 0x178, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok603) {
    // 2250685077923960286.7696180859
    s21_decimal decimal = {{0x9EBE1E7B, 0x886E4021, 0x48B93B09, 0xA0000}};
    // 2250685077923960286
    s21_decimal decimal_check = {{0x5AEE15DE, 0x1F3C0A27, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok604) {
    // -2250685077923960286.7696180859
    s21_decimal decimal = {{0x9EBE1E7B, 0x886E4021, 0x48B93B09, 0x800A0000}};
    // -2250685077923960286
    s21_decimal decimal_check = {{0x5AEE15DE, 0x1F3C0A27, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok605) {
    // 5831356831115224482298039.0668
    s21_decimal decimal = {{0xD71F6F0C, 0x6AAA0178, 0xBC6BDA68, 0x40000}};
    // 5831356831115224482298039
    s21_decimal decimal_check = {{0x401FB8B7, 0x7CBBDEAB, 0x4D2D6, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok606) {
    // -5831356831115224482298039.0668
    s21_decimal decimal = {{0xD71F6F0C, 0x6AAA0178, 0xBC6BDA68, 0x80040000}};
    // -5831356831115224482298039
    s21_decimal decimal_check = {{0x401FB8B7, 0x7CBBDEAB, 0x4D2D6, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok607) {
    // 78505447.02872463144011775639
    s21_decimal decimal = {{0x64A93E97, 0x1A39D064, 0x195DD181, 0x140000}};
    // 78505447
    s21_decimal decimal_check = {{0x4ADE5E7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok608) {
    // -78505447.02872463144011775639
    s21_decimal decimal = {{0x64A93E97, 0x1A39D064, 0x195DD181, 0x80140000}};
    // -78505447
    s21_decimal decimal_check = {{0x4ADE5E7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok609) {
    // -146861595029464533951.114803
    s21_decimal decimal = {{0x72CEE33, 0x4EFA368, 0x797B27, 0x80060000}};
    // -146861595029464533951
    s21_decimal decimal_check = {{0xBE81CBBF, 0xF61D3292, 0x7, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok610) {
    // 146861595029464533951.114803
    s21_decimal decimal = {{0x72CEE33, 0x4EFA368, 0x797B27, 0x60000}};
    // 146861595029464533951
    s21_decimal decimal_check = {{0xBE81CBBF, 0xF61D3292, 0x7, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok611) {
    // -6139.1321668467672541391467764
    s21_decimal decimal = {{0xF367B4F4, 0x3C46B10B, 0xC65DB608, 0x80190000}};
    // -6139
    s21_decimal decimal_check = {{0x17FB, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok612) {
    // 6139.1321668467672541391467764
    s21_decimal decimal = {{0xF367B4F4, 0x3C46B10B, 0xC65DB608, 0x190000}};
    // 6139
    s21_decimal decimal_check = {{0x17FB, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok613) {
    // -53.481243038019987908228744584
    s21_decimal decimal = {{0x3D7F0588, 0x73CBAB7A, 0xACCEA5BA, 0x801B0000}};
    // -53
    s21_decimal decimal_check = {{0x35, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok614) {
    // 53.481243038019987908228744584
    s21_decimal decimal = {{0x3D7F0588, 0x73CBAB7A, 0xACCEA5BA, 0x1B0000}};
    // 53
    s21_decimal decimal_check = {{0x35, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok615) {
    // -6387001091146973938552571.1088
    s21_decimal decimal = {{0x186130F0, 0x582BCB15, 0xCE6008E5, 0x80040000}};
    // -6387001091146973938552571
    s21_decimal decimal_check = {{0x95398EFB, 0x5DF0815, 0x54880, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok616) {
    // 6387001091146973938552571.1088
    s21_decimal decimal = {{0x186130F0, 0x582BCB15, 0xCE6008E5, 0x40000}};
    // 6387001091146973938552571
    s21_decimal decimal_check = {{0x95398EFB, 0x5DF0815, 0x54880, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok617) {
    // -65086817749012254712.218419867
    s21_decimal decimal = {{0xC2CE829B, 0x2EAF10FF, 0xD24E8DC4, 0x80090000}};
    // -65086817749012254712
    s21_decimal decimal_check = {{0xE2770FF8, 0x8742D3E5, 0x3, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok618) {
    // 65086817749012254712.218419867
    s21_decimal decimal = {{0xC2CE829B, 0x2EAF10FF, 0xD24E8DC4, 0x90000}};
    // 65086817749012254712
    s21_decimal decimal_check = {{0xE2770FF8, 0x8742D3E5, 0x3, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok619) {
    // 30486.529320600415583193438107
    s21_decimal decimal = {{0xCD7A979B, 0xC01A37F, 0x6281DDB2, 0x180000}};
    // 30486
    s21_decimal decimal_check = {{0x7716, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok620) {
    // -30486.529320600415583193438107
    s21_decimal decimal = {{0xCD7A979B, 0xC01A37F, 0x6281DDB2, 0x80180000}};
    // -30486
    s21_decimal decimal_check = {{0x7716, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok621) {
    // -6890547008239442829082.2813042
    s21_decimal decimal = {{0xF4A3B572, 0xF92D5D7E, 0xDEA544D9, 0x80070000}};
    // -6890547008239442829082
    s21_decimal decimal_check = {{0xA29B9F1A, 0x898C9C4F, 0x175, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok622) {
    // 6890547008239442829082.2813042
    s21_decimal decimal = {{0xF4A3B572, 0xF92D5D7E, 0xDEA544D9, 0x70000}};
    // 6890547008239442829082
    s21_decimal decimal_check = {{0xA29B9F1A, 0x898C9C4F, 0x175, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok623) {
    // 348557923921022818696.47507028
    s21_decimal decimal = {{0x226D6E54, 0xC2D435CE, 0x70A00923, 0x80000}};
    // 348557923921022818696
    s21_decimal decimal_check = {{0x30321988, 0xE5368111, 0x12, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok624) {
    // -348557923921022818696.47507028
    s21_decimal decimal = {{0x226D6E54, 0xC2D435CE, 0x70A00923, 0x80080000}};
    // -348557923921022818696
    s21_decimal decimal_check = {{0x30321988, 0xE5368111, 0x12, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok625) {
    // -279003477291368638784070538.4
    s21_decimal decimal = {{0xC82AE368, 0x1AEB80C2, 0x903DCD8, 0x80010000}};
    // -279003477291368638784070538
    s21_decimal decimal_check = {{0xAD9DE38A, 0xCF7DF346, 0xE6C948, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok626) {
    // 279003477291368638784070538.4
    s21_decimal decimal = {{0xC82AE368, 0x1AEB80C2, 0x903DCD8, 0x10000}};
    // 279003477291368638784070538
    s21_decimal decimal_check = {{0xAD9DE38A, 0xCF7DF346, 0xE6C948, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok627) {
    // -2039995108414077081564072.294
    s21_decimal decimal = {{0xA951C966, 0x6B8CCD71, 0x69771C4, 0x80030000}};
    // -2039995108414077081564072
    s21_decimal decimal_check = {{0x1F2533A8, 0x5B3E594B, 0x1AFFC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok628) {
    // 2039995108414077081564072.294
    s21_decimal decimal = {{0xA951C966, 0x6B8CCD71, 0x69771C4, 0x30000}};
    // 2039995108414077081564072
    s21_decimal decimal_check = {{0x1F2533A8, 0x5B3E594B, 0x1AFFC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok629) {
    // 70062819041227458495398.719166
    s21_decimal decimal = {{0x5A46AEBE, 0xBF74FD4D, 0xE2629B06, 0x60000}};
    // 70062819041227458495398
    s21_decimal decimal_check = {{0x950843A6, 0x1CEF9545, 0xED6, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok630) {
    // -70062819041227458495398.719166
    s21_decimal decimal = {{0x5A46AEBE, 0xBF74FD4D, 0xE2629B06, 0x80060000}};
    // -70062819041227458495398
    s21_decimal decimal_check = {{0x950843A6, 0x1CEF9545, 0xED6, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok631) {
    // -62238.395006566042936764751400
    s21_decimal decimal = {{0x98B35E28, 0xE80FF93D, 0xC91A64C9, 0x80180000}};
    // -62238
    s21_decimal decimal_check = {{0xF31E, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok632) {
    // 62238.395006566042936764751400
    s21_decimal decimal = {{0x98B35E28, 0xE80FF93D, 0xC91A64C9, 0x180000}};
    // 62238
    s21_decimal decimal_check = {{0xF31E, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok633) {
    // -54228023255750117847641.996373
    s21_decimal decimal = {{0x595DBC55, 0x2C871E6C, 0xAF385E97, 0x80060000}};
    // -54228023255750117847641
    s21_decimal decimal_check = {{0x4F927259, 0xB4FFFEB9, 0xB7B, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok634) {
    // 54228023255750117847641.996373
    s21_decimal decimal = {{0x595DBC55, 0x2C871E6C, 0xAF385E97, 0x60000}};
    // 54228023255750117847641
    s21_decimal decimal_check = {{0x4F927259, 0xB4FFFEB9, 0xB7B, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok635) {
    // 1.4502401506753146244959241825
    s21_decimal decimal = {{0xF4FF0661, 0xFE72E5DD, 0x2EDC1AF8, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok636) {
    // -1.4502401506753146244959241825
    s21_decimal decimal = {{0xF4FF0661, 0xFE72E5DD, 0x2EDC1AF8, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok637) {
    // -505260724.43064302815743674743
    s21_decimal decimal = {{0x5F818977, 0x7F1B97C1, 0xA3423003, 0x80140000}};
    // -505260724
    s21_decimal decimal_check = {{0x1E1DAAB4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok638) {
    // 505260724.43064302815743674743
    s21_decimal decimal = {{0x5F818977, 0x7F1B97C1, 0xA3423003, 0x140000}};
    // 505260724
    s21_decimal decimal_check = {{0x1E1DAAB4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok639) {
    // 373601658.55275108033952559091
    s21_decimal decimal = {{0x1AB52FF3, 0x3C434AD1, 0x78B79AD9, 0x140000}};
    // 373601658
    s21_decimal decimal_check = {{0x1644B57A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok640) {
    // -373601658.55275108033952559091
    s21_decimal decimal = {{0x1AB52FF3, 0x3C434AD1, 0x78B79AD9, 0x80140000}};
    // -373601658
    s21_decimal decimal_check = {{0x1644B57A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok641) {
    // 577128860757644488661266.5880
    s21_decimal decimal = {{0xC03F6618, 0x519A5502, 0x12A5E5E6, 0x40000}};
    // 577128860757644488661266
    s21_decimal decimal_check = {{0xDE12D912, 0x37DE0B52, 0x7A36, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok642) {
    // -577128860757644488661266.5880
    s21_decimal decimal = {{0xC03F6618, 0x519A5502, 0x12A5E5E6, 0x80040000}};
    // -577128860757644488661266
    s21_decimal decimal_check = {{0xDE12D912, 0x37DE0B52, 0x7A36, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok643) {
    // -29935997.743128736361432723967
    s21_decimal decimal = {{0xC3BB1FF, 0x6E5A62DE, 0x60BA7A19, 0x80150000}};
    // -29935997
    s21_decimal decimal_check = {{0x1C8C97D, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok644) {
    // 29935997.743128736361432723967
    s21_decimal decimal = {{0xC3BB1FF, 0x6E5A62DE, 0x60BA7A19, 0x150000}};
    // 29935997
    s21_decimal decimal_check = {{0x1C8C97D, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok645) {
    // 18196470038202427373840458.492
    s21_decimal decimal = {{0xE52B62FC, 0x596D3CC8, 0x3ACBC469, 0x30000}};
    // 18196470038202427373840458
    s21_decimal decimal_check = {{0xD744E84A, 0x9E0A9AF0, 0xF0D40, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok646) {
    // -18196470038202427373840458.492
    s21_decimal decimal = {{0xE52B62FC, 0x596D3CC8, 0x3ACBC469, 0x80030000}};
    // -18196470038202427373840458
    s21_decimal decimal_check = {{0xD744E84A, 0x9E0A9AF0, 0xF0D40, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok647) {
    // -305834.65599940002855804652601
    s21_decimal decimal = {{0xD6B2CC39, 0x478F6AB0, 0x62D20CC0, 0x80170000}};
    // -305834
    s21_decimal decimal_check = {{0x4AAAA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok648) {
    // 305834.65599940002855804652601
    s21_decimal decimal = {{0xD6B2CC39, 0x478F6AB0, 0x62D20CC0, 0x170000}};
    // 305834
    s21_decimal decimal_check = {{0x4AAAA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok649) {
    // -528883.43615860748867825220726
    s21_decimal decimal = {{0xED26BC76, 0x5FB1A0E2, 0xAAE43664, 0x80170000}};
    // -528883
    s21_decimal decimal_check = {{0x811F3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok650) {
    // 528883.43615860748867825220726
    s21_decimal decimal = {{0xED26BC76, 0x5FB1A0E2, 0xAAE43664, 0x170000}};
    // 528883
    s21_decimal decimal_check = {{0x811F3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok651) {
    // 5953333.4042867208048958479097
    s21_decimal decimal = {{0xD0AF9AF9, 0x3AA5DB8B, 0xC05CD1D9, 0x160000}};
    // 5953333
    s21_decimal decimal_check = {{0x5AD735, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok652) {
    // -5953333.4042867208048958479097
    s21_decimal decimal = {{0xD0AF9AF9, 0x3AA5DB8B, 0xC05CD1D9, 0x80160000}};
    // -5953333
    s21_decimal decimal_check = {{0x5AD735, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok653) {
    // 37964672314500.491925501716874
    s21_decimal decimal = {{0xA923298A, 0xDD89224, 0x7AABA412, 0xF0000}};
    // 37964672314500
    s21_decimal decimal_check = {{0x56CEAC84, 0x2287, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok654) {
    // -37964672314500.491925501716874
    s21_decimal decimal = {{0xA923298A, 0xDD89224, 0x7AABA412, 0x800F0000}};
    // -37964672314500
    s21_decimal decimal_check = {{0x56CEAC84, 0x2287, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok655) {
    // 669.49898886995994641939980591
    s21_decimal decimal = {{0x755E612F, 0xC5D1A4F, 0xD853A88B, 0x1A0000}};
    // 669
    s21_decimal decimal_check = {{0x29D, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok656) {
    // -669.49898886995994641939980591
    s21_decimal decimal = {{0x755E612F, 0xC5D1A4F, 0xD853A88B, 0x801A0000}};
    // -669
    s21_decimal decimal_check = {{0x29D, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok657) {
    // -6092.3308664774034440886232630
    s21_decimal decimal = {{0xF3D12636, 0x77B7CB4C, 0xC4DA946C, 0x80190000}};
    // -6092
    s21_decimal decimal_check = {{0x17CC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok658) {
    // 6092.3308664774034440886232630
    s21_decimal decimal = {{0xF3D12636, 0x77B7CB4C, 0xC4DA946C, 0x190000}};
    // 6092
    s21_decimal decimal_check = {{0x17CC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok659) {
    // 7.3308626447132754810257659671
    s21_decimal decimal = {{0x727DD717, 0xCBA4B49B, 0xECDF797A, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok660) {
    // -7.3308626447132754810257659671
    s21_decimal decimal = {{0x727DD717, 0xCBA4B49B, 0xECDF797A, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok661) {
    // -6776551568.5317859585487300628
    s21_decimal decimal = {{0x78E06814, 0x47F6A96C, 0xDAF6521E, 0x80130000}};
    // -6776551568
    s21_decimal decimal_check = {{0x93E9F890, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok662) {
    // 6776551568.5317859585487300628
    s21_decimal decimal = {{0x78E06814, 0x47F6A96C, 0xDAF6521E, 0x130000}};
    // 6776551568
    s21_decimal decimal_check = {{0x93E9F890, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok663) {
    // -490920879618299036.42046162229
    s21_decimal decimal = {{0x70BAE535, 0xD680AB, 0x9EA005FD, 0x800B0000}};
    // -490920879618299036
    s21_decimal decimal_check = {{0x6278949C, 0x6D019F0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok664) {
    // 490920879618299036.42046162229
    s21_decimal decimal = {{0x70BAE535, 0xD680AB, 0x9EA005FD, 0xB0000}};
    // 490920879618299036
    s21_decimal decimal_check = {{0x6278949C, 0x6D019F0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok665) {
    // 418519.65900186993559238168259
    s21_decimal decimal = {{0xC95D4EC3, 0x96AE73CE, 0x873B2281, 0x170000}};
    // 418519
    s21_decimal decimal_check = {{0x662D7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok666) {
    // -418519.65900186993559238168259
    s21_decimal decimal = {{0xC95D4EC3, 0x96AE73CE, 0x873B2281, 0x80170000}};
    // -418519
    s21_decimal decimal_check = {{0x662D7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok667) {
    // -12799325835502.09058233571374
    s21_decimal decimal = {{0x3E72D82E, 0x62D14AF1, 0x422BC44, 0x800E0000}};
    // -12799325835502
    s21_decimal decimal_check = {{0x134510EE, 0xBA4, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok668) {
    // 12799325835502.09058233571374
    s21_decimal decimal = {{0x3E72D82E, 0x62D14AF1, 0x422BC44, 0xE0000}};
    // 12799325835502
    s21_decimal decimal_check = {{0x134510EE, 0xBA4, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok669) {
    // 639014677925522157116.79858410
    s21_decimal decimal = {{0x4E5146EA, 0x48EDE85B, 0xCE7A0E26, 0x80000}};
    // 639014677925522157116
    s21_decimal decimal_check = {{0xAB65AE3C, 0xA41C2FED, 0x22, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok670) {
    // -639014677925522157116.79858410
    s21_decimal decimal = {{0x4E5146EA, 0x48EDE85B, 0xCE7A0E26, 0x80080000}};
    // -639014677925522157116
    s21_decimal decimal_check = {{0xAB65AE3C, 0xA41C2FED, 0x22, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok671) {
    // -33437506.844226338394141262477
    s21_decimal decimal = {{0xA0C2828D, 0x26844875, 0x6C0ADB7E, 0x80150000}};
    // -33437506
    s21_decimal decimal_check = {{0x1FE3742, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok672) {
    // 33437506.844226338394141262477
    s21_decimal decimal = {{0xA0C2828D, 0x26844875, 0x6C0ADB7E, 0x150000}};
    // 33437506
    s21_decimal decimal_check = {{0x1FE3742, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok673) {
    // 4591498185885.0881268918081533
    s21_decimal decimal = {{0x3E2D57FD, 0xCC8607C, 0x945BFB9A, 0x100000}};
    // 4591498185885
    s21_decimal decimal_check = {{0xA9E4C9D, 0x42D, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok674) {
    // -4591498185885.0881268918081533
    s21_decimal decimal = {{0x3E2D57FD, 0xCC8607C, 0x945BFB9A, 0x80100000}};
    // -4591498185885
    s21_decimal decimal_check = {{0xA9E4C9D, 0x42D, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok675) {
    // -13121974844916277405564666.93
    s21_decimal decimal = {{0x2FC89A05, 0x2BB90399, 0x43D6CA0, 0x80020000}};
    // -13121974844916277405564666
    s21_decimal decimal_check = {{0xF8CC3EFA, 0xAE8468FE, 0xADAAF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok676) {
    // 13121974844916277405564666.93
    s21_decimal decimal = {{0x2FC89A05, 0x2BB90399, 0x43D6CA0, 0x20000}};
    // 13121974844916277405564666
    s21_decimal decimal_check = {{0xF8CC3EFA, 0xAE8468FE, 0xADAAF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok677) {
    // -2221.322513557956430871784232
    s21_decimal decimal = {{0x2FE5EB28, 0xBFE0DCED, 0x72D6F56, 0x80180000}};
    // -2221
    s21_decimal decimal_check = {{0x8AD, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok678) {
    // 2221.322513557956430871784232
    s21_decimal decimal = {{0x2FE5EB28, 0xBFE0DCED, 0x72D6F56, 0x180000}};
    // 2221
    s21_decimal decimal_check = {{0x8AD, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok679) {
    // 653456132440757327185.54664238
    s21_decimal decimal = {{0x1CC34D2E, 0x14CB0840, 0xD3249FD8, 0x80000}};
    // 653456132440757327185
    s21_decimal decimal_check = {{0xBFF35551, 0x6C868A4B, 0x23, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok680) {
    // -653456132440757327185.54664238
    s21_decimal decimal = {{0x1CC34D2E, 0x14CB0840, 0xD3249FD8, 0x80080000}};
    // -653456132440757327185
    s21_decimal decimal_check = {{0xBFF35551, 0x6C868A4B, 0x23, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok681) {
    // 6777771957235710374.3788666856
    s21_decimal decimal = {{0x2C4C4FE8, 0x52B9854B, 0xDB006A64, 0xA0000}};
    // 6777771957235710374
    s21_decimal decimal_check = {{0x57A379A6, 0x5E0F7BAF, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok682) {
    // -6777771957235710374.3788666856
    s21_decimal decimal = {{0x2C4C4FE8, 0x52B9854B, 0xDB006A64, 0x800A0000}};
    // -6777771957235710374
    s21_decimal decimal_check = {{0x57A379A6, 0x5E0F7BAF, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok683) {
    // -2776669915102.2558436887214991
    s21_decimal decimal = {{0x3235BB8F, 0x1D50197A, 0x59B81341, 0x80100000}};
    // -2776669915102
    s21_decimal decimal_check = {{0x7E6C87DE, 0x286, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok684) {
    // 2776669915102.2558436887214991
    s21_decimal decimal = {{0x3235BB8F, 0x1D50197A, 0x59B81341, 0x100000}};
    // 2776669915102
    s21_decimal decimal_check = {{0x7E6C87DE, 0x286, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok685) {
    // -30618812476725193253111.517897
    s21_decimal decimal = {{0x20A8D2C9, 0x4F4109DF, 0x62EF49BE, 0x80060000}};
    // -30618812476725193253111
    s21_decimal decimal_check = {{0xF92A0F7, 0xD961EA29, 0x67B, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok686) {
    // 30618812476725193253111.517897
    s21_decimal decimal = {{0x20A8D2C9, 0x4F4109DF, 0x62EF49BE, 0x60000}};
    // 30618812476725193253111
    s21_decimal decimal_check = {{0xF92A0F7, 0xD961EA29, 0x67B, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok687) {
    // 558.33475983411236410614508086
    s21_decimal decimal = {{0xBA3E6A36, 0xEE7C59A0, 0xB4685E6D, 0x1A0000}};
    // 558
    s21_decimal decimal_check = {{0x22E, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok688) {
    // -558.33475983411236410614508086
    s21_decimal decimal = {{0xBA3E6A36, 0xEE7C59A0, 0xB4685E6D, 0x801A0000}};
    // -558
    s21_decimal decimal_check = {{0x22E, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok689) {
    // -71660254397762908223403168176
    s21_decimal decimal = {{0x98FF91B0, 0xF2280971, 0xE78BF91E, 0x80000000}};
    // -71660254397762908223403168176
    s21_decimal decimal_check = {{0x98FF91B0, 0xF2280971, 0xE78BF91E, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok690) {
    // 71660254397762908223403168176
    s21_decimal decimal = {{0x98FF91B0, 0xF2280971, 0xE78BF91E, 0x0}};
    // 71660254397762908223403168176
    s21_decimal decimal_check = {{0x98FF91B0, 0xF2280971, 0xE78BF91E, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok691) {
    // 30427511881243070508693342.418
    s21_decimal decimal = {{0x298E48D2, 0x3FA50510, 0x62510C44, 0x30000}};
    // 30427511881243070508693342
    s21_decimal decimal_check = {{0xA5EDF75E, 0xB9685B65, 0x192B46, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok692) {
    // -30427511881243070508693342.418
    s21_decimal decimal = {{0x298E48D2, 0x3FA50510, 0x62510C44, 0x80030000}};
    // -30427511881243070508693342
    s21_decimal decimal_check = {{0xA5EDF75E, 0xB9685B65, 0x192B46, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok693) {
    // -163104597470335471.3074879214
    s21_decimal decimal = {{0x4F84CAEE, 0x75B91AA6, 0x5452B6B, 0x800A0000}};
    // -163104597470335471
    s21_decimal decimal_check = {{0x6973D1EF, 0x24376C4, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok694) {
    // 163104597470335471.3074879214
    s21_decimal decimal = {{0x4F84CAEE, 0x75B91AA6, 0x5452B6B, 0xA0000}};
    // 163104597470335471
    s21_decimal decimal_check = {{0x6973D1EF, 0x24376C4, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok695) {
    // -70250400195227407579637.849948
    s21_decimal decimal = {{0x28B79F5C, 0x7B69CAB8, 0xE2FDC4E1, 0x80060000}};
    // -70250400195227407579637
    s21_decimal decimal_check = {{0xB9D779F5, 0x4825B6FC, 0xEE0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok696) {
    // 70250400195227407579637.849948
    s21_decimal decimal = {{0x28B79F5C, 0x7B69CAB8, 0xE2FDC4E1, 0x60000}};
    // 70250400195227407579637
    s21_decimal decimal_check = {{0xB9D779F5, 0x4825B6FC, 0xEE0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok697) {
    // 2359.6227154142364818929945668
    s21_decimal decimal = {{0x32DD0C44, 0x262D6547, 0x4C3E5775, 0x190000}};
    // 2359
    s21_decimal decimal_check = {{0x937, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok698) {
    // -2359.6227154142364818929945668
    s21_decimal decimal = {{0x32DD0C44, 0x262D6547, 0x4C3E5775, 0x80190000}};
    // -2359
    s21_decimal decimal_check = {{0x937, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok699) {
    // -518397134194869847726801761.8
    s21_decimal decimal = {{0x1897A1D2, 0x8D5AEE1D, 0x10C014A1, 0x80010000}};
    // -518397134194869847726801761
    s21_decimal decimal_check = {{0xB5A8C361, 0xF48917CF, 0x1ACCEDC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok700) {
    // 518397134194869847726801761.8
    s21_decimal decimal = {{0x1897A1D2, 0x8D5AEE1D, 0x10C014A1, 0x10000}};
    // 518397134194869847726801761
    s21_decimal decimal_check = {{0xB5A8C361, 0xF48917CF, 0x1ACCEDC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok701) {
    // -5214.0619486047282857402175741
    s21_decimal decimal = {{0x602410FD, 0x135C2056, 0xA879B5A6, 0x80190000}};
    // -5214
    s21_decimal decimal_check = {{0x145E, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok702) {
    // 5214.0619486047282857402175741
    s21_decimal decimal = {{0x602410FD, 0x135C2056, 0xA879B5A6, 0x190000}};
    // 5214
    s21_decimal decimal_check = {{0x145E, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok703) {
    // -64811897596.546902901850471836
    s21_decimal decimal = {{0x75DD7D9C, 0xDAAD7DE4, 0xD16B2528, 0x80120000}};
    // -64811897596
    s21_decimal decimal_check = {{0x171712FC, 0xF, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok704) {
    // 64811897596.546902901850471836
    s21_decimal decimal = {{0x75DD7D9C, 0xDAAD7DE4, 0xD16B2528, 0x120000}};
    // 64811897596
    s21_decimal decimal_check = {{0x171712FC, 0xF, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok705) {
    // -32767818046962421889141326401
    s21_decimal decimal = {{0xB88C4241, 0xB4D14FB7, 0x69E0E75F, 0x80000000}};
    // -32767818046962421889141326401
    s21_decimal decimal_check = {{0xB88C4241, 0xB4D14FB7, 0x69E0E75F, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok706) {
    // 32767818046962421889141326401
    s21_decimal decimal = {{0xB88C4241, 0xB4D14FB7, 0x69E0E75F, 0x0}};
    // 32767818046962421889141326401
    s21_decimal decimal_check = {{0xB88C4241, 0xB4D14FB7, 0x69E0E75F, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok707) {
    // 72078.459803798247964870365923
    s21_decimal decimal = {{0xFA52D2E3, 0x6F321B1F, 0xE8E5E78F, 0x180000}};
    // 72078
    s21_decimal decimal_check = {{0x1198E, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok708) {
    // -72078.459803798247964870365923
    s21_decimal decimal = {{0xFA52D2E3, 0x6F321B1F, 0xE8E5E78F, 0x80180000}};
    // -72078
    s21_decimal decimal_check = {{0x1198E, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok709) {
    // -288529960.9409851511048781000
    s21_decimal decimal = {{0xBD7C3CC8, 0x3D5C1F3A, 0x952A9F5, 0x80130000}};
    // -288529960
    s21_decimal decimal_check = {{0x11329E28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok710) {
    // 288529960.9409851511048781000
    s21_decimal decimal = {{0xBD7C3CC8, 0x3D5C1F3A, 0x952A9F5, 0x130000}};
    // 288529960
    s21_decimal decimal_check = {{0x11329E28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok711) {
    // -6512696567951679.9269047546320
    s21_decimal decimal = {{0xC51EB1D0, 0xDB2617FF, 0xD26FC36B, 0x800D0000}};
    // -6512696567951679
    s21_decimal decimal_check = {{0x5576713F, 0x172343, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok712) {
    // 6512696567951679.9269047546320
    s21_decimal decimal = {{0xC51EB1D0, 0xDB2617FF, 0xD26FC36B, 0xD0000}};
    // 6512696567951679
    s21_decimal decimal_check = {{0x5576713F, 0x172343, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok713) {
    // 2997460725542835.0989785565376
    s21_decimal decimal = {{0x195708C0, 0x49690B14, 0x60DA69FB, 0xD0000}};
    // 2997460725542835
    s21_decimal decimal_check = {{0xB5C62FB3, 0xAA62C, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok714) {
    // -2997460725542835.0989785565376
    s21_decimal decimal = {{0x195708C0, 0x49690B14, 0x60DA69FB, 0x800D0000}};
    // -2997460725542835
    s21_decimal decimal_check = {{0xB5C62FB3, 0xAA62C, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok715) {
    // 5568314832795173751154.5521644
    s21_decimal decimal = {{0x4F51C5EC, 0x665F612B, 0xB3EC054F, 0x70000}};
    // 5568314832795173751154
    s21_decimal decimal_check = {{0x16F98972, 0xDBE4463B, 0x12D, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok716) {
    // -5568314832795173751154.5521644
    s21_decimal decimal = {{0x4F51C5EC, 0x665F612B, 0xB3EC054F, 0x80070000}};
    // -5568314832795173751154
    s21_decimal decimal_check = {{0x16F98972, 0xDBE4463B, 0x12D, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok717) {
    // -3403123.9367181193428137130129
    s21_decimal decimal = {{0x9E7BB891, 0xB6AEBA9B, 0x6DF5FB3E, 0x80160000}};
    // -3403123
    s21_decimal decimal_check = {{0x33ED73, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok718) {
    // 3403123.9367181193428137130129
    s21_decimal decimal = {{0x9E7BB891, 0xB6AEBA9B, 0x6DF5FB3E, 0x160000}};
    // 3403123
    s21_decimal decimal_check = {{0x33ED73, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok719) {
    // 451634.52455214742800468742955
    s21_decimal decimal = {{0x543F132B, 0x71C97C1E, 0x91EE550F, 0x170000}};
    // 451634
    s21_decimal decimal_check = {{0x6E432, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok720) {
    // -451634.52455214742800468742955
    s21_decimal decimal = {{0x543F132B, 0x71C97C1E, 0x91EE550F, 0x80170000}};
    // -451634
    s21_decimal decimal_check = {{0x6E432, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok721) {
    // 1490998677579897640118240.6975
    s21_decimal decimal = {{0x5161B93F, 0xB3DB99E2, 0x302D4082, 0x40000}};
    // 1490998677579897640118240
    s21_decimal decimal_check = {{0xE0E7E0, 0x3344E95C, 0x13BBB, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok722) {
    // -1490998677579897640118240.6975
    s21_decimal decimal = {{0x5161B93F, 0xB3DB99E2, 0x302D4082, 0x80040000}};
    // -1490998677579897640118240
    s21_decimal decimal_check = {{0xE0E7E0, 0x3344E95C, 0x13BBB, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok723) {
    // 5241291889812627736862527.6698
    s21_decimal decimal = {{0xBE9CA71A, 0xC8628124, 0xA95AF34A, 0x40000}};
    // 5241291889812627736862527
    s21_decimal decimal_check = {{0xD9359F3F, 0xAF8600, 0x455E3, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok724) {
    // -5241291889812627736862527.6698
    s21_decimal decimal = {{0xBE9CA71A, 0xC8628124, 0xA95AF34A, 0x80040000}};
    // -5241291889812627736862527
    s21_decimal decimal_check = {{0xD9359F3F, 0xAF8600, 0x455E3, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok725) {
    // 3312796670785.118212338696569
    s21_decimal decimal = {{0xFA5B4179, 0x5F970C9D, 0xAB447FB, 0xF0000}};
    // 3312796670785
    s21_decimal decimal_check = {{0x52119B41, 0x303, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok726) {
    // -3312796670785.118212338696569
    s21_decimal decimal = {{0xFA5B4179, 0x5F970C9D, 0xAB447FB, 0x800F0000}};
    // -3312796670785
    s21_decimal decimal_check = {{0x52119B41, 0x303, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok727) {
    // -6619845547998.3525679341504489
    s21_decimal decimal = {{0x311C07E9, 0x544373B8, 0xD5E61436, 0x80100000}};
    // -6619845547998
    s21_decimal decimal_check = {{0x4D8AD7DE, 0x605, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok728) {
    // 6619845547998.3525679341504489
    s21_decimal decimal = {{0x311C07E9, 0x544373B8, 0xD5E61436, 0x100000}};
    // 6619845547998
    s21_decimal decimal_check = {{0x4D8AD7DE, 0x605, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok729) {
    // 2022298153810923643453.0476204
    s21_decimal decimal = {{0xFE0020AC, 0xE33AAD94, 0x41580EE9, 0x70000}};
    // 2022298153810923643453
    s21_decimal decimal_check = {{0xD460623D, 0xA106504B, 0x6D, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok730) {
    // -2022298153810923643453.0476204
    s21_decimal decimal = {{0xFE0020AC, 0xE33AAD94, 0x41580EE9, 0x80070000}};
    // -2022298153810923643453
    s21_decimal decimal_check = {{0xD460623D, 0xA106504B, 0x6D, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok731) {
    // -38.452696079476379048697321387
    s21_decimal decimal = {{0x26E6D7AB, 0x5D5A2039, 0x7C3F531F, 0x801B0000}};
    // -38
    s21_decimal decimal_check = {{0x26, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok732) {
    // 38.452696079476379048697321387
    s21_decimal decimal = {{0x26E6D7AB, 0x5D5A2039, 0x7C3F531F, 0x1B0000}};
    // 38
    s21_decimal decimal_check = {{0x26, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok733) {
    // -7621923436951698444645885904.9
    s21_decimal decimal = {{0xCDF90E29, 0x6E3C43CC, 0xF64712AE, 0x80010000}};
    // -7621923436951698444645885904
    s21_decimal decimal_check = {{0x1498E7D0, 0x716C6D2E, 0x18A0B511, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok734) {
    // 7621923436951698444645885904.9
    s21_decimal decimal = {{0xCDF90E29, 0x6E3C43CC, 0xF64712AE, 0x10000}};
    // 7621923436951698444645885904
    s21_decimal decimal_check = {{0x1498E7D0, 0x716C6D2E, 0x18A0B511, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok735) {
    // 0.792749284472214610041103266
    s21_decimal decimal = {{0xBE4FE3A2, 0xD2B3BF13, 0x28FBF30, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok736) {
    // -0.792749284472214610041103266
    s21_decimal decimal = {{0xBE4FE3A2, 0xD2B3BF13, 0x28FBF30, 0x801B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok737) {
    // -7.0952381376664915616674713068
    s21_decimal decimal = {{0x58818DEC, 0x947B5CEB, 0xE5426F2D, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok738) {
    // 7.0952381376664915616674713068
    s21_decimal decimal = {{0x58818DEC, 0x947B5CEB, 0xE5426F2D, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok739) {
    // -3490641.3018778271549536115518
    s21_decimal decimal = {{0x580C9B3E, 0x6E8973C6, 0x70C9E879, 0x80160000}};
    // -3490641
    s21_decimal decimal_check = {{0x354351, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok740) {
    // 3490641.3018778271549536115518
    s21_decimal decimal = {{0x580C9B3E, 0x6E8973C6, 0x70C9E879, 0x160000}};
    // 3490641
    s21_decimal decimal_check = {{0x354351, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok741) {
    // -7547238403396035183138739700.3
    s21_decimal decimal = {{0x5D21DB8B, 0x9D2F78D6, 0xF3DD4AF8, 0x80010000}};
    // -7547238403396035183138739700
    s21_decimal decimal_check = {{0x6FB695F4, 0xA9518C15, 0x1862EDE5, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok742) {
    // 7547238403396035183138739700.3
    s21_decimal decimal = {{0x5D21DB8B, 0x9D2F78D6, 0xF3DD4AF8, 0x10000}};
    // 7547238403396035183138739700
    s21_decimal decimal_check = {{0x6FB695F4, 0xA9518C15, 0x1862EDE5, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok743) {
    // -2125791772.2201402719835446513
    s21_decimal decimal = {{0x18BEDCF1, 0xD8B082B7, 0x44B0232C, 0x80130000}};
    // -2125791772
    s21_decimal decimal_check = {{0x7EB5021C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok744) {
    // 2125791772.2201402719835446513
    s21_decimal decimal = {{0x18BEDCF1, 0xD8B082B7, 0x44B0232C, 0x130000}};
    // 2125791772
    s21_decimal decimal_check = {{0x7EB5021C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok745) {
    // 40341322520994539500065286694
    s21_decimal decimal = {{0xADDC6A26, 0xE8F80241, 0x82598F53, 0x0}};
    // 40341322520994539500065286694
    s21_decimal decimal_check = {{0xADDC6A26, 0xE8F80241, 0x82598F53, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok746) {
    // -40341322520994539500065286694
    s21_decimal decimal = {{0xADDC6A26, 0xE8F80241, 0x82598F53, 0x80000000}};
    // -40341322520994539500065286694
    s21_decimal decimal_check = {{0xADDC6A26, 0xE8F80241, 0x82598F53, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok747) {
    // -5697424131360859746448160.7926
    s21_decimal decimal = {{0xED8530F6, 0x6579E286, 0xB817FCE2, 0x80040000}};
    // -5697424131360859746448160
    s21_decimal decimal_check = {{0xAD3B320, 0xFB2569EE, 0x4B679, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok748) {
    // 5697424131360859746448160.7926
    s21_decimal decimal = {{0xED8530F6, 0x6579E286, 0xB817FCE2, 0x40000}};
    // 5697424131360859746448160
    s21_decimal decimal_check = {{0xAD3B320, 0xFB2569EE, 0x4B679, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok749) {
    // 9928648.005441794227915721348
    s21_decimal decimal = {{0x4B00A84, 0xDE005F6C, 0x2014C8FE, 0x150000}};
    // 9928648
    s21_decimal decimal_check = {{0x977FC8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok750) {
    // -9928648.005441794227915721348
    s21_decimal decimal = {{0x4B00A84, 0xDE005F6C, 0x2014C8FE, 0x80150000}};
    // -9928648
    s21_decimal decimal_check = {{0x977FC8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok751) {
    // -444142204931712008136708060.70
    s21_decimal decimal = {{0x8F2F3236, 0x65B6DB02, 0x8F829505, 0x80020000}};
    // -444142204931712008136708060
    s21_decimal decimal_check = {{0xAA644FDC, 0x2C898230, 0x16F62C5, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok752) {
    // 444142204931712008136708060.70
    s21_decimal decimal = {{0x8F2F3236, 0x65B6DB02, 0x8F829505, 0x20000}};
    // 444142204931712008136708060
    s21_decimal decimal_check = {{0xAA644FDC, 0x2C898230, 0x16F62C5, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok753) {
    // 782.62817221302704332559028526
    s21_decimal decimal = {{0xA1B112E, 0xCF018751, 0xFCE17C2E, 0x1A0000}};
    // 782
    s21_decimal decimal_check = {{0x30E, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok754) {
    // -782.62817221302704332559028526
    s21_decimal decimal = {{0xA1B112E, 0xCF018751, 0xFCE17C2E, 0x801A0000}};
    // -782
    s21_decimal decimal_check = {{0x30E, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok755) {
    // -51714093494967484281.674582092
    s21_decimal decimal = {{0x2C14C84C, 0xC4A2FC48, 0xA718E541, 0x80090000}};
    // -51714093494967484281
    s21_decimal decimal_check = {{0x68E03F79, 0xCDAD5E0A, 0x2, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok756) {
    // 51714093494967484281.674582092
    s21_decimal decimal = {{0x2C14C84C, 0xC4A2FC48, 0xA718E541, 0x90000}};
    // 51714093494967484281
    s21_decimal decimal_check = {{0x68E03F79, 0xCDAD5E0A, 0x2, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok757) {
    // -27691798873592260757.375191260
    s21_decimal decimal = {{0x2F8488DC, 0xF063874D, 0x597A1E80, 0x80090000}};
    // -27691798873592260757
    s21_decimal decimal_check = {{0xAC076895, 0x804D085B, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok758) {
    // 27691798873592260757.375191260
    s21_decimal decimal = {{0x2F8488DC, 0xF063874D, 0x597A1E80, 0x90000}};
    // 27691798873592260757
    s21_decimal decimal_check = {{0xAC076895, 0x804D085B, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok759) {
    // 555786062048161132199.24957442
    s21_decimal decimal = {{0x6909902, 0x8C8499D0, 0xB3958BA7, 0x80000}};
    // 555786062048161132199
    s21_decimal decimal_check = {{0x85DB6EA7, 0x2114BEC0, 0x1E, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok760) {
    // -555786062048161132199.24957442
    s21_decimal decimal = {{0x6909902, 0x8C8499D0, 0xB3958BA7, 0x80080000}};
    // -555786062048161132199
    s21_decimal decimal_check = {{0x85DB6EA7, 0x2114BEC0, 0x1E, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok761) {
    // 4931461741.295765725699368032
    s21_decimal decimal = {{0xD69FE460, 0xAC0ECDD5, 0xFEF35A4, 0x120000}};
    // 4931461741
    s21_decimal decimal_check = {{0x25F0226D, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok762) {
    // -4931461741.295765725699368032
    s21_decimal decimal = {{0xD69FE460, 0xAC0ECDD5, 0xFEF35A4, 0x80120000}};
    // -4931461741
    s21_decimal decimal_check = {{0x25F0226D, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok763) {
    // 6199987028113.0039382721295233
    s21_decimal decimal = {{0xD6DF381, 0xA18B5999, 0xC8551736, 0x100000}};
    // 6199987028113
    s21_decimal decimal_check = {{0x8C064091, 0x5A3, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok764) {
    // -6199987028113.0039382721295233
    s21_decimal decimal = {{0xD6DF381, 0xA18B5999, 0xC8551736, 0x80100000}};
    // -6199987028113
    s21_decimal decimal_check = {{0x8C064091, 0x5A3, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok765) {
    // 3674479464.0114703411671671754
    s21_decimal decimal = {{0xA97723CA, 0xD13AD628, 0x76BA94EC, 0x130000}};
    // 3674479464
    s21_decimal decimal_check = {{0xDB041B68, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok766) {
    // -3674479464.0114703411671671754
    s21_decimal decimal = {{0xA97723CA, 0xD13AD628, 0x76BA94EC, 0x80130000}};
    // -3674479464
    s21_decimal decimal_check = {{0xDB041B68, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok767) {
    // 18545965274341890763667.304074
    s21_decimal decimal = {{0xFB886E8A, 0x1069852B, 0x3BECDCE8, 0x60000}};
    // 18545965274341890763667
    s21_decimal decimal_check = {{0x5656AB93, 0x60F88447, 0x3ED, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok768) {
    // -18545965274341890763667.304074
    s21_decimal decimal = {{0xFB886E8A, 0x1069852B, 0x3BECDCE8, 0x80060000}};
    // -18545965274341890763667
    s21_decimal decimal_check = {{0x5656AB93, 0x60F88447, 0x3ED, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok769) {
    // 296418771450.42881017504901009
    s21_decimal decimal = {{0xCAC0A791, 0xDC35C892, 0x5FC72FA3, 0x110000}};
    // 296418771450
    s21_decimal decimal_check = {{0x3EF81FA, 0x45, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok770) {
    // -296418771450.42881017504901009
    s21_decimal decimal = {{0xCAC0A791, 0xDC35C892, 0x5FC72FA3, 0x80110000}};
    // -296418771450
    s21_decimal decimal_check = {{0x3EF81FA, 0x45, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok771) {
    // 42180649950451149187743664715
    s21_decimal decimal = {{0x98E2CA4B, 0xA80F782F, 0x884B040F, 0x0}};
    // 42180649950451149187743664715
    s21_decimal decimal_check = {{0x98E2CA4B, 0xA80F782F, 0x884B040F, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok772) {
    // -42180649950451149187743664715
    s21_decimal decimal = {{0x98E2CA4B, 0xA80F782F, 0x884B040F, 0x80000000}};
    // -42180649950451149187743664715
    s21_decimal decimal_check = {{0x98E2CA4B, 0xA80F782F, 0x884B040F, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok773) {
    // 5807606082786.8646448485818561
    s21_decimal decimal = {{0xFEF2E0C1, 0xF2E2E26D, 0xBBA7643D, 0x100000}};
    // 5807606082786
    s21_decimal decimal_check = {{0x304C2CE2, 0x548, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok774) {
    // -5807606082786.8646448485818561
    s21_decimal decimal = {{0xFEF2E0C1, 0xF2E2E26D, 0xBBA7643D, 0x80100000}};
    // -5807606082786
    s21_decimal decimal_check = {{0x304C2CE2, 0x548, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok775) {
    // -32068606267.331647399284410311
    s21_decimal decimal = {{0xC91387C7, 0x2E609E0D, 0x679E8785, 0x80120000}};
    // -32068606267
    s21_decimal decimal_check = {{0x7770193B, 0x7, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok776) {
    // 32068606267.331647399284410311
    s21_decimal decimal = {{0xC91387C7, 0x2E609E0D, 0x679E8785, 0x120000}};
    // 32068606267
    s21_decimal decimal_check = {{0x7770193B, 0x7, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok777) {
    // 75485358599655252236246.620038
    s21_decimal decimal = {{0xE77E9786, 0x3ACC3D8B, 0xF3E80671, 0x60000}};
    // 75485358599655252236246
    s21_decimal decimal_check = {{0xE53717D6, 0x11CA0BD0, 0xFFC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok778) {
    // -75485358599655252236246.620038
    s21_decimal decimal = {{0xE77E9786, 0x3ACC3D8B, 0xF3E80671, 0x80060000}};
    // -75485358599655252236246
    s21_decimal decimal_check = {{0xE53717D6, 0x11CA0BD0, 0xFFC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok779) {
    // 508729132206.95204986732898591
    s21_decimal decimal = {{0x12DB691F, 0xBA2AB3A5, 0xA4611667, 0x110000}};
    // 508729132206
    s21_decimal decimal_check = {{0x729E84AE, 0x76, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok780) {
    // -508729132206.95204986732898591
    s21_decimal decimal = {{0x12DB691F, 0xBA2AB3A5, 0xA4611667, 0x80110000}};
    // -508729132206
    s21_decimal decimal_check = {{0x729E84AE, 0x76, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}


Suite * truncate_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("truncate_suite1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_truncate_ok1);
    tcase_add_test(tc_core, test_truncate_ok2);
    tcase_add_test(tc_core, test_truncate_ok3);
    tcase_add_test(tc_core, test_truncate_ok4);
    tcase_add_test(tc_core, test_truncate_ok5);
    tcase_add_test(tc_core, test_truncate_ok6);
    tcase_add_test(tc_core, test_truncate_ok7);
    tcase_add_test(tc_core, test_truncate_ok8);
    tcase_add_test(tc_core, test_truncate_ok9);
    tcase_add_test(tc_core, test_truncate_ok10);
    tcase_add_test(tc_core, test_truncate_ok11);
    tcase_add_test(tc_core, test_truncate_ok12);
    tcase_add_test(tc_core, test_truncate_ok13);
    tcase_add_test(tc_core, test_truncate_ok14);
    tcase_add_test(tc_core, test_truncate_ok15);
    tcase_add_test(tc_core, test_truncate_ok16);
    tcase_add_test(tc_core, test_truncate_ok17);
    tcase_add_test(tc_core, test_truncate_ok18);
    tcase_add_test(tc_core, test_truncate_ok19);
    tcase_add_test(tc_core, test_truncate_ok20);
    tcase_add_test(tc_core, test_truncate_ok21);
    tcase_add_test(tc_core, test_truncate_ok22);
    tcase_add_test(tc_core, test_truncate_ok23);
    tcase_add_test(tc_core, test_truncate_ok24);
    tcase_add_test(tc_core, test_truncate_ok25);
    tcase_add_test(tc_core, test_truncate_ok26);
    tcase_add_test(tc_core, test_truncate_ok27);
    tcase_add_test(tc_core, test_truncate_ok28);
    tcase_add_test(tc_core, test_truncate_ok29);
    tcase_add_test(tc_core, test_truncate_ok30);
    tcase_add_test(tc_core, test_truncate_ok31);
    tcase_add_test(tc_core, test_truncate_ok32);
    tcase_add_test(tc_core, test_truncate_ok33);
    tcase_add_test(tc_core, test_truncate_ok34);
    tcase_add_test(tc_core, test_truncate_ok35);
    tcase_add_test(tc_core, test_truncate_ok36);
    tcase_add_test(tc_core, test_truncate_ok37);
    tcase_add_test(tc_core, test_truncate_ok38);
    tcase_add_test(tc_core, test_truncate_ok39);
    tcase_add_test(tc_core, test_truncate_ok40);
    tcase_add_test(tc_core, test_truncate_ok41);
    tcase_add_test(tc_core, test_truncate_ok42);
    tcase_add_test(tc_core, test_truncate_ok43);
    tcase_add_test(tc_core, test_truncate_ok44);
    tcase_add_test(tc_core, test_truncate_ok45);
    tcase_add_test(tc_core, test_truncate_ok46);
    tcase_add_test(tc_core, test_truncate_ok47);
    tcase_add_test(tc_core, test_truncate_ok48);
    tcase_add_test(tc_core, test_truncate_ok49);
    tcase_add_test(tc_core, test_truncate_ok50);
    tcase_add_test(tc_core, test_truncate_ok51);
    tcase_add_test(tc_core, test_truncate_ok52);
    tcase_add_test(tc_core, test_truncate_ok53);
    tcase_add_test(tc_core, test_truncate_ok54);
    tcase_add_test(tc_core, test_truncate_ok55);
    tcase_add_test(tc_core, test_truncate_ok56);
    tcase_add_test(tc_core, test_truncate_ok57);
    tcase_add_test(tc_core, test_truncate_ok58);
    tcase_add_test(tc_core, test_truncate_ok59);
    tcase_add_test(tc_core, test_truncate_ok60);
    tcase_add_test(tc_core, test_truncate_ok61);
    tcase_add_test(tc_core, test_truncate_ok62);
    tcase_add_test(tc_core, test_truncate_ok63);
    tcase_add_test(tc_core, test_truncate_ok64);
    tcase_add_test(tc_core, test_truncate_ok65);
    tcase_add_test(tc_core, test_truncate_ok66);
    tcase_add_test(tc_core, test_truncate_ok67);
    tcase_add_test(tc_core, test_truncate_ok68);
    tcase_add_test(tc_core, test_truncate_ok69);
    tcase_add_test(tc_core, test_truncate_ok70);
    tcase_add_test(tc_core, test_truncate_ok71);
    tcase_add_test(tc_core, test_truncate_ok72);
    tcase_add_test(tc_core, test_truncate_ok73);
    tcase_add_test(tc_core, test_truncate_ok74);
    tcase_add_test(tc_core, test_truncate_ok75);
    tcase_add_test(tc_core, test_truncate_ok76);
    tcase_add_test(tc_core, test_truncate_ok77);
    tcase_add_test(tc_core, test_truncate_ok78);
    tcase_add_test(tc_core, test_truncate_ok79);
    tcase_add_test(tc_core, test_truncate_ok80);
    tcase_add_test(tc_core, test_truncate_ok81);
    tcase_add_test(tc_core, test_truncate_ok82);
    tcase_add_test(tc_core, test_truncate_ok83);
    tcase_add_test(tc_core, test_truncate_ok84);
    tcase_add_test(tc_core, test_truncate_ok85);
    tcase_add_test(tc_core, test_truncate_ok86);
    tcase_add_test(tc_core, test_truncate_ok87);
    tcase_add_test(tc_core, test_truncate_ok88);
    tcase_add_test(tc_core, test_truncate_ok89);
    tcase_add_test(tc_core, test_truncate_ok90);
    tcase_add_test(tc_core, test_truncate_ok91);
    tcase_add_test(tc_core, test_truncate_ok92);
    tcase_add_test(tc_core, test_truncate_ok93);
    tcase_add_test(tc_core, test_truncate_ok94);
    tcase_add_test(tc_core, test_truncate_ok95);
    tcase_add_test(tc_core, test_truncate_ok96);
    tcase_add_test(tc_core, test_truncate_ok97);
    tcase_add_test(tc_core, test_truncate_ok98);
    tcase_add_test(tc_core, test_truncate_ok99);
    tcase_add_test(tc_core, test_truncate_ok100);
    tcase_add_test(tc_core, test_truncate_ok101);
    tcase_add_test(tc_core, test_truncate_ok102);
    tcase_add_test(tc_core, test_truncate_ok103);
    tcase_add_test(tc_core, test_truncate_ok104);
    tcase_add_test(tc_core, test_truncate_ok105);
    tcase_add_test(tc_core, test_truncate_ok106);
    tcase_add_test(tc_core, test_truncate_ok107);
    tcase_add_test(tc_core, test_truncate_ok108);
    tcase_add_test(tc_core, test_truncate_ok109);
    tcase_add_test(tc_core, test_truncate_ok110);
    tcase_add_test(tc_core, test_truncate_ok111);
    tcase_add_test(tc_core, test_truncate_ok112);
    tcase_add_test(tc_core, test_truncate_ok113);
    tcase_add_test(tc_core, test_truncate_ok114);
    tcase_add_test(tc_core, test_truncate_ok115);
    tcase_add_test(tc_core, test_truncate_ok116);
    tcase_add_test(tc_core, test_truncate_ok117);
    tcase_add_test(tc_core, test_truncate_ok118);
    tcase_add_test(tc_core, test_truncate_ok119);
    tcase_add_test(tc_core, test_truncate_ok120);
    tcase_add_test(tc_core, test_truncate_ok121);
    tcase_add_test(tc_core, test_truncate_ok122);
    tcase_add_test(tc_core, test_truncate_ok123);
    tcase_add_test(tc_core, test_truncate_ok124);
    tcase_add_test(tc_core, test_truncate_ok125);
    tcase_add_test(tc_core, test_truncate_ok126);
    tcase_add_test(tc_core, test_truncate_ok127);
    tcase_add_test(tc_core, test_truncate_ok128);
    tcase_add_test(tc_core, test_truncate_ok129);
    tcase_add_test(tc_core, test_truncate_ok130);
    tcase_add_test(tc_core, test_truncate_ok131);
    tcase_add_test(tc_core, test_truncate_ok132);
    tcase_add_test(tc_core, test_truncate_ok133);
    tcase_add_test(tc_core, test_truncate_ok134);
    tcase_add_test(tc_core, test_truncate_ok135);
    tcase_add_test(tc_core, test_truncate_ok136);
    tcase_add_test(tc_core, test_truncate_ok137);
    tcase_add_test(tc_core, test_truncate_ok138);
    tcase_add_test(tc_core, test_truncate_ok139);
    tcase_add_test(tc_core, test_truncate_ok140);
    tcase_add_test(tc_core, test_truncate_ok141);
    tcase_add_test(tc_core, test_truncate_ok142);
    tcase_add_test(tc_core, test_truncate_ok143);
    tcase_add_test(tc_core, test_truncate_ok144);
    tcase_add_test(tc_core, test_truncate_ok145);
    tcase_add_test(tc_core, test_truncate_ok146);
    tcase_add_test(tc_core, test_truncate_ok147);
    tcase_add_test(tc_core, test_truncate_ok148);
    tcase_add_test(tc_core, test_truncate_ok149);
    tcase_add_test(tc_core, test_truncate_ok150);
    tcase_add_test(tc_core, test_truncate_ok151);
    tcase_add_test(tc_core, test_truncate_ok152);
    tcase_add_test(tc_core, test_truncate_ok153);
    tcase_add_test(tc_core, test_truncate_ok154);
    tcase_add_test(tc_core, test_truncate_ok155);
    tcase_add_test(tc_core, test_truncate_ok156);
    tcase_add_test(tc_core, test_truncate_ok157);
    tcase_add_test(tc_core, test_truncate_ok158);
    tcase_add_test(tc_core, test_truncate_ok159);
    tcase_add_test(tc_core, test_truncate_ok160);
    tcase_add_test(tc_core, test_truncate_ok161);
    tcase_add_test(tc_core, test_truncate_ok162);
    tcase_add_test(tc_core, test_truncate_ok163);
    tcase_add_test(tc_core, test_truncate_ok164);
    tcase_add_test(tc_core, test_truncate_ok165);
    tcase_add_test(tc_core, test_truncate_ok166);
    tcase_add_test(tc_core, test_truncate_ok167);
    tcase_add_test(tc_core, test_truncate_ok168);
    tcase_add_test(tc_core, test_truncate_ok169);
    tcase_add_test(tc_core, test_truncate_ok170);
    tcase_add_test(tc_core, test_truncate_ok171);
    tcase_add_test(tc_core, test_truncate_ok172);
    tcase_add_test(tc_core, test_truncate_ok173);
    tcase_add_test(tc_core, test_truncate_ok174);
    tcase_add_test(tc_core, test_truncate_ok175);
    tcase_add_test(tc_core, test_truncate_ok176);
    tcase_add_test(tc_core, test_truncate_ok177);
    tcase_add_test(tc_core, test_truncate_ok178);
    tcase_add_test(tc_core, test_truncate_ok179);
    tcase_add_test(tc_core, test_truncate_ok180);
    tcase_add_test(tc_core, test_truncate_ok181);
    tcase_add_test(tc_core, test_truncate_ok182);
    tcase_add_test(tc_core, test_truncate_ok183);
    tcase_add_test(tc_core, test_truncate_ok184);
    tcase_add_test(tc_core, test_truncate_ok185);
    tcase_add_test(tc_core, test_truncate_ok186);
    tcase_add_test(tc_core, test_truncate_ok187);
    tcase_add_test(tc_core, test_truncate_ok188);
    tcase_add_test(tc_core, test_truncate_ok189);
    tcase_add_test(tc_core, test_truncate_ok190);
    tcase_add_test(tc_core, test_truncate_ok191);
    tcase_add_test(tc_core, test_truncate_ok192);
    tcase_add_test(tc_core, test_truncate_ok193);
    tcase_add_test(tc_core, test_truncate_ok194);
    tcase_add_test(tc_core, test_truncate_ok195);
    tcase_add_test(tc_core, test_truncate_ok196);
    tcase_add_test(tc_core, test_truncate_ok197);
    tcase_add_test(tc_core, test_truncate_ok198);
    tcase_add_test(tc_core, test_truncate_ok199);
    tcase_add_test(tc_core, test_truncate_ok200);
    tcase_add_test(tc_core, test_truncate_ok201);
    tcase_add_test(tc_core, test_truncate_ok202);
    tcase_add_test(tc_core, test_truncate_ok203);
    tcase_add_test(tc_core, test_truncate_ok204);
    tcase_add_test(tc_core, test_truncate_ok205);
    tcase_add_test(tc_core, test_truncate_ok206);
    tcase_add_test(tc_core, test_truncate_ok207);
    tcase_add_test(tc_core, test_truncate_ok208);
    tcase_add_test(tc_core, test_truncate_ok209);
    tcase_add_test(tc_core, test_truncate_ok210);
    tcase_add_test(tc_core, test_truncate_ok211);
    tcase_add_test(tc_core, test_truncate_ok212);
    tcase_add_test(tc_core, test_truncate_ok213);
    tcase_add_test(tc_core, test_truncate_ok214);
    tcase_add_test(tc_core, test_truncate_ok215);
    tcase_add_test(tc_core, test_truncate_ok216);
    tcase_add_test(tc_core, test_truncate_ok217);
    tcase_add_test(tc_core, test_truncate_ok218);
    tcase_add_test(tc_core, test_truncate_ok219);
    tcase_add_test(tc_core, test_truncate_ok220);
    tcase_add_test(tc_core, test_truncate_ok221);
    tcase_add_test(tc_core, test_truncate_ok222);
    tcase_add_test(tc_core, test_truncate_ok223);
    tcase_add_test(tc_core, test_truncate_ok224);
    tcase_add_test(tc_core, test_truncate_ok225);
    tcase_add_test(tc_core, test_truncate_ok226);
    tcase_add_test(tc_core, test_truncate_ok227);
    tcase_add_test(tc_core, test_truncate_ok228);
    tcase_add_test(tc_core, test_truncate_ok229);
    tcase_add_test(tc_core, test_truncate_ok230);
    tcase_add_test(tc_core, test_truncate_ok231);
    tcase_add_test(tc_core, test_truncate_ok232);
    tcase_add_test(tc_core, test_truncate_ok233);
    tcase_add_test(tc_core, test_truncate_ok234);
    tcase_add_test(tc_core, test_truncate_ok235);
    tcase_add_test(tc_core, test_truncate_ok236);
    tcase_add_test(tc_core, test_truncate_ok237);
    tcase_add_test(tc_core, test_truncate_ok238);
    tcase_add_test(tc_core, test_truncate_ok239);
    tcase_add_test(tc_core, test_truncate_ok240);
    tcase_add_test(tc_core, test_truncate_ok241);
    tcase_add_test(tc_core, test_truncate_ok242);
    tcase_add_test(tc_core, test_truncate_ok243);
    tcase_add_test(tc_core, test_truncate_ok244);
    tcase_add_test(tc_core, test_truncate_ok245);
    tcase_add_test(tc_core, test_truncate_ok246);
    tcase_add_test(tc_core, test_truncate_ok247);
    tcase_add_test(tc_core, test_truncate_ok248);
    tcase_add_test(tc_core, test_truncate_ok249);
    tcase_add_test(tc_core, test_truncate_ok250);
    tcase_add_test(tc_core, test_truncate_ok251);
    tcase_add_test(tc_core, test_truncate_ok252);
    tcase_add_test(tc_core, test_truncate_ok253);
    tcase_add_test(tc_core, test_truncate_ok254);
    tcase_add_test(tc_core, test_truncate_ok255);
    tcase_add_test(tc_core, test_truncate_ok256);
    tcase_add_test(tc_core, test_truncate_ok257);
    tcase_add_test(tc_core, test_truncate_ok258);
    tcase_add_test(tc_core, test_truncate_ok259);
    tcase_add_test(tc_core, test_truncate_ok260);
    tcase_add_test(tc_core, test_truncate_ok261);
    tcase_add_test(tc_core, test_truncate_ok262);
    tcase_add_test(tc_core, test_truncate_ok263);
    tcase_add_test(tc_core, test_truncate_ok264);
    tcase_add_test(tc_core, test_truncate_ok265);
    tcase_add_test(tc_core, test_truncate_ok266);
    tcase_add_test(tc_core, test_truncate_ok267);
    tcase_add_test(tc_core, test_truncate_ok268);
    tcase_add_test(tc_core, test_truncate_ok269);
    tcase_add_test(tc_core, test_truncate_ok270);
    tcase_add_test(tc_core, test_truncate_ok271);
    tcase_add_test(tc_core, test_truncate_ok272);
    tcase_add_test(tc_core, test_truncate_ok273);
    tcase_add_test(tc_core, test_truncate_ok274);
    tcase_add_test(tc_core, test_truncate_ok275);
    tcase_add_test(tc_core, test_truncate_ok276);
    tcase_add_test(tc_core, test_truncate_ok277);
    tcase_add_test(tc_core, test_truncate_ok278);
    tcase_add_test(tc_core, test_truncate_ok279);
    tcase_add_test(tc_core, test_truncate_ok280);
    tcase_add_test(tc_core, test_truncate_ok281);
    tcase_add_test(tc_core, test_truncate_ok282);
    tcase_add_test(tc_core, test_truncate_ok283);
    tcase_add_test(tc_core, test_truncate_ok284);
    tcase_add_test(tc_core, test_truncate_ok285);
    tcase_add_test(tc_core, test_truncate_ok286);
    tcase_add_test(tc_core, test_truncate_ok287);
    tcase_add_test(tc_core, test_truncate_ok288);
    tcase_add_test(tc_core, test_truncate_ok289);
    tcase_add_test(tc_core, test_truncate_ok290);
    tcase_add_test(tc_core, test_truncate_ok291);
    tcase_add_test(tc_core, test_truncate_ok292);
    tcase_add_test(tc_core, test_truncate_ok293);
    tcase_add_test(tc_core, test_truncate_ok294);
    tcase_add_test(tc_core, test_truncate_ok295);
    tcase_add_test(tc_core, test_truncate_ok296);
    tcase_add_test(tc_core, test_truncate_ok297);
    tcase_add_test(tc_core, test_truncate_ok298);
    tcase_add_test(tc_core, test_truncate_ok299);
    tcase_add_test(tc_core, test_truncate_ok300);
    tcase_add_test(tc_core, test_truncate_ok301);
    tcase_add_test(tc_core, test_truncate_ok302);
    tcase_add_test(tc_core, test_truncate_ok303);
    tcase_add_test(tc_core, test_truncate_ok304);
    tcase_add_test(tc_core, test_truncate_ok305);
    tcase_add_test(tc_core, test_truncate_ok306);
    tcase_add_test(tc_core, test_truncate_ok307);
    tcase_add_test(tc_core, test_truncate_ok308);
    tcase_add_test(tc_core, test_truncate_ok309);
    tcase_add_test(tc_core, test_truncate_ok310);
    tcase_add_test(tc_core, test_truncate_ok311);
    tcase_add_test(tc_core, test_truncate_ok312);
    tcase_add_test(tc_core, test_truncate_ok313);
    tcase_add_test(tc_core, test_truncate_ok314);
    tcase_add_test(tc_core, test_truncate_ok315);
    tcase_add_test(tc_core, test_truncate_ok316);
    tcase_add_test(tc_core, test_truncate_ok317);
    tcase_add_test(tc_core, test_truncate_ok318);
    tcase_add_test(tc_core, test_truncate_ok319);
    tcase_add_test(tc_core, test_truncate_ok320);
    tcase_add_test(tc_core, test_truncate_ok321);
    tcase_add_test(tc_core, test_truncate_ok322);
    tcase_add_test(tc_core, test_truncate_ok323);
    tcase_add_test(tc_core, test_truncate_ok324);
    tcase_add_test(tc_core, test_truncate_ok325);
    tcase_add_test(tc_core, test_truncate_ok326);
    tcase_add_test(tc_core, test_truncate_ok327);
    tcase_add_test(tc_core, test_truncate_ok328);
    tcase_add_test(tc_core, test_truncate_ok329);
    tcase_add_test(tc_core, test_truncate_ok330);
    tcase_add_test(tc_core, test_truncate_ok331);
    tcase_add_test(tc_core, test_truncate_ok332);
    tcase_add_test(tc_core, test_truncate_ok333);
    tcase_add_test(tc_core, test_truncate_ok334);
    tcase_add_test(tc_core, test_truncate_ok335);
    tcase_add_test(tc_core, test_truncate_ok336);
    tcase_add_test(tc_core, test_truncate_ok337);
    tcase_add_test(tc_core, test_truncate_ok338);
    tcase_add_test(tc_core, test_truncate_ok339);
    tcase_add_test(tc_core, test_truncate_ok340);
    tcase_add_test(tc_core, test_truncate_ok341);
    tcase_add_test(tc_core, test_truncate_ok342);
    tcase_add_test(tc_core, test_truncate_ok343);
    tcase_add_test(tc_core, test_truncate_ok344);
    tcase_add_test(tc_core, test_truncate_ok345);
    tcase_add_test(tc_core, test_truncate_ok346);
    tcase_add_test(tc_core, test_truncate_ok347);
    tcase_add_test(tc_core, test_truncate_ok348);
    tcase_add_test(tc_core, test_truncate_ok349);
    tcase_add_test(tc_core, test_truncate_ok350);
    tcase_add_test(tc_core, test_truncate_ok351);
    tcase_add_test(tc_core, test_truncate_ok352);
    tcase_add_test(tc_core, test_truncate_ok353);
    tcase_add_test(tc_core, test_truncate_ok354);
    tcase_add_test(tc_core, test_truncate_ok355);
    tcase_add_test(tc_core, test_truncate_ok356);
    tcase_add_test(tc_core, test_truncate_ok357);
    tcase_add_test(tc_core, test_truncate_ok358);
    tcase_add_test(tc_core, test_truncate_ok359);
    tcase_add_test(tc_core, test_truncate_ok360);
    tcase_add_test(tc_core, test_truncate_ok361);
    tcase_add_test(tc_core, test_truncate_ok362);
    tcase_add_test(tc_core, test_truncate_ok363);
    tcase_add_test(tc_core, test_truncate_ok364);
    tcase_add_test(tc_core, test_truncate_ok365);
    tcase_add_test(tc_core, test_truncate_ok366);
    tcase_add_test(tc_core, test_truncate_ok367);
    tcase_add_test(tc_core, test_truncate_ok368);
    tcase_add_test(tc_core, test_truncate_ok369);
    tcase_add_test(tc_core, test_truncate_ok370);
    tcase_add_test(tc_core, test_truncate_ok371);
    tcase_add_test(tc_core, test_truncate_ok372);
    tcase_add_test(tc_core, test_truncate_ok373);
    tcase_add_test(tc_core, test_truncate_ok374);
    tcase_add_test(tc_core, test_truncate_ok375);
    tcase_add_test(tc_core, test_truncate_ok376);
    tcase_add_test(tc_core, test_truncate_ok377);
    tcase_add_test(tc_core, test_truncate_ok378);
    tcase_add_test(tc_core, test_truncate_ok379);
    tcase_add_test(tc_core, test_truncate_ok380);
    tcase_add_test(tc_core, test_truncate_ok381);
    tcase_add_test(tc_core, test_truncate_ok382);
    tcase_add_test(tc_core, test_truncate_ok383);
    tcase_add_test(tc_core, test_truncate_ok384);
    tcase_add_test(tc_core, test_truncate_ok385);
    tcase_add_test(tc_core, test_truncate_ok386);
    tcase_add_test(tc_core, test_truncate_ok387);
    tcase_add_test(tc_core, test_truncate_ok388);
    tcase_add_test(tc_core, test_truncate_ok389);
    tcase_add_test(tc_core, test_truncate_ok390);
    tcase_add_test(tc_core, test_truncate_ok391);
    tcase_add_test(tc_core, test_truncate_ok392);
    tcase_add_test(tc_core, test_truncate_ok393);
    tcase_add_test(tc_core, test_truncate_ok394);
    tcase_add_test(tc_core, test_truncate_ok395);
    tcase_add_test(tc_core, test_truncate_ok396);
    tcase_add_test(tc_core, test_truncate_ok397);
    tcase_add_test(tc_core, test_truncate_ok398);
    tcase_add_test(tc_core, test_truncate_ok399);
    tcase_add_test(tc_core, test_truncate_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * truncate_suite2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("truncate_suite2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_truncate_ok401);
    tcase_add_test(tc_core, test_truncate_ok402);
    tcase_add_test(tc_core, test_truncate_ok403);
    tcase_add_test(tc_core, test_truncate_ok404);
    tcase_add_test(tc_core, test_truncate_ok405);
    tcase_add_test(tc_core, test_truncate_ok406);
    tcase_add_test(tc_core, test_truncate_ok407);
    tcase_add_test(tc_core, test_truncate_ok408);
    tcase_add_test(tc_core, test_truncate_ok409);
    tcase_add_test(tc_core, test_truncate_ok410);
    tcase_add_test(tc_core, test_truncate_ok411);
    tcase_add_test(tc_core, test_truncate_ok412);
    tcase_add_test(tc_core, test_truncate_ok413);
    tcase_add_test(tc_core, test_truncate_ok414);
    tcase_add_test(tc_core, test_truncate_ok415);
    tcase_add_test(tc_core, test_truncate_ok416);
    tcase_add_test(tc_core, test_truncate_ok417);
    tcase_add_test(tc_core, test_truncate_ok418);
    tcase_add_test(tc_core, test_truncate_ok419);
    tcase_add_test(tc_core, test_truncate_ok420);
    tcase_add_test(tc_core, test_truncate_ok421);
    tcase_add_test(tc_core, test_truncate_ok422);
    tcase_add_test(tc_core, test_truncate_ok423);
    tcase_add_test(tc_core, test_truncate_ok424);
    tcase_add_test(tc_core, test_truncate_ok425);
    tcase_add_test(tc_core, test_truncate_ok426);
    tcase_add_test(tc_core, test_truncate_ok427);
    tcase_add_test(tc_core, test_truncate_ok428);
    tcase_add_test(tc_core, test_truncate_ok429);
    tcase_add_test(tc_core, test_truncate_ok430);
    tcase_add_test(tc_core, test_truncate_ok431);
    tcase_add_test(tc_core, test_truncate_ok432);
    tcase_add_test(tc_core, test_truncate_ok433);
    tcase_add_test(tc_core, test_truncate_ok434);
    tcase_add_test(tc_core, test_truncate_ok435);
    tcase_add_test(tc_core, test_truncate_ok436);
    tcase_add_test(tc_core, test_truncate_ok437);
    tcase_add_test(tc_core, test_truncate_ok438);
    tcase_add_test(tc_core, test_truncate_ok439);
    tcase_add_test(tc_core, test_truncate_ok440);
    tcase_add_test(tc_core, test_truncate_ok441);
    tcase_add_test(tc_core, test_truncate_ok442);
    tcase_add_test(tc_core, test_truncate_ok443);
    tcase_add_test(tc_core, test_truncate_ok444);
    tcase_add_test(tc_core, test_truncate_ok445);
    tcase_add_test(tc_core, test_truncate_ok446);
    tcase_add_test(tc_core, test_truncate_ok447);
    tcase_add_test(tc_core, test_truncate_ok448);
    tcase_add_test(tc_core, test_truncate_ok449);
    tcase_add_test(tc_core, test_truncate_ok450);
    tcase_add_test(tc_core, test_truncate_ok451);
    tcase_add_test(tc_core, test_truncate_ok452);
    tcase_add_test(tc_core, test_truncate_ok453);
    tcase_add_test(tc_core, test_truncate_ok454);
    tcase_add_test(tc_core, test_truncate_ok455);
    tcase_add_test(tc_core, test_truncate_ok456);
    tcase_add_test(tc_core, test_truncate_ok457);
    tcase_add_test(tc_core, test_truncate_ok458);
    tcase_add_test(tc_core, test_truncate_ok459);
    tcase_add_test(tc_core, test_truncate_ok460);
    tcase_add_test(tc_core, test_truncate_ok461);
    tcase_add_test(tc_core, test_truncate_ok462);
    tcase_add_test(tc_core, test_truncate_ok463);
    tcase_add_test(tc_core, test_truncate_ok464);
    tcase_add_test(tc_core, test_truncate_ok465);
    tcase_add_test(tc_core, test_truncate_ok466);
    tcase_add_test(tc_core, test_truncate_ok467);
    tcase_add_test(tc_core, test_truncate_ok468);
    tcase_add_test(tc_core, test_truncate_ok469);
    tcase_add_test(tc_core, test_truncate_ok470);
    tcase_add_test(tc_core, test_truncate_ok471);
    tcase_add_test(tc_core, test_truncate_ok472);
    tcase_add_test(tc_core, test_truncate_ok473);
    tcase_add_test(tc_core, test_truncate_ok474);
    tcase_add_test(tc_core, test_truncate_ok475);
    tcase_add_test(tc_core, test_truncate_ok476);
    tcase_add_test(tc_core, test_truncate_ok477);
    tcase_add_test(tc_core, test_truncate_ok478);
    tcase_add_test(tc_core, test_truncate_ok479);
    tcase_add_test(tc_core, test_truncate_ok480);
    tcase_add_test(tc_core, test_truncate_ok481);
    tcase_add_test(tc_core, test_truncate_ok482);
    tcase_add_test(tc_core, test_truncate_ok483);
    tcase_add_test(tc_core, test_truncate_ok484);
    tcase_add_test(tc_core, test_truncate_ok485);
    tcase_add_test(tc_core, test_truncate_ok486);
    tcase_add_test(tc_core, test_truncate_ok487);
    tcase_add_test(tc_core, test_truncate_ok488);
    tcase_add_test(tc_core, test_truncate_ok489);
    tcase_add_test(tc_core, test_truncate_ok490);
    tcase_add_test(tc_core, test_truncate_ok491);
    tcase_add_test(tc_core, test_truncate_ok492);
    tcase_add_test(tc_core, test_truncate_ok493);
    tcase_add_test(tc_core, test_truncate_ok494);
    tcase_add_test(tc_core, test_truncate_ok495);
    tcase_add_test(tc_core, test_truncate_ok496);
    tcase_add_test(tc_core, test_truncate_ok497);
    tcase_add_test(tc_core, test_truncate_ok498);
    tcase_add_test(tc_core, test_truncate_ok499);
    tcase_add_test(tc_core, test_truncate_ok500);
    tcase_add_test(tc_core, test_truncate_ok501);
    tcase_add_test(tc_core, test_truncate_ok502);
    tcase_add_test(tc_core, test_truncate_ok503);
    tcase_add_test(tc_core, test_truncate_ok504);
    tcase_add_test(tc_core, test_truncate_ok505);
    tcase_add_test(tc_core, test_truncate_ok506);
    tcase_add_test(tc_core, test_truncate_ok507);
    tcase_add_test(tc_core, test_truncate_ok508);
    tcase_add_test(tc_core, test_truncate_ok509);
    tcase_add_test(tc_core, test_truncate_ok510);
    tcase_add_test(tc_core, test_truncate_ok511);
    tcase_add_test(tc_core, test_truncate_ok512);
    tcase_add_test(tc_core, test_truncate_ok513);
    tcase_add_test(tc_core, test_truncate_ok514);
    tcase_add_test(tc_core, test_truncate_ok515);
    tcase_add_test(tc_core, test_truncate_ok516);
    tcase_add_test(tc_core, test_truncate_ok517);
    tcase_add_test(tc_core, test_truncate_ok518);
    tcase_add_test(tc_core, test_truncate_ok519);
    tcase_add_test(tc_core, test_truncate_ok520);
    tcase_add_test(tc_core, test_truncate_ok521);
    tcase_add_test(tc_core, test_truncate_ok522);
    tcase_add_test(tc_core, test_truncate_ok523);
    tcase_add_test(tc_core, test_truncate_ok524);
    tcase_add_test(tc_core, test_truncate_ok525);
    tcase_add_test(tc_core, test_truncate_ok526);
    tcase_add_test(tc_core, test_truncate_ok527);
    tcase_add_test(tc_core, test_truncate_ok528);
    tcase_add_test(tc_core, test_truncate_ok529);
    tcase_add_test(tc_core, test_truncate_ok530);
    tcase_add_test(tc_core, test_truncate_ok531);
    tcase_add_test(tc_core, test_truncate_ok532);
    tcase_add_test(tc_core, test_truncate_ok533);
    tcase_add_test(tc_core, test_truncate_ok534);
    tcase_add_test(tc_core, test_truncate_ok535);
    tcase_add_test(tc_core, test_truncate_ok536);
    tcase_add_test(tc_core, test_truncate_ok537);
    tcase_add_test(tc_core, test_truncate_ok538);
    tcase_add_test(tc_core, test_truncate_ok539);
    tcase_add_test(tc_core, test_truncate_ok540);
    tcase_add_test(tc_core, test_truncate_ok541);
    tcase_add_test(tc_core, test_truncate_ok542);
    tcase_add_test(tc_core, test_truncate_ok543);
    tcase_add_test(tc_core, test_truncate_ok544);
    tcase_add_test(tc_core, test_truncate_ok545);
    tcase_add_test(tc_core, test_truncate_ok546);
    tcase_add_test(tc_core, test_truncate_ok547);
    tcase_add_test(tc_core, test_truncate_ok548);
    tcase_add_test(tc_core, test_truncate_ok549);
    tcase_add_test(tc_core, test_truncate_ok550);
    tcase_add_test(tc_core, test_truncate_ok551);
    tcase_add_test(tc_core, test_truncate_ok552);
    tcase_add_test(tc_core, test_truncate_ok553);
    tcase_add_test(tc_core, test_truncate_ok554);
    tcase_add_test(tc_core, test_truncate_ok555);
    tcase_add_test(tc_core, test_truncate_ok556);
    tcase_add_test(tc_core, test_truncate_ok557);
    tcase_add_test(tc_core, test_truncate_ok558);
    tcase_add_test(tc_core, test_truncate_ok559);
    tcase_add_test(tc_core, test_truncate_ok560);
    tcase_add_test(tc_core, test_truncate_ok561);
    tcase_add_test(tc_core, test_truncate_ok562);
    tcase_add_test(tc_core, test_truncate_ok563);
    tcase_add_test(tc_core, test_truncate_ok564);
    tcase_add_test(tc_core, test_truncate_ok565);
    tcase_add_test(tc_core, test_truncate_ok566);
    tcase_add_test(tc_core, test_truncate_ok567);
    tcase_add_test(tc_core, test_truncate_ok568);
    tcase_add_test(tc_core, test_truncate_ok569);
    tcase_add_test(tc_core, test_truncate_ok570);
    tcase_add_test(tc_core, test_truncate_ok571);
    tcase_add_test(tc_core, test_truncate_ok572);
    tcase_add_test(tc_core, test_truncate_ok573);
    tcase_add_test(tc_core, test_truncate_ok574);
    tcase_add_test(tc_core, test_truncate_ok575);
    tcase_add_test(tc_core, test_truncate_ok576);
    tcase_add_test(tc_core, test_truncate_ok577);
    tcase_add_test(tc_core, test_truncate_ok578);
    tcase_add_test(tc_core, test_truncate_ok579);
    tcase_add_test(tc_core, test_truncate_ok580);
    tcase_add_test(tc_core, test_truncate_ok581);
    tcase_add_test(tc_core, test_truncate_ok582);
    tcase_add_test(tc_core, test_truncate_ok583);
    tcase_add_test(tc_core, test_truncate_ok584);
    tcase_add_test(tc_core, test_truncate_ok585);
    tcase_add_test(tc_core, test_truncate_ok586);
    tcase_add_test(tc_core, test_truncate_ok587);
    tcase_add_test(tc_core, test_truncate_ok588);
    tcase_add_test(tc_core, test_truncate_ok589);
    tcase_add_test(tc_core, test_truncate_ok590);
    tcase_add_test(tc_core, test_truncate_ok591);
    tcase_add_test(tc_core, test_truncate_ok592);
    tcase_add_test(tc_core, test_truncate_ok593);
    tcase_add_test(tc_core, test_truncate_ok594);
    tcase_add_test(tc_core, test_truncate_ok595);
    tcase_add_test(tc_core, test_truncate_ok596);
    tcase_add_test(tc_core, test_truncate_ok597);
    tcase_add_test(tc_core, test_truncate_ok598);
    tcase_add_test(tc_core, test_truncate_ok599);
    tcase_add_test(tc_core, test_truncate_ok600);
    tcase_add_test(tc_core, test_truncate_ok601);
    tcase_add_test(tc_core, test_truncate_ok602);
    tcase_add_test(tc_core, test_truncate_ok603);
    tcase_add_test(tc_core, test_truncate_ok604);
    tcase_add_test(tc_core, test_truncate_ok605);
    tcase_add_test(tc_core, test_truncate_ok606);
    tcase_add_test(tc_core, test_truncate_ok607);
    tcase_add_test(tc_core, test_truncate_ok608);
    tcase_add_test(tc_core, test_truncate_ok609);
    tcase_add_test(tc_core, test_truncate_ok610);
    tcase_add_test(tc_core, test_truncate_ok611);
    tcase_add_test(tc_core, test_truncate_ok612);
    tcase_add_test(tc_core, test_truncate_ok613);
    tcase_add_test(tc_core, test_truncate_ok614);
    tcase_add_test(tc_core, test_truncate_ok615);
    tcase_add_test(tc_core, test_truncate_ok616);
    tcase_add_test(tc_core, test_truncate_ok617);
    tcase_add_test(tc_core, test_truncate_ok618);
    tcase_add_test(tc_core, test_truncate_ok619);
    tcase_add_test(tc_core, test_truncate_ok620);
    tcase_add_test(tc_core, test_truncate_ok621);
    tcase_add_test(tc_core, test_truncate_ok622);
    tcase_add_test(tc_core, test_truncate_ok623);
    tcase_add_test(tc_core, test_truncate_ok624);
    tcase_add_test(tc_core, test_truncate_ok625);
    tcase_add_test(tc_core, test_truncate_ok626);
    tcase_add_test(tc_core, test_truncate_ok627);
    tcase_add_test(tc_core, test_truncate_ok628);
    tcase_add_test(tc_core, test_truncate_ok629);
    tcase_add_test(tc_core, test_truncate_ok630);
    tcase_add_test(tc_core, test_truncate_ok631);
    tcase_add_test(tc_core, test_truncate_ok632);
    tcase_add_test(tc_core, test_truncate_ok633);
    tcase_add_test(tc_core, test_truncate_ok634);
    tcase_add_test(tc_core, test_truncate_ok635);
    tcase_add_test(tc_core, test_truncate_ok636);
    tcase_add_test(tc_core, test_truncate_ok637);
    tcase_add_test(tc_core, test_truncate_ok638);
    tcase_add_test(tc_core, test_truncate_ok639);
    tcase_add_test(tc_core, test_truncate_ok640);
    tcase_add_test(tc_core, test_truncate_ok641);
    tcase_add_test(tc_core, test_truncate_ok642);
    tcase_add_test(tc_core, test_truncate_ok643);
    tcase_add_test(tc_core, test_truncate_ok644);
    tcase_add_test(tc_core, test_truncate_ok645);
    tcase_add_test(tc_core, test_truncate_ok646);
    tcase_add_test(tc_core, test_truncate_ok647);
    tcase_add_test(tc_core, test_truncate_ok648);
    tcase_add_test(tc_core, test_truncate_ok649);
    tcase_add_test(tc_core, test_truncate_ok650);
    tcase_add_test(tc_core, test_truncate_ok651);
    tcase_add_test(tc_core, test_truncate_ok652);
    tcase_add_test(tc_core, test_truncate_ok653);
    tcase_add_test(tc_core, test_truncate_ok654);
    tcase_add_test(tc_core, test_truncate_ok655);
    tcase_add_test(tc_core, test_truncate_ok656);
    tcase_add_test(tc_core, test_truncate_ok657);
    tcase_add_test(tc_core, test_truncate_ok658);
    tcase_add_test(tc_core, test_truncate_ok659);
    tcase_add_test(tc_core, test_truncate_ok660);
    tcase_add_test(tc_core, test_truncate_ok661);
    tcase_add_test(tc_core, test_truncate_ok662);
    tcase_add_test(tc_core, test_truncate_ok663);
    tcase_add_test(tc_core, test_truncate_ok664);
    tcase_add_test(tc_core, test_truncate_ok665);
    tcase_add_test(tc_core, test_truncate_ok666);
    tcase_add_test(tc_core, test_truncate_ok667);
    tcase_add_test(tc_core, test_truncate_ok668);
    tcase_add_test(tc_core, test_truncate_ok669);
    tcase_add_test(tc_core, test_truncate_ok670);
    tcase_add_test(tc_core, test_truncate_ok671);
    tcase_add_test(tc_core, test_truncate_ok672);
    tcase_add_test(tc_core, test_truncate_ok673);
    tcase_add_test(tc_core, test_truncate_ok674);
    tcase_add_test(tc_core, test_truncate_ok675);
    tcase_add_test(tc_core, test_truncate_ok676);
    tcase_add_test(tc_core, test_truncate_ok677);
    tcase_add_test(tc_core, test_truncate_ok678);
    tcase_add_test(tc_core, test_truncate_ok679);
    tcase_add_test(tc_core, test_truncate_ok680);
    tcase_add_test(tc_core, test_truncate_ok681);
    tcase_add_test(tc_core, test_truncate_ok682);
    tcase_add_test(tc_core, test_truncate_ok683);
    tcase_add_test(tc_core, test_truncate_ok684);
    tcase_add_test(tc_core, test_truncate_ok685);
    tcase_add_test(tc_core, test_truncate_ok686);
    tcase_add_test(tc_core, test_truncate_ok687);
    tcase_add_test(tc_core, test_truncate_ok688);
    tcase_add_test(tc_core, test_truncate_ok689);
    tcase_add_test(tc_core, test_truncate_ok690);
    tcase_add_test(tc_core, test_truncate_ok691);
    tcase_add_test(tc_core, test_truncate_ok692);
    tcase_add_test(tc_core, test_truncate_ok693);
    tcase_add_test(tc_core, test_truncate_ok694);
    tcase_add_test(tc_core, test_truncate_ok695);
    tcase_add_test(tc_core, test_truncate_ok696);
    tcase_add_test(tc_core, test_truncate_ok697);
    tcase_add_test(tc_core, test_truncate_ok698);
    tcase_add_test(tc_core, test_truncate_ok699);
    tcase_add_test(tc_core, test_truncate_ok700);
    tcase_add_test(tc_core, test_truncate_ok701);
    tcase_add_test(tc_core, test_truncate_ok702);
    tcase_add_test(tc_core, test_truncate_ok703);
    tcase_add_test(tc_core, test_truncate_ok704);
    tcase_add_test(tc_core, test_truncate_ok705);
    tcase_add_test(tc_core, test_truncate_ok706);
    tcase_add_test(tc_core, test_truncate_ok707);
    tcase_add_test(tc_core, test_truncate_ok708);
    tcase_add_test(tc_core, test_truncate_ok709);
    tcase_add_test(tc_core, test_truncate_ok710);
    tcase_add_test(tc_core, test_truncate_ok711);
    tcase_add_test(tc_core, test_truncate_ok712);
    tcase_add_test(tc_core, test_truncate_ok713);
    tcase_add_test(tc_core, test_truncate_ok714);
    tcase_add_test(tc_core, test_truncate_ok715);
    tcase_add_test(tc_core, test_truncate_ok716);
    tcase_add_test(tc_core, test_truncate_ok717);
    tcase_add_test(tc_core, test_truncate_ok718);
    tcase_add_test(tc_core, test_truncate_ok719);
    tcase_add_test(tc_core, test_truncate_ok720);
    tcase_add_test(tc_core, test_truncate_ok721);
    tcase_add_test(tc_core, test_truncate_ok722);
    tcase_add_test(tc_core, test_truncate_ok723);
    tcase_add_test(tc_core, test_truncate_ok724);
    tcase_add_test(tc_core, test_truncate_ok725);
    tcase_add_test(tc_core, test_truncate_ok726);
    tcase_add_test(tc_core, test_truncate_ok727);
    tcase_add_test(tc_core, test_truncate_ok728);
    tcase_add_test(tc_core, test_truncate_ok729);
    tcase_add_test(tc_core, test_truncate_ok730);
    tcase_add_test(tc_core, test_truncate_ok731);
    tcase_add_test(tc_core, test_truncate_ok732);
    tcase_add_test(tc_core, test_truncate_ok733);
    tcase_add_test(tc_core, test_truncate_ok734);
    tcase_add_test(tc_core, test_truncate_ok735);
    tcase_add_test(tc_core, test_truncate_ok736);
    tcase_add_test(tc_core, test_truncate_ok737);
    tcase_add_test(tc_core, test_truncate_ok738);
    tcase_add_test(tc_core, test_truncate_ok739);
    tcase_add_test(tc_core, test_truncate_ok740);
    tcase_add_test(tc_core, test_truncate_ok741);
    tcase_add_test(tc_core, test_truncate_ok742);
    tcase_add_test(tc_core, test_truncate_ok743);
    tcase_add_test(tc_core, test_truncate_ok744);
    tcase_add_test(tc_core, test_truncate_ok745);
    tcase_add_test(tc_core, test_truncate_ok746);
    tcase_add_test(tc_core, test_truncate_ok747);
    tcase_add_test(tc_core, test_truncate_ok748);
    tcase_add_test(tc_core, test_truncate_ok749);
    tcase_add_test(tc_core, test_truncate_ok750);
    tcase_add_test(tc_core, test_truncate_ok751);
    tcase_add_test(tc_core, test_truncate_ok752);
    tcase_add_test(tc_core, test_truncate_ok753);
    tcase_add_test(tc_core, test_truncate_ok754);
    tcase_add_test(tc_core, test_truncate_ok755);
    tcase_add_test(tc_core, test_truncate_ok756);
    tcase_add_test(tc_core, test_truncate_ok757);
    tcase_add_test(tc_core, test_truncate_ok758);
    tcase_add_test(tc_core, test_truncate_ok759);
    tcase_add_test(tc_core, test_truncate_ok760);
    tcase_add_test(tc_core, test_truncate_ok761);
    tcase_add_test(tc_core, test_truncate_ok762);
    tcase_add_test(tc_core, test_truncate_ok763);
    tcase_add_test(tc_core, test_truncate_ok764);
    tcase_add_test(tc_core, test_truncate_ok765);
    tcase_add_test(tc_core, test_truncate_ok766);
    tcase_add_test(tc_core, test_truncate_ok767);
    tcase_add_test(tc_core, test_truncate_ok768);
    tcase_add_test(tc_core, test_truncate_ok769);
    tcase_add_test(tc_core, test_truncate_ok770);
    tcase_add_test(tc_core, test_truncate_ok771);
    tcase_add_test(tc_core, test_truncate_ok772);
    tcase_add_test(tc_core, test_truncate_ok773);
    tcase_add_test(tc_core, test_truncate_ok774);
    tcase_add_test(tc_core, test_truncate_ok775);
    tcase_add_test(tc_core, test_truncate_ok776);
    tcase_add_test(tc_core, test_truncate_ok777);
    tcase_add_test(tc_core, test_truncate_ok778);
    tcase_add_test(tc_core, test_truncate_ok779);
    tcase_add_test(tc_core, test_truncate_ok780);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * truncate_suite0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("truncate_suite0");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, from_truncate_fail1);
    tcase_add_test(tc_core, from_truncate_fail2);
    tcase_add_test(tc_core, from_truncate_fail3);
    tcase_add_test(tc_core, from_truncate_fail4);
    tcase_add_test(tc_core, from_truncate_fail5);
    tcase_add_test(tc_core, from_truncate_fail6);
    tcase_add_test(tc_core, from_truncate_fail7);
    tcase_add_test(tc_core, from_truncate_fail8);
    tcase_add_test(tc_core, from_truncate_fail9);

    suite_add_tcase(s, tc_core);
    return s;
}

void test_truncate(s21_decimal decimal, s21_decimal decimal_check) {
    s21_decimal result;

    #if defined(__DEBUG)
    s21_print_decimal_bits(decimal);
    s21_print_decimal_string(decimal);
    s21_print_decimal_bits(decimal_check);
    s21_print_decimal_string(decimal_check);
    #endif

    int res = s21_truncate(decimal, &result);

    #if defined(__DEBUG)
    s21_print_decimal_bits(result);
    s21_print_decimal_string(result);
    #endif

    ck_assert_int_eq(res, TEST_OTHER_OK);
    ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
    ck_assert_int_eq(s21_decimal_get_sign(result), s21_decimal_get_sign(decimal_check));
}
