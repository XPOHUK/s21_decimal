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
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok118) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok119) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok120) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok121) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok122) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok123) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok124) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok125) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok126) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok127) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok128) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok129) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok130) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok131) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok132) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok133) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok134) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok135) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok136) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok137) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok138) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok139) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok140) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok141) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok142) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok143) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok144) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok145) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok146) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok147) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok148) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok149) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok150) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok151) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok152) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok153) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok154) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok155) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok156) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok157) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok158) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok159) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok160) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok161) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok162) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok163) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok164) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok165) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok166) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok167) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok168) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok169) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok170) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok171) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok172) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok173) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok174) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok175) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok176) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok177) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok178) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok179) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok180) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok181) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok182) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok183) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok184) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok185) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok186) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok187) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok188) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok189) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok190) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok191) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok192) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok193) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok194) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok195) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok196) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok197) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok198) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok199) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok200) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok201) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok202) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok203) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok204) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok205) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok206) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok207) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok208) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok209) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok210) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok211) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok212) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok213) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok214) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok215) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok216) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok217) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok218) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok219) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok220) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok221) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok222) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok223) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok224) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok225) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok226) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok227) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok228) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok229) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok230) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok231) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok232) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok233) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok234) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok235) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok236) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok237) {
    // 5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok238) {
    // -5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok239) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok240) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok241) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok242) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok243) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok244) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok245) {
    // 5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok246) {
    // -5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok247) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok248) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok249) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok250) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok251) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok252) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok253) {
    // 5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok254) {
    // -5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok255) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok256) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok257) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok258) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok259) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok260) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok261) {
    // 5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok262) {
    // -5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok263) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok264) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok265) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok266) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok267) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok268) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok269) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok270) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok271) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok272) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok273) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok274) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok275) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok276) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok277) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok278) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok279) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok280) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok281) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    // 2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok282) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    // -2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok283) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    // 286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok284) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    // -286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok285) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    // 286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok286) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    // -286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok287) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok288) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok289) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok290) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok291) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919784798344
    s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok292) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919784798344
    s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok293) {
    // 2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok294) {
    // -2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok295) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok296) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok297) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok298) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok299) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok300) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok301) {
    // 2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok302) {
    // -2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok303) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok304) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok305) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // 26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok306) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok307) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450804312200
    s21_decimal decimal_check = {{0x8888888, 0x80000000, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok308) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450804312200
    s21_decimal decimal_check = {{0x8888888, 0x80000000, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok309) {
    // 2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok310) {
    // -2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok311) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok312) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok313) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    // 26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok314) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok315) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok316) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok317) {
    // 2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok318) {
    // -2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok319) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok320) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok321) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // 6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok322) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // -6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok323) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    // 614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok324) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    // -614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok325) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    // 6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok326) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    // -6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok327) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok328) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok329) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    // 6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok330) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // -6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok331) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    // 614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok332) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    // -614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok333) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    // 6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok334) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    // -6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok335) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok336) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok337) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    // 1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok338) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // -1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok339) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    // 143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok340) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    // -143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok341) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    // 143165
    s21_decimal decimal_check = {{0x22F3D, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok342) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    // -143165
    s21_decimal decimal_check = {{0x22F3D, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok343) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok344) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok345) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    // 18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok346) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    // -18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok347) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok348) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    // -1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok349) {
    // 184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000}};
    // 184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok350) {
    // -184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80080000}};
    // -184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok351) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok352) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok353) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    // 18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok354) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    // -18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok355) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok356) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    // -1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok357) {
    // 18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x90000}};
    // 18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok358) {
    // -18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80090000}};
    // -18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok359) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok360) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok361) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    // 18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok362) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    // -18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok363) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok364) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    // -1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok365) {
    // 1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xA0000}};
    // 1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok366) {
    // -1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800A0000}};
    // -1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok367) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok368) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok369) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    // 18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok370) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    // -18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok371) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok372) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    // -1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok373) {
    // 184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xB0000}};
    // 184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok374) {
    // -184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800B0000}};
    // -184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok375) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok376) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok377) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    // 4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok378) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    // -4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok379) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok380) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    // -429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok381) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok382) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    // -42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok383) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    // 429496
    s21_decimal decimal_check = {{0x68DB8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok384) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    // -429496
    s21_decimal decimal_check = {{0x68DB8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok385) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok386) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok387) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok388) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    // -42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok389) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    // 4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok390) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    // -4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok391) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok392) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    // -429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok393) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok394) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    // -42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok395) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    // 4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok396) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    // -4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok397) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok398) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok399) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok400) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    // -42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok401) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok402) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok403) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok404) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok405) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok406) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok407) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok408) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok409) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok410) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok411) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok412) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok413) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok414) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok415) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083577423462
    s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok416) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083577423462
    s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok417) {
    // 39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
    // 39614081266355
    s21_decimal decimal_check = {{0x5F3DF2B3, 0x2407, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok418) {
    // -39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
    // -39614081266355
    s21_decimal decimal_check = {{0x5F3DF2B3, 0x2407, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok419) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok420) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok421) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok422) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok423) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083362675097
    s21_decimal decimal_check = {{0x99999999, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok424) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083362675097
    s21_decimal decimal_check = {{0x99999999, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok425) {
    // 3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0xD0000}};
    // 3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok426) {
    // -3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x800D0000}};
    // -3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok427) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok428) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok429) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    // 39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok430) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok431) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879891945881
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok432) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879891945881
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok433) {
    // 39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0xC0000}};
    // 39614081257132168
    s21_decimal decimal_check = {{0x96F5088, 0x8CBCCC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok434) {
    // -39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x800C0000}};
    // -39614081257132168
    s21_decimal decimal_check = {{0x96F5088, 0x8CBCCC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok435) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok436) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok437) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    // 39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok438) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok439) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879677197516
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok440) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879677197516
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok441) {
    // 396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0xB0000}};
    // 396140812571321687
    s21_decimal decimal_check = {{0x5E592557, 0x57F5FF8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok442) {
    // -396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x800B0000}};
    // -396140812571321687
    s21_decimal decimal_check = {{0x5E592557, 0x57F5FF8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok443) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok444) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok445) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    // 9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok446) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    // -9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok447) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    // 922337203900225945
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok448) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    // -922337203900225945
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok449) {
    // 922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x70000}};
    // 922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok450) {
    // -922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80070000}};
    // -922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok451) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok452) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok453) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    // 9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok454) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    // -9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok455) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    // 922337203685477580
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok456) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    // -922337203685477580
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok457) {
    // 92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000}};
    // 92233720368
    s21_decimal decimal_check = {{0x798EE230, 0x15, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok458) {
    // -92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80080000}};
    // -92233720368
    s21_decimal decimal_check = {{0x798EE230, 0x15, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok459) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok460) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok461) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    // 2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok462) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    // -2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok463) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    // 214748364
    s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok464) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    // -214748364
    s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok465) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    // 21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok466) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    // -21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok467) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    // 214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok468) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    // -214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok469) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    // 21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok470) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    // -21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok471) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok472) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok473) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    // 156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok474) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok475) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok476) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok477) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    // 1560647
    s21_decimal decimal_check = {{0x17D047, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok478) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    // -1560647
    s21_decimal decimal_check = {{0x17D047, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok479) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok480) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok481) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    // 156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok482) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok483) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269529696665
    s21_decimal decimal_check = {{0x99999999, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok484) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269529696665
    s21_decimal decimal_check = {{0x99999999, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok485) {
    // 15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x40000}};
    // 15606476756221269529696
    s21_decimal decimal_check = {{0x27525460, 0x75F7320, 0x34E, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok486) {
    // -15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80040000}};
    // -15606476756221269529696
    s21_decimal decimal_check = {{0x27525460, 0x75F7320, 0x34E, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok487) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok488) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok489) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    // 156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok490) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok491) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    // 15606476752587603503068569
    s21_decimal decimal_check = {{0xCCD9B599, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok492) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603503068569
    s21_decimal decimal_check = {{0xCCD9B599, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok493) {
    // 1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0xB0000}};
    // 1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok494) {
    // -1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x800B0000}};
    // -1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok495) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok496) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok497) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    // 156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok498) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok499) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    // 15606476752587603502222540
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok500) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603502222540
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok501) {
    // 15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x130000}};
    // 15606476
    s21_decimal decimal_check = {{0xEE22CC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok502) {
    // -15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80130000}};
    // -15606476
    s21_decimal decimal_check = {{0xEE22CC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok503) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok504) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok505) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    // 36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok506) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    // -36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok507) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    // 3633666028320153
    s21_decimal decimal_check = {{0xCCD9B599, 0xCE8CC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok508) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    // -3633666028320153
    s21_decimal decimal_check = {{0xCCD9B599, 0xCE8CC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok509) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    // 363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok510) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    // -363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok511) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok512) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok513) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    // 36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok514) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    // -36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok515) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    // 3633666027474124
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCE8CC, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok516) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    // -3633666027474124
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCE8CC, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok517) {
    // 363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x20000}};
    // 363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok518) {
    // -363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80020000}};
    // -363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok519) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    // 363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok520) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    // -363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok521) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    // 36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok522) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    // -36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok523) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok524) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok525) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    // 8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok526) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    // -8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok527) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    // 846028
    s21_decimal decimal_check = {{0xCE8CC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok528) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    // -846028
    s21_decimal decimal_check = {{0xCE8CC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok529) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    // 84602
    s21_decimal decimal_check = {{0x14A7A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok530) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    // -84602
    s21_decimal decimal_check = {{0x14A7A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok531) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    // 8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok532) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    // -8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok533) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    // 84
    s21_decimal decimal_check = {{0x54, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok534) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    // -84
    s21_decimal decimal_check = {{0x54, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok535) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok536) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok537) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok538) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok539) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok540) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok541) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok542) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok543) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok544) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok545) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok546) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok547) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok548) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok549) {
    // 79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok550) {
    // -79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok551) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok552) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok553) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok554) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok555) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759352412936601
    s21_decimal decimal_check = {{0x19999999, 0x80000000, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok556) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759352412936601
    s21_decimal decimal_check = {{0x19999999, 0x80000000, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok557) {
    // 792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x110000}};
    // 792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok558) {
    // -792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80110000}};
    // -792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok559) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok560) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok561) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok562) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok563) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok564) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok565) {
    // 79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x120000}};
    // 79228162495
    s21_decimal decimal_check = {{0x725DD1BF, 0x12, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok566) {
    // -79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80120000}};
    // -79228162495
    s21_decimal decimal_check = {{0x725DD1BF, 0x12, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok567) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok568) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok569) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok570) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok571) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok572) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok573) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744073709551
    s21_decimal decimal_check = {{0x4BC6A7EF, 0x418937, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok574) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744073709551
    s21_decimal decimal_check = {{0x4BC6A7EF, 0x418937, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok575) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    // 184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok576) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    // -184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok577) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok578) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok579) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok580) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok581) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok582) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok583) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok584) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok585) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok586) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok587) {
    // 18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x90000}};
    // 18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok588) {
    // -18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80090000}};
    // -18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok589) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok590) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok591) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok592) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok593) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    // 4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok594) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    // -4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok595) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok596) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    // -429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok597) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok598) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    // -42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok599) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    // 42949
    s21_decimal decimal_check = {{0xA7C5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok600) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    // -42949
    s21_decimal decimal_check = {{0xA7C5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok601) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok602) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    // -42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok603) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok604) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok605) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok606) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok607) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok608) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok609) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok610) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok611) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok612) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok613) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok614) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok615) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok616) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok617) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok618) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok619) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok620) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok621) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok622) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok623) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    // 12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok624) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    // -12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok625) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    // 123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok626) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    // -123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok627) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    // 1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok628) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    // -1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok629) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    // 12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok630) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    // -12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok631) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    // 123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok632) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    // -123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok633) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    // 1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok634) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    // -1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok635) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    // 1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok636) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    // -1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok637) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    // 12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok638) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    // -12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok639) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok640) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok641) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok642) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok643) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok644) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok645) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    // 999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok646) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    // -999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok647) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    // 9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok648) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    // -9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok649) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    // 99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok650) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    // -99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok651) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    // 999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok652) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    // -999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok653) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    // 9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok654) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    // -9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok655) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    // 99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok656) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    // -99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok657) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    // 999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok658) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    // -999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok659) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    // 9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok660) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    // -9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok661) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok662) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok663) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok664) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok665) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok666) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok667) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok668) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok669) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok670) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok671) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok672) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok673) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok674) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok675) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok676) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok677) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok678) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok679) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok680) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok681) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok682) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok683) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok684) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok685) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok686) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok687) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok688) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok689) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok690) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok691) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok692) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok693) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok694) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok695) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok696) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok697) {
    // -4180611030418700364028644.2608
    s21_decimal decimal = {{0x6C7A7470, 0xBF97BD18, 0x87153434, 0x80040000}};
    // -4180611030418700364028644
    s21_decimal decimal_check = {{0x25E61AE4, 0x60C98345, 0x37547, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok698) {
    // 4180611030418700364028644.2608
    s21_decimal decimal = {{0x6C7A7470, 0xBF97BD18, 0x87153434, 0x40000}};
    // 4180611030418700364028644
    s21_decimal decimal_check = {{0x25E61AE4, 0x60C98345, 0x37547, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok699) {
    // -18500051708432759889568494.755
    s21_decimal decimal = {{0xB13474A3, 0xAB39A480, 0x3BC6E254, 0x80030000}};
    // -18500051708432759889568494
    s21_decimal decimal_check = {{0xF3E3A2EE, 0xD00B10CD, 0xF4D89, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok700) {
    // 18500051708432759889568494.755
    s21_decimal decimal = {{0xB13474A3, 0xAB39A480, 0x3BC6E254, 0x30000}};
    // 18500051708432759889568494
    s21_decimal decimal_check = {{0xF3E3A2EE, 0xD00B10CD, 0xF4D89, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok701) {
    // -45825.547021454991760560119695
    s21_decimal decimal = {{0x83FE5F8F, 0xCCC6B3A0, 0x94120109, 0x80180000}};
    // -45825
    s21_decimal decimal_check = {{0xB301, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok702) {
    // 45825.547021454991760560119695
    s21_decimal decimal = {{0x83FE5F8F, 0xCCC6B3A0, 0x94120109, 0x180000}};
    // 45825
    s21_decimal decimal_check = {{0xB301, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok703) {
    // -245623.07699487127859919216398
    s21_decimal decimal = {{0x649A5F0E, 0x73BAC86A, 0x4F5D76F8, 0x80170000}};
    // -245623
    s21_decimal decimal_check = {{0x3BF77, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok704) {
    // 245623.07699487127859919216398
    s21_decimal decimal = {{0x649A5F0E, 0x73BAC86A, 0x4F5D76F8, 0x170000}};
    // 245623
    s21_decimal decimal_check = {{0x3BF77, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok705) {
    // -705326109095510.98397091489020
    s21_decimal decimal = {{0x5E40E4FC, 0xF5E3A0F2, 0xE3E73552, 0x800E0000}};
    // -705326109095510
    s21_decimal decimal_check = {{0x882EF656, 0x2817D, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok706) {
    // 705326109095510.98397091489020
    s21_decimal decimal = {{0x5E40E4FC, 0xF5E3A0F2, 0xE3E73552, 0xE0000}};
    // 705326109095510
    s21_decimal decimal_check = {{0x882EF656, 0x2817D, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok707) {
    // 3163429532.7378598393222397605
    s21_decimal decimal = {{0xC1A9FEA5, 0xF318B79A, 0x66374699, 0x130000}};
    // 3163429532
    s21_decimal decimal_check = {{0xBC8E1A9C, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok708) {
    // -3163429532.7378598393222397605
    s21_decimal decimal = {{0xC1A9FEA5, 0xF318B79A, 0x66374699, 0x80130000}};
    // -3163429532
    s21_decimal decimal_check = {{0xBC8E1A9C, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok709) {
    // 48141.053243327282463657486786
    s21_decimal decimal = {{0xD390E9C2, 0x9B980E76, 0x9B8D588D, 0x180000}};
    // 48141
    s21_decimal decimal_check = {{0xBC0D, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok710) {
    // -48141.053243327282463657486786
    s21_decimal decimal = {{0xD390E9C2, 0x9B980E76, 0x9B8D588D, 0x80180000}};
    // -48141
    s21_decimal decimal_check = {{0xBC0D, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok711) {
    // -169396915328741059.43029752603
    s21_decimal decimal = {{0x2708A31B, 0xF0EDC95, 0x36BC2F36, 0x800B0000}};
    // -169396915328741059
    s21_decimal decimal_check = {{0xD4376EC3, 0x259D198, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok712) {
    // 169396915328741059.43029752603
    s21_decimal decimal = {{0x2708A31B, 0xF0EDC95, 0x36BC2F36, 0xB0000}};
    // 169396915328741059
    s21_decimal decimal_check = {{0xD4376EC3, 0x259D198, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok713) {
    // 752066.28270209882026778654303
    s21_decimal decimal = {{0x94D9765F, 0xCB271A87, 0xF30176FF, 0x170000}};
    // 752066
    s21_decimal decimal_check = {{0xB79C2, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok714) {
    // -752066.28270209882026778654303
    s21_decimal decimal = {{0x94D9765F, 0xCB271A87, 0xF30176FF, 0x80170000}};
    // -752066
    s21_decimal decimal_check = {{0xB79C2, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok715) {
    // 191249980285949583.38146042555
    s21_decimal decimal = {{0x380A02BB, 0x91B5EC1C, 0x3DCBD3DC, 0xB0000}};
    // 191249980285949583
    s21_decimal decimal_check = {{0x23E968F, 0x2A774D8, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok716) {
    // -191249980285949583.38146042555
    s21_decimal decimal = {{0x380A02BB, 0x91B5EC1C, 0x3DCBD3DC, 0x800B0000}};
    // -191249980285949583
    s21_decimal decimal_check = {{0x23E968F, 0x2A774D8, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok717) {
    // -8122713270871415.566335259951
    s21_decimal decimal = {{0xC440B52F, 0xBCDF3C90, 0x1A3EF370, 0x800C0000}};
    // -8122713270871415
    s21_decimal decimal_check = {{0x8F1F6577, 0x1CDB90, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok718) {
    // 8122713270871415.566335259951
    s21_decimal decimal = {{0xC440B52F, 0xBCDF3C90, 0x1A3EF370, 0xC0000}};
    // 8122713270871415
    s21_decimal decimal_check = {{0x8F1F6577, 0x1CDB90, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok719) {
    // 553726209260360621073.09964488
    s21_decimal decimal = {{0x1B47FCC8, 0x36132DBE, 0xB2EB2893, 0x80000}};
    // 553726209260360621073
    s21_decimal decimal_check = {{0x1B68DC11, 0x47EAD8E, 0x1E, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok720) {
    // -553726209260360621073.09964488
    s21_decimal decimal = {{0x1B47FCC8, 0x36132DBE, 0xB2EB2893, 0x80080000}};
    // -553726209260360621073
    s21_decimal decimal_check = {{0x1B68DC11, 0x47EAD8E, 0x1E, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok721) {
    // 6144438.6306769652680870133631
    s21_decimal decimal = {{0x5A78FF7F, 0xABABCC7, 0xC6899AE8, 0x160000}};
    // 6144438
    s21_decimal decimal_check = {{0x5DC1B6, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok722) {
    // -6144438.6306769652680870133631
    s21_decimal decimal = {{0x5A78FF7F, 0xABABCC7, 0xC6899AE8, 0x80160000}};
    // -6144438
    s21_decimal decimal_check = {{0x5DC1B6, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok723) {
    // -664525769876891273815356.2446
    s21_decimal decimal = {{0xB732814E, 0xAFC2A7AE, 0x1578D40D, 0x80040000}};
    // -664525769876891273815356
    s21_decimal decimal_check = {{0xD83C653C, 0x3A08E9B, 0x8CB8, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok724) {
    // 664525769876891273815356.2446
    s21_decimal decimal = {{0xB732814E, 0xAFC2A7AE, 0x1578D40D, 0x40000}};
    // 664525769876891273815356
    s21_decimal decimal_check = {{0xD83C653C, 0x3A08E9B, 0x8CB8, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok725) {
    // 7652806542293823926782422.0737
    s21_decimal decimal = {{0x6743A41, 0x62145339, 0xF7468833, 0x40000}};
    // 7652806542293823926782422
    s21_decimal decimal_check = {{0x7E6349D6, 0x7954056F, 0x6548B, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok726) {
    // -7652806542293823926782422.0737
    s21_decimal decimal = {{0x6743A41, 0x62145339, 0xF7468833, 0x80040000}};
    // -7652806542293823926782422
    s21_decimal decimal_check = {{0x7E6349D6, 0x7954056F, 0x6548B, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok727) {
    // 309894.41179695071703611740084
    s21_decimal decimal = {{0xDCC00FB4, 0x8E8E36AC, 0x6421DD6C, 0x170000}};
    // 309894
    s21_decimal decimal_check = {{0x4BA86, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok728) {
    // -309894.41179695071703611740084
    s21_decimal decimal = {{0xDCC00FB4, 0x8E8E36AC, 0x6421DD6C, 0x80170000}};
    // -309894
    s21_decimal decimal_check = {{0x4BA86, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok729) {
    // 74714523293440252950179.891243
    s21_decimal decimal = {{0x431E482B, 0x8C5FD6F4, 0xF16A67B7, 0x60000}};
    // 74714523293440252950179
    s21_decimal decimal_check = {{0xBAB9B6A3, 0x484CE8DF, 0xFD2, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok730) {
    // -74714523293440252950179.891243
    s21_decimal decimal = {{0x431E482B, 0x8C5FD6F4, 0xF16A67B7, 0x80060000}};
    // -74714523293440252950179
    s21_decimal decimal_check = {{0xBAB9B6A3, 0x484CE8DF, 0xFD2, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok731) {
    // 66611715967280177.6517322028
    s21_decimal decimal = {{0x3DCD152C, 0x95154CDF, 0x226FFCB, 0xA0000}};
    // 66611715967280177
    s21_decimal decimal_check = {{0xB41BE431, 0xECA700, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok732) {
    // -66611715967280177.6517322028
    s21_decimal decimal = {{0x3DCD152C, 0x95154CDF, 0x226FFCB, 0x800A0000}};
    // -66611715967280177
    s21_decimal decimal_check = {{0xB41BE431, 0xECA700, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok733) {
    // -447206130687125.30385266512086
    s21_decimal decimal = {{0x752B90D6, 0x32F773EF, 0x9080062C, 0x800E0000}};
    // -447206130687125
    s21_decimal decimal_check = {{0x4A8F9C95, 0x196BB, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok734) {
    // 447206130687125.30385266512086
    s21_decimal decimal = {{0x752B90D6, 0x32F773EF, 0x9080062C, 0xE0000}};
    // 447206130687125
    s21_decimal decimal_check = {{0x4A8F9C95, 0x196BB, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok735) {
    // 3586208.4160992681386155280363
    s21_decimal decimal = {{0x95ED87EB, 0xDC3D7C23, 0x73E06BB5, 0x160000}};
    // 3586208
    s21_decimal decimal_check = {{0x36B8A0, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok736) {
    // -3586208.4160992681386155280363
    s21_decimal decimal = {{0x95ED87EB, 0xDC3D7C23, 0x73E06BB5, 0x80160000}};
    // -3586208
    s21_decimal decimal_check = {{0x36B8A0, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok737) {
    // -63414447872562374553.326627236
    s21_decimal decimal = {{0x95C0A9A4, 0x8521AC66, 0xCCE733AB, 0x80090000}};
    // -63414447872562374553
    s21_decimal decimal_check = {{0x1F9B2799, 0x700D605B, 0x3, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok738) {
    // 63414447872562374553.326627236
    s21_decimal decimal = {{0x95C0A9A4, 0x8521AC66, 0xCCE733AB, 0x90000}};
    // 63414447872562374553
    s21_decimal decimal_check = {{0x1F9B2799, 0x700D605B, 0x3, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok739) {
    // -62718.090630173553860344874351
    s21_decimal decimal = {{0xF599056F, 0xC4D31D38, 0xCAA73049, 0x80180000}};
    // -62718
    s21_decimal decimal_check = {{0xF4FE, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok740) {
    // 62718.090630173553860344874351
    s21_decimal decimal = {{0xF599056F, 0xC4D31D38, 0xCAA73049, 0x180000}};
    // 62718
    s21_decimal decimal_check = {{0xF4FE, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok741) {
    // 4327309140.136035529319909948
    s21_decimal decimal = {{0x62C20A3C, 0x899FBA29, 0xDFB775A, 0x120000}};
    // 4327309140
    s21_decimal decimal_check = {{0x1ED7F54, 0x1, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok742) {
    // -4327309140.136035529319909948
    s21_decimal decimal = {{0x62C20A3C, 0x899FBA29, 0xDFB775A, 0x80120000}};
    // -4327309140
    s21_decimal decimal_check = {{0x1ED7F54, 0x1, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok743) {
    // 24245277394047.024969849972650
    s21_decimal decimal = {{0x578327AA, 0x282F6DB0, 0x4E573931, 0xF0000}};
    // 24245277394047
    s21_decimal decimal_check = {{0xB25847F, 0x160D, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok744) {
    // -24245277394047.024969849972650
    s21_decimal decimal = {{0x578327AA, 0x282F6DB0, 0x4E573931, 0x800F0000}};
    // -24245277394047
    s21_decimal decimal_check = {{0xB25847F, 0x160D, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok745) {
    // 5.4782519809476743676092818150
    s21_decimal decimal = {{0x5D122E6, 0x954F7076, 0xB10309CD, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok746) {
    // -5.4782519809476743676092818150
    s21_decimal decimal = {{0x5D122E6, 0x954F7076, 0xB10309CD, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok747) {
    // -20665521939165152533.169342920
    s21_decimal decimal = {{0x1BC89C8, 0x1977E40D, 0x42C61E7D, 0x80090000}};
    // -20665521939165152533
    s21_decimal decimal_check = {{0x89FB0515, 0x1ECAAEB6, 0x1, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok748) {
    // 20665521939165152533.169342920
    s21_decimal decimal = {{0x1BC89C8, 0x1977E40D, 0x42C61E7D, 0x90000}};
    // 20665521939165152533
    s21_decimal decimal_check = {{0x89FB0515, 0x1ECAAEB6, 0x1, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok749) {
    // 31844355948514237.797120835773
    s21_decimal decimal = {{0xC5A780BD, 0x9FEA207, 0x66E508AB, 0xC0000}};
    // 31844355948514237
    s21_decimal decimal_check = {{0xE4698BBD, 0x712245, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok750) {
    // -31844355948514237.797120835773
    s21_decimal decimal = {{0xC5A780BD, 0x9FEA207, 0x66E508AB, 0x800C0000}};
    // -31844355948514237
    s21_decimal decimal_check = {{0xE4698BBD, 0x712245, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok751) {
    // 2401861907392671774775.4329411
    s21_decimal decimal = {{0xCC566543, 0xAE11F8, 0x4D9BBC6D, 0x70000}};
    // 2401861907392671774775
    s21_decimal decimal_check = {{0xF25FF837, 0x3487A729, 0x82, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok752) {
    // -2401861907392671774775.4329411
    s21_decimal decimal = {{0xCC566543, 0xAE11F8, 0x4D9BBC6D, 0x80070000}};
    // -2401861907392671774775
    s21_decimal decimal_check = {{0xF25FF837, 0x3487A729, 0x82, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok753) {
    // 773.75200545805953816123124549
    s21_decimal decimal = {{0xAB47AB45, 0x69C8CC2F, 0xFA03440A, 0x1A0000}};
    // 773
    s21_decimal decimal_check = {{0x305, 0x0, 0x0, 0x0}};

    test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok754) {
    // -773.75200545805953816123124549
    s21_decimal decimal = {{0xAB47AB45, 0x69C8CC2F, 0xFA03440A, 0x801A0000}};
    // -773
    s21_decimal decimal_check = {{0x305, 0x0, 0x0, 0x80000000}};

    test_truncate(decimal, decimal_check);
}

Suite * from_truncate_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("truncate");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, from_truncate_fail1);

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

    ck_assert_int_eq(res, S21_OTHER_OK);
    ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
    ck_assert_int_eq(s21_decimal_get_sign(result), s21_decimal_get_sign(decimal_check));
}
