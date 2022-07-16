#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные (ручные)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
START_TEST(test_from_decimal_to_float_fail_manual1) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int code = s21_from_decimal_to_float(decimal, NULL);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}

START_TEST(test_from_decimal_to_float_fail_manual2) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual4) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual5) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual6) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual7) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual8) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual9) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
END_TEST


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_decimal_to_float_ok1) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    int check = 1870659584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok2) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    int check = -276824064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    int check = 1842138317;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    int check = -305345331;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok5) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    int check = 1814288138;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok6) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    int check = -333195510;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok7) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    int check = 1786974831;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok8) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    int check = -360508817;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok9) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    int check = 1758574359;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok10) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    int check = -388909289;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok11) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    int check = 1730659756;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok12) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    int check = -416823892;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok13) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    int check = 1703294909;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok14) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    int check = -444188739;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok15) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    int check = 1675018133;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok16) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    int check = -472465515;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok17) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    int check = 1647037559;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok18) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    int check = -500446089;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok19) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    int check = 1619619935;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok20) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    int check = -527863713;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok21) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    int check = 1591469823;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok22) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    int check = -556013825;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok23) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    int check = 1563421695;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok24) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    int check = -584061953;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok25) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    int check = 1535950028;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok26) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    int check = -611533620;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok27) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    int check = 1507929619;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok28) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    int check = -639554029;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok29) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    int check = 1479812316;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok30) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    int check = -667671332;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok31) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    int check = 1452285309;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok32) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    int check = -695198339;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok33) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    int check = 1424397717;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok34) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    int check = -723085931;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok35) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    int check = 1396209578;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok36) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    int check = -751274070;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok37) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    int check = 1368625903;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok38) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    int check = -778857745;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok39) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    int check = 1340874314;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok40) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    int check = -806609334;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok41) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int check = 1312613640;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok42) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    int check = -834870008;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok43) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    int check = 1284971936;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok44) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    int check = -862511712;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok45) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    int check = 1257359617;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok46) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    int check = -890124031;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok47) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    int check = 1229024666;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok48) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    int check = -918458982;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok49) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    int check = 1201323541;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok50) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    int check = -946160107;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok51) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    int check = 1173853832;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok52) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    int check = -973629816;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok53) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    int check = 1145442822;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok54) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    int check = -1002040826;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok55) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    int check = 1117680850;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok56) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    int check = -1029802798;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok57) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 1090357174;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok58) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -1057126474;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok59) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    int check = 1870659584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok60) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    int check = -276824064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok61) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    int check = 1842138317;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok62) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    int check = -305345331;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok63) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    int check = 1814288138;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok64) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    int check = -333195510;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok65) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    int check = 1786974831;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok66) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    int check = -360508817;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok67) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    int check = 1758574359;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok68) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    int check = -388909289;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok69) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    int check = 1730659756;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok70) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    int check = -416823892;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok71) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    int check = 1703294909;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok72) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    int check = -444188739;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok73) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    int check = 1675018133;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok74) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    int check = -472465515;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok75) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    int check = 1647037559;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok76) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    int check = -500446089;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok77) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    int check = 1619619935;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok78) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    int check = -527863713;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok79) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    int check = 1591469823;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok80) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    int check = -556013825;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok81) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    int check = 1563421695;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok82) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    int check = -584061953;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok83) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    int check = 1535950028;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok84) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    int check = -611533620;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok85) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    int check = 1507929619;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok86) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    int check = -639554029;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok87) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    int check = 1479812316;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok88) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    int check = -667671332;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok89) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    int check = 1452285309;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok90) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    int check = -695198339;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok91) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    int check = 1424397717;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok92) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    int check = -723085931;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok93) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    int check = 1396209578;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok94) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    int check = -751274070;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok95) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    int check = 1368625903;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok96) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    int check = -778857745;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok97) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    int check = 1340874314;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok98) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    int check = -806609334;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok99) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int check = 1312613640;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok100) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    int check = -834870008;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok101) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    int check = 1284971936;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok102) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    int check = -862511712;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok103) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    int check = 1257359617;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok104) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    int check = -890124031;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok105) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    int check = 1229024666;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok106) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    int check = -918458982;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok107) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    int check = 1201323541;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok108) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    int check = -946160107;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok109) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    int check = 1173853832;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok110) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    int check = -973629816;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok111) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    int check = 1145442822;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok112) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    int check = -1002040826;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok113) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    int check = 1117680850;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok114) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    int check = -1029802798;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok115) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 1090357174;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok116) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -1057126474;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok117) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    int check = 1865067179;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok118) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    int check = -282416469;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok119) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    int check = 1837664393;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok120) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    int check = -309819255;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok121) {
    // 528187750.09509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
    int check = 1308351499;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok122) {
    // -528187750.09509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
    int check = -839132149;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok123) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    int check = 1084818724;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok124) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    int check = -1062664924;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok125) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    int check = 1865067179;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok126) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    int check = -282416469;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok127) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    int check = 1837664393;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok128) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    int check = -309819255;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok129) {
    // 528187750.09509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
    int check = 1308351499;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok130) {
    // -528187750.09509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
    int check = -839132149;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok131) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    int check = 1084818724;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok132) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    int check = -1062664924;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok133) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    int check = 1865067179;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok134) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    int check = -282416469;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok135) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    int check = 1837664393;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok136) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    int check = -309819255;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok137) {
    // 528187749.97211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x140000}};
    int check = 1308351499;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok138) {
    // -528187749.97211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80140000}};
    int check = -839132149;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok139) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    int check = 1084818724;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok140) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    int check = -1062664924;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok141) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    int check = 1865067179;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok142) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    int check = -282416469;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok143) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    int check = 1837664393;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok144) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    int check = -309819255;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok145) {
    // 528187749.97211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x140000}};
    int check = 1308351499;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok146) {
    // -528187749.97211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80140000}};
    int check = -839132149;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok147) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    int check = 1084818724;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok148) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    int check = -1062664924;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok149) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    int check = 1596631723;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok150) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    int check = -550851925;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok151) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    int check = 1569228937;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok152) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    int check = -578254711;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok153) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    int check = 1290440703;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok154) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    int check = -857042945;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok155) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    int check = 1067280775;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok156) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    int check = -1080202873;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok157) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    int check = 1596631723;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok158) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    int check = -550851925;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok159) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    int check = 1569228937;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok160) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    int check = -578254711;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok161) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    int check = 1290440703;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok162) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    int check = -857042945;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok163) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    int check = 1067280775;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok164) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    int check = -1080202873;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok165) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    int check = 1328196267;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok166) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    int check = -819287381;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok167) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    int check = 1300793481;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok168) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    int check = -846690167;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok169) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    int check = 1217122149;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok170) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    int check = -930361499;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok171) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    int check = 1077362815;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok172) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    int check = -1070120833;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok173) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    int check = 1856678571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok174) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    int check = -290805077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok175) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    int check = 1829275785;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok176) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    int check = -318207863;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok177) {
    // 264093875.04754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x140000}};
    int check = 1299962891;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok178) {
    // -264093875.04754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80140000}};
    int check = -847520757;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok179) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    int check = 1076430116;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok180) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    int check = -1071053532;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok181) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    int check = 1856678571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok182) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    int check = -290805077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok183) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    int check = 1829275785;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok184) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    int check = -318207863;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok185) {
    // 264093875.04754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x140000}};
    int check = 1299962891;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok186) {
    // -264093875.04754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80140000}};
    int check = -847520757;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok187) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    int check = 1076430116;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok188) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    int check = -1071053532;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok189) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    int check = 1856678571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok190) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    int check = -290805077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok191) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    int check = 1829275785;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok192) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    int check = -318207863;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok193) {
    // 264093874.98605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x140000}};
    int check = 1299962891;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok194) {
    // -264093874.98605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80140000}};
    int check = -847520757;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok195) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    int check = 1076430116;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok196) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    int check = -1071053532;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok197) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    int check = 1856678571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok198) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    int check = -290805077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok199) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    int check = 1829275785;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok200) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    int check = -318207863;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok201) {
    // 264093874.98605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x140000}};
    int check = 1299962891;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok202) {
    // -264093874.98605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80140000}};
    int check = -847520757;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok203) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    int check = 1076430116;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok204) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    int check = -1071053532;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok205) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    int check = 1588243115;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok206) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    int check = -559240533;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok207) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    int check = 1560840329;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok208) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    int check = -586643319;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok209) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    int check = 1253811813;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok210) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    int check = -893671835;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok211) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    int check = 1086637033;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok212) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    int check = -1060846615;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok213) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    int check = 1588243115;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok214) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    int check = -559240533;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok215) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    int check = 1560840329;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok216) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    int check = -586643319;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok217) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    int check = 1253811813;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok218) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    int check = -893671835;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok219) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    int check = 1086637033;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok220) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    int check = -1060846615;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok221) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    int check = 1319807659;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok222) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    int check = -827675989;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok223) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    int check = 1292404873;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok224) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    int check = -855078775;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok225) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    int check = 1208733541;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok226) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    int check = -938750107;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok227) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    int check = 1068974207;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok228) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    int check = -1078509441;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok229) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    int check = 1602224128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok230) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    int check = -545259520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok231) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    int check = 1573702861;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok232) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    int check = -573780787;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok233) {
    // 184467440.78004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0xB0000}};
    int check = 1294986239;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok234) {
    // -184467440.78004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x800B0000}};
    int check = -852497409;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok235) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    int check = 1072438858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok236) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    int check = -1075044790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok237) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    int check = 1602224128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok238) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    int check = -545259520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok239) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    int check = 1573702861;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok240) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    int check = -573780787;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok241) {
    // 18446744.078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0xC0000}};
    int check = 1267514572;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok242) {
    // -18446744.078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x800C0000}};
    int check = -879969076;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok243) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    int check = 1072438858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok244) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    int check = -1075044790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok245) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    int check = 1602224128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok246) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    int check = -545259520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok247) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    int check = 1573702861;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok248) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    int check = -573780787;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok249) {
    // 1844674.4073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xD0000}};
    int check = 1239494163;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok250) {
    // -1844674.4073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800D0000}};
    int check = -907989485;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok251) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    int check = 1072438858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok252) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    int check = -1075044790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok253) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    int check = 1602224128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok254) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    int check = -545259520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok255) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    int check = 1573702861;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok256) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    int check = -573780787;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok257) {
    // 184467.44073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xE0000}};
    int check = 1211376860;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok258) {
    // -184467.44073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800E0000}};
    int check = -936106788;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok259) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    int check = 1072438858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok260) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    int check = -1075044790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok261) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    int check = 1333788672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok262) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    int check = -813694976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok263) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    int check = 1305267405;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok264) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    int check = -842216243;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok265) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    int check = 1277417226;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok266) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    int check = -870066422;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok267) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    int check = 1221703447;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok268) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    int check = -925780201;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok269) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    int check = 1082749023;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok270) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    int check = -1064734625;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok271) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    int check = 1110166647;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok272) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    int check = -1037317001;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok273) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    int check = 1333788672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok274) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    int check = -813694976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok275) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    int check = 1305267405;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok276) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    int check = -842216243;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok277) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    int check = 1277417226;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok278) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    int check = -870066422;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok279) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    int check = 1250103919;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok280) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    int check = -897379729;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok281) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    int check = 1082749023;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok282) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    int check = -1064734625;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok283) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    int check = 1110166647;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok284) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    int check = -1037317001;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok285) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    int check = 1036831949;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok286) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    int check = -1110651699;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok287) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    int check = 702623251;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok288) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    int check = -1444860397;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok289) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    int check = 674505948;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok290) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    int check = -1472977700;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok291) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    int check = 312374482;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok292) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    int check = -1835109166;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok293) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    int check = 285050806;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok294) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    int check = -1862432842;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok295) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    int check = 1862270976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok296) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    int check = -285212672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok297) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    int check = 1833749709;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok298) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    int check = -313733939;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok299) {
    // 396140812.66355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x140000}};
    int check = 1304225032;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok300) {
    // -396140812.66355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80140000}};
    int check = -843258616;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok301) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    int check = 1081968566;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok302) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    int check = -1065515082;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok303) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    int check = 1862270976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok304) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    int check = -285212672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok305) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    int check = 1833749709;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok306) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    int check = -313733939;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok307) {
    // 39614081.266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x150000}};
    int check = 1276583328;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok308) {
    // -39614081.266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80150000}};
    int check = -870900320;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok309) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    int check = 1081968566;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok310) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    int check = -1065515082;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok311) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    int check = 1862270976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok312) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    int check = -285212672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok313) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    int check = 1833749709;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok314) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    int check = -313733939;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok315) {
    // 3961408.1257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x160000}};
    int check = 1248971009;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok316) {
    // -3961408.1257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80160000}};
    int check = -898512639;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok317) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    int check = 1081968566;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok318) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    int check = -1065515082;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok319) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    int check = 1862270976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok320) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    int check = -285212672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok321) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    int check = 1833749709;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok322) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    int check = -313733939;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok323) {
    // 396140.81257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x170000}};
    int check = 1220636058;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok324) {
    // -396140.81257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80170000}};
    int check = -926847590;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok325) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    int check = 1081968566;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok326) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    int check = -1065515082;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok327) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    int check = 1593835520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok328) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    int check = -553648128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok329) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    int check = 1565314253;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok330) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    int check = -582169395;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok331) {
    // 922337203.9002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0xA0000}};
    int check = 1314645759;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok332) {
    // -922337203.9002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x800A0000}};
    int check = -832837889;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok333) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    int check = 1091801839;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok334) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    int check = -1055681809;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok335) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    int check = 1593835520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok336) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    int check = -553648128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok337) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    int check = 1565314253;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok338) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    int check = -582169395;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok339) {
    // 92233720.36854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0xB0000}};
    int check = 1286597631;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok340) {
    // -92233720.36854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x800B0000}};
    int check = -860886017;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok341) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    int check = 1091801839;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok342) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    int check = -1055681809;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok343) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok344) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok345) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    int check = 1296878797;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok346) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    int check = -850604851;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok347) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    int check = 1269028618;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok348) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    int check = -878455030;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok349) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    int check = 1213314839;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok350) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    int check = -934168809;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok351) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    int check = 1101778039;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok352) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    int check = -1045705609;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok353) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    int check = 1074360415;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok354) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    int check = -1073123233;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok355) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    int check = 1795233792;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok356) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    int check = -352249856;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok357) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    int check = 1766755533;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok358) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    int check = -380728115;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok359) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    int check = 1237221949;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok360) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    int check = -910261699;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok361) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    int check = 1070056270;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok362) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    int check = -1077427378;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok363) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    int check = 1795233792;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok364) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    int check = -352249856;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok365) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    int check = 1766755533;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok366) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    int check = -380728115;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok367) {
    // 15606476.7562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x130000}};
    int check = 1265509069;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok368) {
    // -15606476.7562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80130000}};
    int check = -881974579;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok369) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    int check = 1070056270;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok370) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    int check = -1077427378;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok371) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    int check = 1795233792;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok372) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    int check = -352249856;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok373) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    int check = 1766755533;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok374) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    int check = -380728115;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok375) {
    // 156064.767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x150000}};
    int check = 1209559089;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok376) {
    // -156064.767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80150000}};
    int check = -937924559;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok377) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    int check = 1070056270;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok378) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    int check = -1077427378;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok379) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    int check = 1795233792;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok380) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    int check = -352249856;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok381) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    int check = 1766755533;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok382) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    int check = -380728115;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok383) {
    // 15606.4767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x160000}};
    int check = 1181997544;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok384) {
    // -15606.4767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80160000}};
    int check = -965486104;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok385) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    int check = 1070056270;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok386) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    int check = -1077427378;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok387) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    int check = 1526798336;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok388) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    int check = -620685312;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok389) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    int check = 1498320077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok390) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    int check = -649163571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok391) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    int check = 1303200838;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok392) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    int check = -844282810;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok393) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    int check = 1080593916;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok394) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    int check = -1066889732;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok395) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    int check = 1526798336;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok396) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    int check = -620685312;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok397) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    int check = 1498320077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok398) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    int check = -649163571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok399) {
    // 3633666.0274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xA0000}};
    int check = 1247660040;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok400) {
    // -3633666.0274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800A0000}};
    int check = -899823608;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok401) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    int check = 1303200838;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok402) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    int check = -844282810;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok403) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    int check = 1108433085;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok404) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    int check = -1039050563;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok405) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    int check = 1080593916;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok406) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    int check = -1066889732;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok407) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    int check = 1258362880;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok408) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    int check = -889120768;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok409) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    int check = 1229884621;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok410) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    int check = -917599027;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok411) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    int check = 1202011505;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok412) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    int check = -945472143;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok413) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    int check = 1174679847;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok414) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    int check = -972803801;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok415) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    int check = 1118385325;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok416) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    int check = -1029098323;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok417) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    int check = 1091001687;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok418) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    int check = -1056481961;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok419) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    int check = 1870659584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok420) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    int check = -276824064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok421) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    int check = 1842138317;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok422) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    int check = -305345331;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok423) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int check = 1312613640;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok424) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    int check = -834870008;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok425) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 1090357174;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok426) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -1057126474;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok427) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    int check = 1870659584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok428) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    int check = -276824064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok429) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    int check = 1842138317;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok430) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    int check = -305345331;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok431) {
    // 79228162.514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    int check = 1284971936;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok432) {
    // -79228162.514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    int check = -862511712;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok433) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 1090357174;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok434) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -1057126474;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok435) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    int check = 1870659584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok436) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    int check = -276824064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok437) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    int check = 1842138317;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok438) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    int check = -305345331;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok439) {
    // 7922816.2495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x160000}};
    int check = 1257359616;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok440) {
    // -7922816.2495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80160000}};
    int check = -890124032;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok441) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    int check = 1090357174;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok442) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    int check = -1057126474;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok443) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    int check = 1870659584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok444) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    int check = -276824064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok445) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    int check = 1842138317;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok446) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    int check = -305345331;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok447) {
    // 792281.62495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x170000}};
    int check = 1229024666;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok448) {
    // -792281.62495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80170000}};
    int check = -918458982;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok449) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    int check = 1090357174;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok450) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    int check = -1057126474;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok451) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    int check = 1602224128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok452) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    int check = -545259520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok453) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    int check = 1573702861;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok454) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    int check = -573780787;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok455) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    int check = 1518539375;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok456) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    int check = -628944273;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok457) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    int check = 1294986239;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok458) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    int check = -852497409;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok459) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    int check = 1127774122;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok460) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    int check = -1019709526;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok461) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    int check = 1072438858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok462) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    int check = -1075044790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok463) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    int check = 1602224128;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok464) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    int check = -545259520;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok465) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    int check = 1573702861;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok466) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    int check = -573780787;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok467) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    int check = 1518539375;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok468) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    int check = -628944273;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok469) {
    // 18446744.069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0xC0000}};
    int check = 1267514572;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok470) {
    // -18446744.069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x800C0000}};
    int check = -879969076;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok471) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    int check = 1127774122;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok472) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    int check = -1019709526;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok473) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    int check = 1072438858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok474) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    int check = -1075044790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok475) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    int check = 1333788672;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok476) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    int check = -813694976;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok477) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    int check = 1305267405;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok478) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    int check = -842216243;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok479) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    int check = 1277417226;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok480) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    int check = -870066422;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok481) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    int check = 1193788844;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok482) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    int check = -953694804;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok483) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    int check = 1110166647;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok484) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    int check = -1037317001;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok485) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    int check = 1082749023;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok486) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    int check = -1064734625;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok487) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok488) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok489) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok490) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok491) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok492) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok493) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok494) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok495) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok496) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok497) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok498) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok499) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok500) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok501) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok502) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok503) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok504) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok505) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    int check = 1066192077;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok506) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    int check = -1081291571;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok507) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    int check = 1094839173;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok508) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    int check = -1052644475;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok509) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    int check = 1123434234;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok510) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    int check = -1024049414;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok511) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    int check = 1150960627;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok512) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    int check = -996523021;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok513) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    int check = 1178657918;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok514) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    int check = -968825730;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok515) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    int check = 1206984720;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok516) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    int check = -940498928;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok517) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    int check = 1234613305;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok518) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    int check = -912870343;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok519) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    int check = 1318267910;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok520) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    int check = -829215738;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok521) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    int check = 1429448509;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok522) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    int check = -718035139;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok523) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    int check = 1120272384;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok524) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    int check = -1027211264;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok525) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    int check = 1092511334;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok526) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    int check = -1054972314;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok527) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    int check = 1120402145;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok528) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    int check = -1027081503;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok529) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    int check = 1148846064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok530) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    int check = -998637584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok531) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    int check = 1176256512;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok532) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    int check = -971227136;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok533) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    int check = 1203982336;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok534) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    int check = -943501312;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok535) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    int check = 1232348160;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok536) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    int check = -915135488;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok537) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    int check = 1259902592;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok538) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    int check = -887581056;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok539) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    int check = 1287568416;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok540) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    int check = -859915232;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok541) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    int check = 1315859240;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok542) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    int check = -831624408;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok543) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    int check = 1343554297;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok544) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    int check = -803929351;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok545) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    int check = 1091567616;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok546) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    int check = -1055916032;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok547) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    int check = 1063675494;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok548) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    int check = -1083808154;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok549) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    int check = 1065185444;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok550) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    int check = -1082298204;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok551) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    int check = 1065336439;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok552) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    int check = -1082147209;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok553) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    int check = 1065351538;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok554) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    int check = -1082132110;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok555) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    int check = 1065353048;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok556) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    int check = -1082130600;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok557) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    int check = 1065353199;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok558) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    int check = -1082130449;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok559) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    int check = 1065353214;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok560) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    int check = -1082130434;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok561) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok562) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok563) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok564) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok565) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok566) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok567) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    int check = 1065353216;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok568) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    int check = -1082130432;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok569) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    int check = -2147483648;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok570) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    int check = 0;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok571) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    int check = -2147483648;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok572) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    int check = 0;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok573) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    int check = -2147483648;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok574) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    int check = 0;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok575) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    int check = -2147483648;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok576) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    int check = 0;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok577) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    int check = -2147483648;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok578) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    int check = 0;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok579) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    int check = -2147483648;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok580) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok581) {
    // 2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x0}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok582) {
    // -2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80000000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok583) {
    // 2147483646.00
    s21_decimal decimal = {{0xFFFFFF38, 0x31, 0x0, 0x20000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok584) {
    // -2147483646.00
    s21_decimal decimal = {{0xFFFFFF38, 0x31, 0x0, 0x80020000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok585) {
    // 2147483646.99
    s21_decimal decimal = {{0xFFFFFF9B, 0x31, 0x0, 0x20000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok586) {
    // -2147483646.99
    s21_decimal decimal = {{0xFFFFFF9B, 0x31, 0x0, 0x80020000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok587) {
    // 2147483646.999999999999999999
    s21_decimal decimal = {{0x589BFFFF, 0xC5D1494C, 0x6F05B59, 0x120000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok588) {
    // -2147483646.999999999999999999
    s21_decimal decimal = {{0x589BFFFF, 0xC5D1494C, 0x6F05B59, 0x80120000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok589) {
    // 21474836.46
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x20000}};
    int check = 1269028618;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok590) {
    // -21474836.46
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80020000}};
    int check = -878455030;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok591) {
    // 214.7483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x70000}};
    int check = 1129758613;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok592) {
    // -214.7483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80070000}};
    int check = -1017725035;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok593) {
    // 2.147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x90000}};
    int check = 1074360415;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok594) {
    // -2.147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80090000}};
    int check = -1073123233;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok595) {
    // 0.2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0xA0000}};
    int check = 1046210303;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok596) {
    // -0.2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x800A0000}};
    int check = -1101273345;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok597) {
    // 0.0000000000000000002147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x1C0000}};
    int check = 545097654;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok598) {
    // -0.0000000000000000002147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x801C0000}};
    int check = -1602385994;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok599) {
    // 2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok600) {
    // -2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok601) {
    // 2147483647.00
    s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x20000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok602) {
    // -2147483647.00
    s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x80020000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok603) {
    // 2147483647.99
    s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x20000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok604) {
    // -2147483647.99
    s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x80020000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok605) {
    // 2147483647.999999999999999999
    s21_decimal decimal = {{0xFFFFFFFF, 0xD3B1FFFF, 0x6F05B59, 0x120000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok606) {
    // -2147483647.999999999999999999
    s21_decimal decimal = {{0xFFFFFFFF, 0xD3B1FFFF, 0x6F05B59, 0x80120000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok607) {
    // 21474836.47
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x20000}};
    int check = 1269028618;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok608) {
    // -21474836.47
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80020000}};
    int check = -878455030;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok609) {
    // 214.7483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x70000}};
    int check = 1129758613;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok610) {
    // -214.7483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80070000}};
    int check = -1017725035;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok611) {
    // 2.147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x90000}};
    int check = 1074360415;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok612) {
    // -2.147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80090000}};
    int check = -1073123233;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok613) {
    // 0.2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0xA0000}};
    int check = 1046210303;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok614) {
    // -0.2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x800A0000}};
    int check = -1101273345;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok615) {
    // 0.0000000000000000002147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x1C0000}};
    int check = 545097654;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok616) {
    // -0.0000000000000000002147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x801C0000}};
    int check = -1602385994;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok617) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok618) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok619) {
    // 2147483648.00
    s21_decimal decimal = {{0x0, 0x32, 0x0, 0x20000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok620) {
    // -2147483648.00
    s21_decimal decimal = {{0x0, 0x32, 0x0, 0x80020000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok621) {
    // 2147483648.99
    s21_decimal decimal = {{0x63, 0x32, 0x0, 0x20000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok622) {
    // -2147483648.99
    s21_decimal decimal = {{0x63, 0x32, 0x0, 0x80020000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok623) {
    // 2147483648.999999999999999999
    s21_decimal decimal = {{0xA763FFFF, 0xE192B6B3, 0x6F05B59, 0x120000}};
    int check = 1325400064;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok624) {
    // -2147483648.999999999999999999
    s21_decimal decimal = {{0xA763FFFF, 0xE192B6B3, 0x6F05B59, 0x80120000}};
    int check = -822083584;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok625) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    int check = 1269028618;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok626) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    int check = -878455030;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok627) {
    // 214.7483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x70000}};
    int check = 1129758613;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok628) {
    // -214.7483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80070000}};
    int check = -1017725035;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok629) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    int check = 1074360415;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok630) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    int check = -1073123233;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok631) {
    // 0.2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0xA0000}};
    int check = 1046210303;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok632) {
    // -0.2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x800A0000}};
    int check = -1101273345;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok633) {
    // 0.0000000000000000002147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x1C0000}};
    int check = 545097654;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok634) {
    // -0.0000000000000000002147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x801C0000}};
    int check = -1602385994;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok635) {
    // 6106520747677.4271625495128829
    s21_decimal decimal = {{0x579D2AFD, 0x7AD693D4, 0xC54FF4AA, 0x100000}};
    int check = 1420933408;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok636) {
    // -6106520747677.4271625495128829
    s21_decimal decimal = {{0x579D2AFD, 0x7AD693D4, 0xC54FF4AA, 0x80100000}};
    int check = -726550240;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok637) {
    // -74889.374403716981248396587600
    s21_decimal decimal = {{0x76777250, 0x3AC16D58, 0xF1FB09E1, 0x80180000}};
    int check = -946715472;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok638) {
    // 74889.374403716981248396587600
    s21_decimal decimal = {{0x76777250, 0x3AC16D58, 0xF1FB09E1, 0x180000}};
    int check = 1200768176;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok639) {
    // 6134854533651.9803809608043381
    s21_decimal decimal = {{0x5A750B75, 0xA24E9664, 0xC63A53CA, 0x100000}};
    int check = 1420987450;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok640) {
    // -6134854533651.9803809608043381
    s21_decimal decimal = {{0x5A750B75, 0xA24E9664, 0xC63A53CA, 0x80100000}};
    int check = -726496198;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok641) {
    // 5346891104.4422425476576932158
    s21_decimal decimal = {{0xF801713E, 0xBD66BAC5, 0xACC47253, 0x130000}};
    int check = 1335843211;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok642) {
    // -5346891104.4422425476576932158
    s21_decimal decimal = {{0xF801713E, 0xBD66BAC5, 0xACC47253, 0x80130000}};
    int check = -811640437;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok643) {
    // -30.499087459303925446062648780
    s21_decimal decimal = {{0x6702DCC, 0x1C31DF45, 0x628C40FC, 0x801B0000}};
    int check = -1040974302;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok644) {
    // 30.499087459303925446062648780
    s21_decimal decimal = {{0x6702DCC, 0x1C31DF45, 0x628C40FC, 0x1B0000}};
    int check = 1106509346;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok645) {
    // -21.93269095551860212335148673
    s21_decimal decimal = {{0xAF247E81, 0xE9817F26, 0x7163ACB, 0x801A0000}};
    int check = -1045465561;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok646) {
    // 21.93269095551860212335148673
    s21_decimal decimal = {{0xAF247E81, 0xE9817F26, 0x7163ACB, 0x1A0000}};
    int check = 1102018087;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok647) {
    // -2924595329341314621806490621.2
    s21_decimal decimal = {{0x942207E4, 0xDB3D71D5, 0x5E7FAF80, 0x80010000}};
    int check = -317246798;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok648) {
    // 2924595329341314621806490621.2
    s21_decimal decimal = {{0x942207E4, 0xDB3D71D5, 0x5E7FAF80, 0x10000}};
    int check = 1830236850;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok649) {
    // -7933753176687179.952362985527
    s21_decimal decimal = {{0xA3BD9837, 0x81A378C3, 0x19A2A595, 0x800C0000}};
    int check = -639533657;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok650) {
    // 7933753176687179.952362985527
    s21_decimal decimal = {{0xA3BD9837, 0x81A378C3, 0x19A2A595, 0xC0000}};
    int check = 1507949991;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok651) {
    // -6.8263927184223926983629069911
    s21_decimal decimal = {{0x3715DE57, 0xC6C1B557, 0xDC9298DB, 0x801C0000}};
    int check = -1059425841;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok652) {
    // 6.8263927184223926983629069911
    s21_decimal decimal = {{0x3715DE57, 0xC6C1B557, 0xDC9298DB, 0x1C0000}};
    int check = 1088057807;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok653) {
    // -177676472067078452.49744917274
    s21_decimal decimal = {{0x3AD6531A, 0x12CC7928, 0x39690DA5, 0x800B0000}};
    int check = -602026252;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok654) {
    // 177676472067078452.49744917274
    s21_decimal decimal = {{0x3AD6531A, 0x12CC7928, 0x39690DA5, 0xB0000}};
    int check = 1545457396;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok655) {
    // 1344737398110546470.9724034659
    s21_decimal decimal = {{0xF7C4D663, 0x3A1B5559, 0x2B736834, 0xA0000}};
    int check = 1570065340;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok656) {
    // -1344737398110546470.9724034659
    s21_decimal decimal = {{0xF7C4D663, 0x3A1B5559, 0x2B736834, 0x800A0000}};
    int check = -577418308;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok657) {
    // -49316351996238566051214.163451
    s21_decimal decimal = {{0xE4867DFB, 0xAB4924CD, 0x9F5987BE, 0x80060000}};
    int check = -450423010;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok658) {
    // 49316351996238566051214.163451
    s21_decimal decimal = {{0xE4867DFB, 0xAB4924CD, 0x9F5987BE, 0x60000}};
    int check = 1697060638;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok659) {
    // 490716702332314943439986.55226
    s21_decimal decimal = {{0x2D514AFA, 0xB7D4E5D1, 0x9E8F225D, 0x50000}};
    int check = 1724896157;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok660) {
    // -490716702332314943439986.55226
    s21_decimal decimal = {{0x2D514AFA, 0xB7D4E5D1, 0x9E8F225D, 0x80050000}};
    int check = -422587491;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok661) {
    // 71769374779018053.62361261033
    s21_decimal decimal = {{0xBD09DBE9, 0x4445B636, 0x17309FA0, 0xB0000}};
    int check = 1535048158;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok662) {
    // -71769374779018053.62361261033
    s21_decimal decimal = {{0xBD09DBE9, 0x4445B636, 0x17309FA0, 0x800B0000}};
    int check = -612435490;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok663) {
    // 20242800.41626613106538192075
    s21_decimal decimal = {{0x20D41CCB, 0xF149B73F, 0x68A71F8, 0x140000}};
    int check = 1268412600;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok664) {
    // -20242800.41626613106538192075
    s21_decimal decimal = {{0x20D41CCB, 0xF149B73F, 0x68A71F8, 0x80140000}};
    int check = -879071048;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok665) {
    // 15646430756764.061979446182298
    s21_decimal decimal = {{0x9955819A, 0xE8088E6E, 0x328E6C96, 0xF0000}};
    int check = 1432596351;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok666) {
    // -15646430756764.061979446182298
    s21_decimal decimal = {{0x9955819A, 0xE8088E6E, 0x328E6C96, 0x800F0000}};
    int check = -714887297;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok667) {
    // -3989550626992528507.7400401040
    s21_decimal decimal = {{0x45BFB490, 0x835AB5CE, 0x80E8CA10, 0x800A0000}};
    int check = -564300051;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok668) {
    // 3989550626992528507.7400401040
    s21_decimal decimal = {{0x45BFB490, 0x835AB5CE, 0x80E8CA10, 0xA0000}};
    int check = 1583183597;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok669) {
    // -2519.4382125834691211478689194
    s21_decimal decimal = {{0x9DE7E5AA, 0xC353C03D, 0x51684DEF, 0x80190000}};
    int check = -987924733;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok670) {
    // 2519.4382125834691211478689194
    s21_decimal decimal = {{0x9DE7E5AA, 0xC353C03D, 0x51684DEF, 0x190000}};
    int check = 1159558915;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok671) {
    // -5573343877344555320049694038.5
    s21_decimal decimal = {{0x9FDC9561, 0xE9B23AC5, 0xB4159EB9, 0x80010000}};
    int check = -309325492;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok672) {
    // 5573343877344555320049694038.5
    s21_decimal decimal = {{0x9FDC9561, 0xE9B23AC5, 0xB4159EB9, 0x10000}};
    int check = 1838158156;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok673) {
    // 27746391550383212917315197.618
    s21_decimal decimal = {{0x7B21DAB2, 0xE0C11432, 0x59A746F3, 0x30000}};
    int check = 1773640759;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok674) {
    // -27746391550383212917315197.618
    s21_decimal decimal = {{0x7B21DAB2, 0xE0C11432, 0x59A746F3, 0x80030000}};
    int check = -373842889;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok675) {
    // -3181012500219676624.9211899351
    s21_decimal decimal = {{0xF8F7ADD7, 0xB88A4420, 0x66C8B7FB, 0x800A0000}};
    int check = -567241496;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok676) {
    // 3181012500219676624.9211899351
    s21_decimal decimal = {{0xF8F7ADD7, 0xB88A4420, 0x66C8B7FB, 0xA0000}};
    int check = 1580242152;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok677) {
    // -7922488324235.0896161340529192
    s21_decimal decimal = {{0xB0281A28, 0x50389C3E, 0xFFFD4996, 0x80100000}};
    int check = -723086557;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok678) {
    // 7922488324235.0896161340529192
    s21_decimal decimal = {{0xB0281A28, 0x50389C3E, 0xFFFD4996, 0x100000}};
    int check = 1424397091;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok679) {
    // -1.0759575828820809183800908152
    s21_decimal decimal = {{0x6CA4D978, 0x6E76ED04, 0x22C41CCE, 0x801C0000}};
    int check = -1081493254;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok680) {
    // 1.0759575828820809183800908152
    s21_decimal decimal = {{0x6CA4D978, 0x6E76ED04, 0x22C41CCE, 0x1C0000}};
    int check = 1065990394;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok681) {
    // -27752158366718631.710314318576
    s21_decimal decimal = {{0xC955CAF0, 0x9E2F0D29, 0x59AC0C1F, 0x800C0000}};
    int check = -624611102;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok682) {
    // 27752158366718631.710314318576
    s21_decimal decimal = {{0xC955CAF0, 0x9E2F0D29, 0x59AC0C1F, 0xC0000}};
    int check = 1522872546;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok683) {
    // -280821.07358867798127659756677
    s21_decimal decimal = {{0xB4A0AC85, 0x52A1D583, 0x5ABCF98A, 0x80170000}};
    int check = -930537822;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok684) {
    // 280821.07358867798127659756677
    s21_decimal decimal = {{0xB4A0AC85, 0x52A1D583, 0x5ABCF98A, 0x170000}};
    int check = 1216945826;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok685) {
    // 3534.5426619788454960221658751
    s21_decimal decimal = {{0xC7741E7F, 0x6E19CBD7, 0x72350D38, 0x190000}};
    int check = 1163716783;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok686) {
    // -3534.5426619788454960221658751
    s21_decimal decimal = {{0xC7741E7F, 0x6E19CBD7, 0x72350D38, 0x80190000}};
    int check = -983766865;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok687) {
    // 50664850805616249.396690705315
    s21_decimal decimal = {{0x23805BA3, 0x9AEB6DB9, 0xA3B4FB79, 0xC0000}};
    int check = 1530134378;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok688) {
    // -50664850805616249.396690705315
    s21_decimal decimal = {{0x23805BA3, 0x9AEB6DB9, 0xA3B4FB79, 0x800C0000}};
    int check = -617349270;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok689) {
    // -33774179283115086113635818302
    s21_decimal decimal = {{0x4D43DB3E, 0xA2277679, 0x6D2158A7, 0x80000000}};
    int check = -287685967;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok690) {
    // 33774179283115086113635818302
    s21_decimal decimal = {{0x4D43DB3E, 0xA2277679, 0x6D2158A7, 0x0}};
    int check = 1859797681;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok691) {
    // -137453.07840654651945276290061
    s21_decimal decimal = {{0x54B6340D, 0x1DB18EE2, 0x2C69DA27, 0x80170000}};
    int check = -939115707;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok692) {
    // 137453.07840654651945276290061
    s21_decimal decimal = {{0x54B6340D, 0x1DB18EE2, 0x2C69DA27, 0x170000}};
    int check = 1208367941;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok693) {
    // -4543.7477156667446086025321012
    s21_decimal decimal = {{0x3E539A34, 0x46A5BA30, 0x92D1000C, 0x80190000}};
    int check = -980550149;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok694) {
    // 4543.7477156667446086025321012
    s21_decimal decimal = {{0x3E539A34, 0x46A5BA30, 0x92D1000C, 0x190000}};
    int check = 1166933499;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok695) {
    // -1942310252346668869966791.8841
    s21_decimal decimal = {{0x40712FF9, 0x9E18A1EE, 0x3EC269F1, 0x80040000}};
    int check = -405952915;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok696) {
    // 1942310252346668869966791.8841
    s21_decimal decimal = {{0x40712FF9, 0x9E18A1EE, 0x3EC269F1, 0x40000}};
    int check = 1741530733;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok697) {
    // -5089752.0556851410617841706801
    s21_decimal decimal = {{0x5DA36731, 0x17DBB214, 0xA4757136, 0x80160000}};
    int check = -895790160;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok698) {
    // 5089752.0556851410617841706801
    s21_decimal decimal = {{0x5DA36731, 0x17DBB214, 0xA4757136, 0x160000}};
    int check = 1251693488;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok699) {
    // -131.72475313206132285348901479
    s21_decimal decimal = {{0x5D19F267, 0x945956C4, 0x2A900425, 0x801A0000}};
    int check = -1023166071;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok700) {
    // 131.72475313206132285348901479
    s21_decimal decimal = {{0x5D19F267, 0x945956C4, 0x2A900425, 0x1A0000}};
    int check = 1124317577;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok701) {
    // -4813978553442762187.5525344873
    s21_decimal decimal = {{0x4317DE69, 0xF87B7EC5, 0x9B8C4C1A, 0x800A0000}};
    int check = -561668768;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok702) {
    // 4813978553442762187.5525344873
    s21_decimal decimal = {{0x4317DE69, 0xF87B7EC5, 0x9B8C4C1A, 0xA0000}};
    int check = 1585814880;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok703) {
    // 205999366795200.84952405834410
    s21_decimal decimal = {{0x368FAAA, 0xCCB2D3F, 0x428FDE45, 0xE0000}};
    int check = 1463507703;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok704) {
    // -205999366795200.84952405834410
    s21_decimal decimal = {{0x368FAAA, 0xCCB2D3F, 0x428FDE45, 0x800E0000}};
    int check = -683975945;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok705) {
    // -981143603420539827607302.2598
    s21_decimal decimal = {{0x69976486, 0x2CA5A871, 0x1FB3D465, 0x80040000}};
    int check = -414202905;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok706) {
    // 981143603420539827607302.2598
    s21_decimal decimal = {{0x69976486, 0x2CA5A871, 0x1FB3D465, 0x40000}};
    int check = 1733280743;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok707) {
    // 2939857929323272.8928078616606
    s21_decimal decimal = {{0xCE69581E, 0xE2B11435, 0x5EFDEF50, 0xD0000}};
    int check = 1495735440;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok708) {
    // -2939857929323272.8928078616606
    s21_decimal decimal = {{0xCE69581E, 0xE2B11435, 0x5EFDEF50, 0x800D0000}};
    int check = -651748208;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok709) {
    // 28337472741832.541773302920900
    s21_decimal decimal = {{0x3ED8F6C4, 0x78E0CEA5, 0x5B903543, 0xF0000}};
    int check = 1439575720;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok710) {
    // -28337472741832.541773302920900
    s21_decimal decimal = {{0x3ED8F6C4, 0x78E0CEA5, 0x5B903543, 0x800F0000}};
    int check = -707907928;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok711) {
    // 429822983.66986642929679112504
    s21_decimal decimal = {{0x7CE49938, 0x6535E138, 0x8AE21FB7, 0x140000}};
    int check = 1305277600;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok712) {
    // -429822983.66986642929679112504
    s21_decimal decimal = {{0x7CE49938, 0x6535E138, 0x8AE21FB7, 0x80140000}};
    int check = -842206048;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok713) {
    // -366759903773829859.33234316711
    s21_decimal decimal = {{0xEC6B25A7, 0x42C41491, 0x7681AB0E, 0x800B0000}};
    int check = -593305658;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok714) {
    // 366759903773829859.33234316711
    s21_decimal decimal = {{0xEC6B25A7, 0x42C41491, 0x7681AB0E, 0xB0000}};
    int check = 1554177990;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok715) {
    // -69446999889372.751830274654277
    s21_decimal decimal = {{0xA389C045, 0xA2077341, 0xE065363F, 0x800F0000}};
    int check = -696474225;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok716) {
    // 69446999889372.751830274654277
    s21_decimal decimal = {{0xA389C045, 0xA2077341, 0xE065363F, 0xF0000}};
    int check = 1451009423;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok717) {
    // 3191889863679867815.9669802516
    s21_decimal decimal = {{0x34AB3614, 0x44A15378, 0x6722B1B2, 0xA0000}};
    int check = 1580281724;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok718) {
    // -3191889863679867815.9669802516
    s21_decimal decimal = {{0x34AB3614, 0x44A15378, 0x6722B1B2, 0x800A0000}};
    int check = -567201924;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok719) {
    // 2214001397575.3006793621046921
    s21_decimal decimal = {{0x3F390689, 0x918BF827, 0x4789CA52, 0x100000}};
    int check = 1409343281;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok720) {
    // -2214001397575.3006793621046921
    s21_decimal decimal = {{0x3F390689, 0x918BF827, 0x4789CA52, 0x80100000}};
    int check = -738140367;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok721) {
    // -761.61397777419499924036886445
    s21_decimal decimal = {{0xC1299FAD, 0x7D94539D, 0xF6173B4E, 0x801A0000}};
    int check = -1002543285;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok722) {
    // 761.61397777419499924036886445
    s21_decimal decimal = {{0xC1299FAD, 0x7D94539D, 0xF6173B4E, 0x1A0000}};
    int check = 1144940363;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok723) {
    // -7278598590904284456394952327.4
    s21_decimal decimal = {{0x4B78914A, 0x744506F2, 0xEB2F280A, 0x80010000}};
    int check = -306436678;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok724) {
    // 7278598590904284456394952327.4
    s21_decimal decimal = {{0x4B78914A, 0x744506F2, 0xEB2F280A, 0x10000}};
    int check = 1841046970;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok725) {
    // 188738677872944.70210078213766
    s21_decimal decimal = {{0x75F18686, 0xE8D13527, 0x3CFC18F6, 0xE0000}};
    int check = 1462478886;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok726) {
    // -188738677872944.70210078213766
    s21_decimal decimal = {{0x75F18686, 0xE8D13527, 0x3CFC18F6, 0x800E0000}};
    int check = -685004762;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok727) {
    // -67348665959536417898871452.82
    s21_decimal decimal = {{0xF5DCE542, 0xBC9511D1, 0x15C2F379, 0x80020000}};
    int check = -362883446;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok728) {
    // 67348665959536417898871452.82
    s21_decimal decimal = {{0xF5DCE542, 0xBC9511D1, 0x15C2F379, 0x20000}};
    int check = 1784600202;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok729) {
    // -266237510.0258101058251596496
    s21_decimal decimal = {{0x2AAD22D0, 0x6230CF8A, 0x89A43DB, 0x80130000}};
    int check = -847386780;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok730) {
    // 266237510.0258101058251596496
    s21_decimal decimal = {{0x2AAD22D0, 0x6230CF8A, 0x89A43DB, 0x130000}};
    int check = 1300096868;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok731) {
    // -72993.069385634905652645938673
    s21_decimal decimal = {{0x435D45F1, 0x36EB34B6, 0xEBDA73AC, 0x80180000}};
    int check = -946958199;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok732) {
    // 72993.069385634905652645938673
    s21_decimal decimal = {{0x435D45F1, 0x36EB34B6, 0xEBDA73AC, 0x180000}};
    int check = 1200525449;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok733) {
    // 742687919193011520927.03700468
    s21_decimal decimal = {{0xF95435F4, 0x56C94FEB, 0xEFF9B46D, 0x80000}};
    int check = 1646332790;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok734) {
    // -742687919193011520927.03700468
    s21_decimal decimal = {{0xF95435F4, 0x56C94FEB, 0xEFF9B46D, 0x80080000}};
    int check = -501150858;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok735) {
    // 76310708278046726.902778046020
    s21_decimal decimal = {{0x28A22644, 0xF2C33A08, 0xF692BD08, 0xC0000}};
    int check = 1535610392;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok736) {
    // -76310708278046726.902778046020
    s21_decimal decimal = {{0x28A22644, 0xF2C33A08, 0xF692BD08, 0x800C0000}};
    int check = -611873256;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok737) {
    // 7109514071.866224232859617300
    s21_decimal decimal = {{0xFE6AC814, 0x1A07C84D, 0x16F8DA2A, 0x120000}};
    int check = 1339285834;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok738) {
    // -7109514071.866224232859617300
    s21_decimal decimal = {{0xFE6AC814, 0x1A07C84D, 0x16F8DA2A, 0x80120000}};
    int check = -808197814;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok739) {
    // -3219907.2326172187284624009643
    s21_decimal decimal = {{0x3C3269AB, 0x6716982F, 0x680A72C8, 0x80160000}};
    int check = -901478643;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok740) {
    // 3219907.2326172187284624009643
    s21_decimal decimal = {{0x3C3269AB, 0x6716982F, 0x680A72C8, 0x160000}};
    int check = 1246005005;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok741) {
    // 4906626360522483140.435423304
    s21_decimal decimal = {{0x14A8B048, 0xFB8F5813, 0xFDAAA8B, 0x90000}};
    int check = 1585983405;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok742) {
    // -4906626360522483140.435423304
    s21_decimal decimal = {{0x14A8B048, 0xFB8F5813, 0xFDAAA8B, 0x80090000}};
    int check = -561500243;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok743) {
    // 139910813934508.68056327659020
    s21_decimal decimal = {{0x321F1E0C, 0x1C2C127D, 0x2D3526BA, 0xE0000}};
    int check = 1459519245;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok744) {
    // -139910813934508.68056327659020
    s21_decimal decimal = {{0x321F1E0C, 0x1C2C127D, 0x2D3526BA, 0x800E0000}};
    int check = -687964403;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok745) {
    // 53140874951985192126.326645696
    s21_decimal decimal = {{0xDBF223C0, 0x8940B481, 0xABB519FB, 0x90000}};
    int check = 1614306964;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok746) {
    // -53140874951985192126.326645696
    s21_decimal decimal = {{0xDBF223C0, 0x8940B481, 0xABB519FB, 0x80090000}};
    int check = -533176684;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok747) {
    // -32286397110.827235265149761549
    s21_decimal decimal = {{0x4605780D, 0x76E4E43A, 0x6852AE86, 0x80120000}};
    int check = -789541526;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok748) {
    // 32286397110.827235265149761549
    s21_decimal decimal = {{0x4605780D, 0x76E4E43A, 0x6852AE86, 0x120000}};
    int check = 1357942122;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok749) {
    // 4599581689691898.5271805846450
    s21_decimal decimal = {{0x5ECDA3B2, 0x3E874A09, 0x949ED916, 0xD0000}};
    int check = 1501739613;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok750) {
    // -4599581689691898.5271805846450
    s21_decimal decimal = {{0x5ECDA3B2, 0x3E874A09, 0x949ED916, 0x800D0000}};
    int check = -645744035;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok751) {
    // -63279655278985225160718489.158
    s21_decimal decimal = {{0x415F1646, 0x61672364, 0xCC77B43A, 0x80030000}};
    int check = -363765772;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok752) {
    // 63279655278985225160718489.158
    s21_decimal decimal = {{0x415F1646, 0x61672364, 0xCC77B43A, 0x30000}};
    int check = 1783717876;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok753) {
    // 29698335632975137169629920224
    s21_decimal decimal = {{0xAF523BE0, 0x9FAF1A59, 0x5FF5E330, 0x0}};
    int check = 1858071494;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok754) {
    // -29698335632975137169629920224
    s21_decimal decimal = {{0xAF523BE0, 0x9FAF1A59, 0x5FF5E330, 0x80000000}};
    int check = -289412154;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok755) {
    // -1356790212662.1519684385635176
    s21_decimal decimal = {{0x52AFFB68, 0x1672ADDE, 0x2BD71B08, 0x80100000}};
    int check = -744623232;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok756) {
    // 1356790212662.1519684385635176
    s21_decimal decimal = {{0x52AFFB68, 0x1672ADDE, 0x2BD71B08, 0x100000}};
    int check = 1402860416;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok757) {
    // -1180363682720488652675810112.3
    s21_decimal decimal = {{0xB73A2083, 0x90742526, 0x2623BD52, 0x80010000}};
    int check = -327936017;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok758) {
    // 1180363682720488652675810112.3
    s21_decimal decimal = {{0xB73A2083, 0x90742526, 0x2623BD52, 0x10000}};
    int check = 1819547631;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok759) {
    // 48264603356607231947.64217836
    s21_decimal decimal = {{0xE4244DEC, 0x1121E88F, 0xF985ABB, 0x80000}};
    int check = 1613198228;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok760) {
    // -48264603356607231947.64217836
    s21_decimal decimal = {{0xE4244DEC, 0x1121E88F, 0xF985ABB, 0x80080000}};
    int check = -534285420;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok761) {
    // -7424506528.761769464028458226
    s21_decimal decimal = {{0xE6A7ECF2, 0x67E3902A, 0x17FD6869, 0x80120000}};
    int check = -807582595;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok762) {
    // 7424506528.761769464028458226
    s21_decimal decimal = {{0xE6A7ECF2, 0x67E3902A, 0x17FD6869, 0x120000}};
    int check = 1339901053;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok763) {
    // 5986486.4128109071953412875214
    s21_decimal decimal = {{0x421E3CE, 0x298A8609, 0xC16F0E13, 0x160000}};
    int check = 1253486957;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok764) {
    // -5986486.4128109071953412875214
    s21_decimal decimal = {{0x421E3CE, 0x298A8609, 0xC16F0E13, 0x80160000}};
    int check = -893996691;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok765) {
    // 82523232456574120711.54310536
    s21_decimal decimal = {{0x7EC8DD88, 0x8CBA6F34, 0x1AAA296B, 0x80000}};
    int check = 1619994541;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok766) {
    // -82523232456574120711.54310536
    s21_decimal decimal = {{0x7EC8DD88, 0x8CBA6F34, 0x1AAA296B, 0x80080000}};
    int check = -527489107;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok767) {
    // -4485424553.1326301208224432858
    s21_decimal decimal = {{0x8F8B82DA, 0x835B3169, 0x90EE8FF2, 0x80130000}};
    int check = -813322989;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok768) {
    // 4485424553.1326301208224432858
    s21_decimal decimal = {{0x8F8B82DA, 0x835B3169, 0x90EE8FF2, 0x130000}};
    int check = 1334160659;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok769) {
    // 41332978985143333385533089690
    s21_decimal decimal = {{0xEC2B679A, 0x8CAC5E0D, 0x858DD6C0, 0x0}};
    int check = 1862634967;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok770) {
    // -41332978985143333385533089690
    s21_decimal decimal = {{0xEC2B679A, 0x8CAC5E0D, 0x858DD6C0, 0x80000000}};
    int check = -284848681;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok771) {
    // 5.4331168135659675185310200589
    s21_decimal decimal = {{0x7949F30D, 0x516009C5, 0xAF8DB05E, 0x1C0000}};
    int check = 1085135896;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok772) {
    // -5.4331168135659675185310200589
    s21_decimal decimal = {{0x7949F30D, 0x516009C5, 0xAF8DB05E, 0x801C0000}};
    int check = -1062347752;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok773) {
    // 4455328934399469791522621.7786
    s21_decimal decimal = {{0x1A7D5D3A, 0xE81E8F5A, 0x8FF59DFE, 0x40000}};
    int check = 1751899383;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok774) {
    // -4455328934399469791522621.7786
    s21_decimal decimal = {{0x1A7D5D3A, 0xE81E8F5A, 0x8FF59DFE, 0x80040000}};
    int check = -395584265;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok775) {
    // 503111740454794353602756.0617
    s21_decimal decimal = {{0x1DD4EAA9, 0x84C0A8, 0x1041A48D, 0x40000}};
    int check = 1725240188;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok776) {
    // -503111740454794353602756.0617
    s21_decimal decimal = {{0x1DD4EAA9, 0x84C0A8, 0x1041A48D, 0x80040000}};
    int check = -422243460;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok777) {
    // -3224309022.9373695612955046671
    s21_decimal decimal = {{0xEC02B30F, 0xB776B59F, 0x682EDBEF, 0x80130000}};
    int check = -817877235;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok778) {
    // 3224309022.9373695612955046671
    s21_decimal decimal = {{0xEC02B30F, 0xB776B59F, 0x682EDBEF, 0x130000}};
    int check = 1329606413;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok779) {
    // -771245569547042963.56274339516
    s21_decimal decimal = {{0x67D7EBC, 0x1D164277, 0xF933F032, 0x800B0000}};
    int check = -584368068;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok780) {
    // 771245569547042963.56274339516
    s21_decimal decimal = {{0x67D7EBC, 0x1D164277, 0xF933F032, 0xB0000}};
    int check = 1563115580;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok781) {
    // 666018717813209424561451.70439
    s21_decimal decimal = {{0x8B53D007, 0xD86FFF57, 0xD733C6EF, 0x50000}};
    int check = 1728907506;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok782) {
    // -666018717813209424561451.70439
    s21_decimal decimal = {{0x8B53D007, 0xD86FFF57, 0xD733C6EF, 0x80050000}};
    int check = -418576142;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok783) {
    // -588632747869359473511469.07700
    s21_decimal decimal = {{0xB8DC4834, 0x2E2BFB66, 0xBE328F48, 0x80050000}};
    int check = -419869775;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok784) {
    // 588632747869359473511469.07700
    s21_decimal decimal = {{0xB8DC4834, 0x2E2BFB66, 0xBE328F48, 0x50000}};
    int check = 1727613873;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok785) {
    // -6616457517630031351787981029.3
    s21_decimal decimal = {{0xBC9958F5, 0x62E2306E, 0xD5CA0DC7, 0x80010000}};
    int check = -307558389;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok786) {
    // 6616457517630031351787981029.3
    s21_decimal decimal = {{0xBC9958F5, 0x62E2306E, 0xD5CA0DC7, 0x10000}};
    int check = 1839925259;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok787) {
    // 687125853453535333118.86546320
    s21_decimal decimal = {{0x48A7D590, 0x6D285708, 0xDE05B7EB, 0x80000}};
    int check = 1645543206;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok788) {
    // -687125853453535333118.86546320
    s21_decimal decimal = {{0x48A7D590, 0x6D285708, 0xDE05B7EB, 0x80080000}};
    int check = -501940442;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok789) {
    // 465631022936562317405517.5053
    s21_decimal decimal = {{0x7569A38D, 0x527DF287, 0xF0B9C0B, 0x40000}};
    int check = 1724199889;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok790) {
    // -465631022936562317405517.5053
    s21_decimal decimal = {{0x7569A38D, 0x527DF287, 0xF0B9C0B, 0x80040000}};
    int check = -423283759;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok791) {
    // -6556307281622.5532719246388173
    s21_decimal decimal = {{0x56A8ABCD, 0x1BDDBB2C, 0xD3D880B3, 0x80100000}};
    int check = -725692340;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok792) {
    // 6556307281622.5532719246388173
    s21_decimal decimal = {{0x56A8ABCD, 0x1BDDBB2C, 0xD3D880B3, 0x100000}};
    int check = 1421791308;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok793) {
    // 432698166.71707846622195781223
    s21_decimal decimal = {{0x298C8E67, 0xECFE6E47, 0x8BCFF415, 0x140000}};
    int check = 1305367450;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok794) {
    // -432698166.71707846622195781223
    s21_decimal decimal = {{0x298C8E67, 0xECFE6E47, 0x8BCFF415, 0x80140000}};
    int check = -842116198;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok795) {
    // -12045234722591910729.271482683
    s21_decimal decimal = {{0xD840193B, 0xB77309D7, 0x26EB95AA, 0x80090000}};
    int check = -551081659;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok796) {
    // 12045234722591910729.271482683
    s21_decimal decimal = {{0xD840193B, 0xB77309D7, 0x26EB95AA, 0x90000}};
    int check = 1596401989;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok797) {
    // -3505368.8071945329077039935900
    s21_decimal decimal = {{0x408C319C, 0xFC620E9, 0x7143BB2E, 0x80160000}};
    int check = -900336797;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok798) {
    // 3505368.8071945329077039935900
    s21_decimal decimal = {{0x408C319C, 0xFC620E9, 0x7143BB2E, 0x160000}};
    int check = 1247146851;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok799) {
    // 3676.4289823937310013081519767
    s21_decimal decimal = {{0x37400697, 0xD998242A, 0x76CAB530, 0x190000}};
    int check = 1164297949;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok800) {
    // -3676.4289823937310013081519767
    s21_decimal decimal = {{0x37400697, 0xD998242A, 0x76CAB530, 0x80190000}};
    int check = -983185699;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok801) {
    // -306771040044.55501441838072787
    s21_decimal decimal = {{0xE6FFC3D3, 0x5C16AEE4, 0x631F8174, 0x80110000}};
    int check = -762390027;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok802) {
    // 306771040044.55501441838072787
    s21_decimal decimal = {{0xE6FFC3D3, 0x5C16AEE4, 0x631F8174, 0x110000}};
    int check = 1385093621;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok803) {
    // 294535749003615.85437472356002
    s21_decimal decimal = {{0xF7CE76A2, 0xB8C9B4AF, 0x5F2B6D16, 0xE0000}};
    int check = 1468395641;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok804) {
    // -294535749003615.85437472356002
    s21_decimal decimal = {{0xF7CE76A2, 0xB8C9B4AF, 0x5F2B6D16, 0x800E0000}};
    int check = -679088007;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok805) {
    // 68775081.832095914483970785653
    s21_decimal decimal = {{0x8684C175, 0xC2E6F8C2, 0xDE396A10, 0x150000}};
    int check = 1283665301;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok806) {
    // -68775081.832095914483970785653
    s21_decimal decimal = {{0x8684C175, 0xC2E6F8C2, 0xDE396A10, 0x80150000}};
    int check = -863818347;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok807) {
    // 5238827880765001589958524369.3
    s21_decimal decimal = {{0xDB1E6A2D, 0xCD309BBF, 0xA946918C, 0x10000}};
    int check = 1837591464;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok808) {
    // -5238827880765001589958524369.3
    s21_decimal decimal = {{0xDB1E6A2D, 0xCD309BBF, 0xA946918C, 0x80010000}};
    int check = -309892184;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok809) {
    // 1193514.5231984993486934590053
    s21_decimal decimal = {{0xB1AB4265, 0x78EFAA0F, 0x2690854F, 0x160000}};
    int check = 1234284884;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok810) {
    // -1193514.5231984993486934590053
    s21_decimal decimal = {{0xB1AB4265, 0x78EFAA0F, 0x2690854F, 0x80160000}};
    int check = -913198764;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok811) {
    // -6616011540752.2723580938799890
    s21_decimal decimal = {{0x5F6FCB12, 0xD61DC20E, 0xD5C65D62, 0x80100000}};
    int check = -725578463;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok812) {
    // 6616011540752.2723580938799890
    s21_decimal decimal = {{0x5F6FCB12, 0xD61DC20E, 0xD5C65D62, 0x100000}};
    int check = 1421905185;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok813) {
    // -3994686533530535920140355.9557
    s21_decimal decimal = {{0xF90A5E85, 0x6B4E8A4, 0x811345C5, 0x80040000}};
    int check = -397182439;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok814) {
    // 3994686533530535920140355.9557
    s21_decimal decimal = {{0xF90A5E85, 0x6B4E8A4, 0x811345C5, 0x40000}};
    int check = 1750301209;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok815) {
    // 6690605431871039954.4642264986
    s21_decimal decimal = {{0xB8F85F9A, 0x3D2BC435, 0xD82F6418, 0xA0000}};
    int check = 1589228444;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok816) {
    // -6690605431871039954.4642264986
    s21_decimal decimal = {{0xB8F85F9A, 0x3D2BC435, 0xD82F6418, 0x800A0000}};
    int check = -558255204;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok817) {
    // 5916373466874.8502172174844184
    s21_decimal decimal = {{0x98C70118, 0x2BA3A36, 0xBF2B1823, 0x100000}};
    int check = 1420570731;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok818) {
    // -5916373466874.8502172174844184
    s21_decimal decimal = {{0x98C70118, 0x2BA3A36, 0xBF2B1823, 0x80100000}};
    int check = -726912917;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok819) {
    // -6951465962447402.8790955244921
    s21_decimal decimal = {{0x65D1FD79, 0x38E5C678, 0xE09D2DC1, 0x800D0000}};
    int check = -641363310;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok820) {
    // 6951465962447402.8790955244921
    s21_decimal decimal = {{0x65D1FD79, 0x38E5C678, 0xE09D2DC1, 0xD0000}};
    int check = 1506120338;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok821) {
    // 5809.5625779706301320654144754
    s21_decimal decimal = {{0x4AE6C4F2, 0x1CF5980D, 0xBBB79348, 0x190000}};
    int check = 1169525888;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok822) {
    // -5809.5625779706301320654144754
    s21_decimal decimal = {{0x4AE6C4F2, 0x1CF5980D, 0xBBB79348, 0x80190000}};
    int check = -977957760;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok823) {
    // -3903169292860282406573686.0552
    s21_decimal decimal = {{0xA64D6388, 0x72EC0975, 0x7E1E4279, 0x80040000}};
    int check = -397499953;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok824) {
    // 3903169292860282406573686.0552
    s21_decimal decimal = {{0xA64D6388, 0x72EC0975, 0x7E1E4279, 0x40000}};
    int check = 1749983695;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok825) {
    // 27648401857949296392091685661
    s21_decimal decimal = {{0x1393531D, 0x1CDA653, 0x595638D4, 0x0}};
    int check = 1857203314;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok826) {
    // -27648401857949296392091685661
    s21_decimal decimal = {{0x1393531D, 0x1CDA653, 0x595638D4, 0x80000000}};
    int check = -290280334;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok827) {
    // 71291785.14403755577635988124
    s21_decimal decimal = {{0x601B629C, 0xAAECDB42, 0x17091E45, 0x140000}};
    int check = 1283979889;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok828) {
    // -71291785.14403755577635988124
    s21_decimal decimal = {{0x601B629C, 0xAAECDB42, 0x17091E45, 0x80140000}};
    int check = -863503759;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok829) {
    // -868.4787200025246838280164675
    s21_decimal decimal = {{0x33641543, 0x7DF93255, 0x1C0FE339, 0x80190000}};
    int check = -1000792413;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok830) {
    // 868.4787200025246838280164675
    s21_decimal decimal = {{0x33641543, 0x7DF93255, 0x1C0FE339, 0x190000}};
    int check = 1146691235;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok831) {
    // -1486.6783843035280525419492011
    s21_decimal decimal = {{0xE4CA32AB, 0x649B86E, 0x300983EF, 0x80190000}};
    int check = -994454091;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok832) {
    // 1486.6783843035280525419492011
    s21_decimal decimal = {{0xE4CA32AB, 0x649B86E, 0x300983EF, 0x190000}};
    int check = 1153029557;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok833) {
    // 412776511414768501.39765889131
    s21_decimal decimal = {{0xA7CB586B, 0x2267EAAD, 0x856012A0, 0xB0000}};
    int check = 1555517250;

    test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok834) {
    // -412776511414768501.39765889131
    s21_decimal decimal = {{0xA7CB586B, 0x2267EAAD, 0x856012A0, 0x800B0000}};
    int check = -591966398;

    test_from_decimal_to_float(decimal, check);
}


Suite * from_decimal_to_float_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_decimal_to_float_ok1);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok2);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok3);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok4);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok5);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok6);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok7);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok8);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok9);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok10);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok11);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok12);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok13);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok14);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok15);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok16);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok17);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok18);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok19);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok20);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok21);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok22);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok23);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok24);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok25);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok26);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok27);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok28);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok29);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok30);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok31);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok32);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok33);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok34);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok35);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok36);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok37);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok38);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok39);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok40);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok41);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok42);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok43);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok44);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok45);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok46);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok47);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok48);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok49);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok50);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok51);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok52);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok53);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok54);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok55);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok56);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok57);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok58);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok59);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok60);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok61);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok62);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok63);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok64);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok65);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok66);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok67);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok68);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok69);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok70);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok71);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok72);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok73);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok74);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok75);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok76);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok77);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok78);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok79);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok80);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok81);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok82);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok83);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok84);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok85);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok86);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok87);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok88);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok89);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok90);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok91);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok92);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok93);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok94);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok95);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok96);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok97);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok98);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok99);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok100);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok101);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok102);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok103);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok104);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok105);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok106);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok107);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok108);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok109);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok110);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok111);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok112);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok113);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok114);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok115);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok116);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok117);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok118);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok119);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok120);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok121);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok122);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok123);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok124);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok125);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok126);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok127);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok128);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok129);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok130);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok131);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok132);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok133);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok134);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok135);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok136);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok137);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok138);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok139);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok140);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok141);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok142);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok143);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok144);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok145);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok146);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok147);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok148);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok149);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok150);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok151);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok152);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok153);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok154);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok155);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok156);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok157);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok158);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok159);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok160);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok161);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok162);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok163);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok164);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok165);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok166);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok167);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok168);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok169);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok170);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok171);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok172);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok173);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok174);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok175);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok176);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok177);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok178);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok179);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok180);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok181);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok182);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok183);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok184);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok185);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok186);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok187);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok188);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok189);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok190);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok191);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok192);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok193);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok194);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok195);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok196);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok197);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok198);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok199);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok200);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok201);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok202);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok203);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok204);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok205);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok206);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok207);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok208);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok209);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok210);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok211);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok212);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok213);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok214);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok215);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok216);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok217);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok218);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok219);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok220);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok221);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok222);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok223);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok224);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok225);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok226);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok227);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok228);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok229);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok230);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok231);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok232);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok233);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok234);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok235);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok236);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok237);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok238);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok239);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok240);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok241);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok242);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok243);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok244);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok245);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok246);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok247);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok248);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok249);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok250);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok251);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok252);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok253);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok254);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok255);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok256);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok257);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok258);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok259);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok260);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok261);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok262);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok263);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok264);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok265);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok266);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok267);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok268);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok269);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok270);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok271);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok272);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok273);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok274);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok275);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok276);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok277);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok278);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok279);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok280);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok281);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok282);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok283);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok284);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok285);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok286);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok287);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok288);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok289);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok290);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok291);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok292);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok293);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok294);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok295);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok296);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok297);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok298);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok299);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok300);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok301);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok302);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok303);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok304);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok305);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok306);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok307);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok308);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok309);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok310);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok311);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok312);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok313);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok314);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok315);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok316);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok317);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok318);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok319);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok320);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok321);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok322);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok323);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok324);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok325);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok326);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok327);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok328);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok329);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok330);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok331);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok332);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok333);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok334);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok335);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok336);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok337);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok338);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok339);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok340);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok341);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok342);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok343);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok344);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok345);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok346);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok347);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok348);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok349);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok350);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok351);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok352);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok353);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok354);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok355);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok356);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok357);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok358);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok359);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok360);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok361);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok362);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok363);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok364);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok365);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok366);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok367);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok368);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok369);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok370);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok371);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok372);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok373);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok374);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok375);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok376);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok377);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok378);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok379);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok380);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok381);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok382);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok383);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok384);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok385);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok386);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok387);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok388);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok389);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok390);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok391);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok392);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok393);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok394);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok395);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok396);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok397);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok398);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok399);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * from_decimal_to_float_suite2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_decimal_to_float_ok401);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok402);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok403);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok404);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok405);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok406);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok407);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok408);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok409);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok410);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok411);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok412);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok413);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok414);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok415);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok416);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok417);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok418);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok419);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok420);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok421);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok422);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok423);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok424);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok425);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok426);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok427);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok428);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok429);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok430);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok431);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok432);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok433);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok434);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok435);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok436);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok437);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok438);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok439);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok440);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok441);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok442);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok443);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok444);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok445);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok446);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok447);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok448);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok449);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok450);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok451);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok452);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok453);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok454);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok455);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok456);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok457);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok458);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok459);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok460);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok461);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok462);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok463);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok464);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok465);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok466);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok467);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok468);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok469);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok470);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok471);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok472);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok473);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok474);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok475);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok476);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok477);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok478);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok479);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok480);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok481);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok482);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok483);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok484);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok485);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok486);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok487);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok488);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok489);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok490);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok491);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok492);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok493);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok494);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok495);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok496);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok497);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok498);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok499);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok500);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok501);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok502);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok503);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok504);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok505);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok506);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok507);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok508);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok509);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok510);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok511);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok512);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok513);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok514);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok515);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok516);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok517);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok518);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok519);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok520);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok521);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok522);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok523);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok524);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok525);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok526);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok527);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok528);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok529);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok530);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok531);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok532);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok533);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok534);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok535);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok536);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok537);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok538);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok539);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok540);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok541);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok542);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok543);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok544);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok545);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok546);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok547);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok548);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok549);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok550);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok551);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok552);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok553);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok554);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok555);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok556);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok557);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok558);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok559);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok560);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok561);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok562);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok563);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok564);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok565);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok566);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok567);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok568);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok569);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok570);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok571);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok572);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok573);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok574);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok575);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok576);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok577);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok578);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok579);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok580);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok581);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok582);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok583);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok584);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok585);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok586);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok587);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok588);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok589);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok590);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok591);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok592);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok593);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok594);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok595);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok596);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok597);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok598);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok599);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok600);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok601);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok602);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok603);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok604);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok605);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok606);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok607);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok608);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok609);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok610);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok611);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok612);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok613);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok614);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok615);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok616);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok617);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok618);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok619);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok620);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok621);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok622);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok623);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok624);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok625);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok626);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok627);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok628);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok629);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok630);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok631);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok632);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok633);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok634);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok635);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok636);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok637);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok638);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok639);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok640);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok641);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok642);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok643);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok644);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok645);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok646);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok647);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok648);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok649);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok650);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok651);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok652);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok653);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok654);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok655);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok656);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok657);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok658);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok659);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok660);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok661);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok662);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok663);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok664);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok665);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok666);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok667);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok668);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok669);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok670);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok671);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok672);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok673);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok674);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok675);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok676);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok677);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok678);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok679);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok680);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok681);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok682);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok683);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok684);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok685);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok686);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok687);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok688);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok689);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok690);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok691);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok692);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok693);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok694);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok695);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok696);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok697);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok698);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok699);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok700);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok701);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok702);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok703);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok704);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok705);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok706);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok707);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok708);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok709);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok710);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok711);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok712);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok713);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok714);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok715);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok716);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok717);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok718);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok719);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok720);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok721);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok722);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok723);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok724);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok725);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok726);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok727);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok728);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok729);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok730);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok731);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok732);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok733);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok734);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok735);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok736);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok737);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok738);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok739);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok740);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok741);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok742);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok743);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok744);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok745);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok746);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok747);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok748);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok749);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok750);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok751);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok752);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok753);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok754);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok755);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok756);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok757);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok758);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok759);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok760);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok761);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok762);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok763);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok764);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok765);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok766);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok767);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok768);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok769);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok770);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok771);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok772);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok773);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok774);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok775);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok776);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok777);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok778);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok779);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok780);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok781);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok782);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok783);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok784);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok785);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok786);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok787);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok788);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok789);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok790);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok791);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok792);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok793);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok794);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok795);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok796);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok797);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok798);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok799);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok800);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * from_decimal_to_float_suite3(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug3");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_decimal_to_float_ok801);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok802);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok803);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok804);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok805);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok806);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok807);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok808);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok809);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok810);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok811);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok812);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok813);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok814);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok815);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok816);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok817);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok818);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok819);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok820);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok821);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok822);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok823);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok824);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok825);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok826);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok827);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok828);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok829);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok830);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok831);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok832);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok833);
    tcase_add_test(tc_core, test_from_decimal_to_float_ok834);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * from_decimal_to_float_suite0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_decimal_to_float0");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual1);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual2);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual3);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual4);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual5);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual6);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual7);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual8);
    tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual9);

    suite_add_tcase(s, tc_core);
    return s;
}

void test_from_decimal_to_float(s21_decimal decimal, int check) {
    float result;
    printf("de:"); s21_print_decimal_string(decimal);
    int code = s21_from_decimal_to_float(decimal, &result);
    printf("re:%f\n", result);

    float_cast cast;
    cast.f = result;

    printf("re:%d\n", cast.int32_bytes);
    printf("ch:%d\n", check);
    printf("re:"); s21_print_bit(cast.bytes, 0); printf("\n");
    printf("ch:"); s21_print_bit(check, 0); printf("\n");


    ck_assert_int_eq(cast.int32_bytes, check);
    ck_assert_int_eq(code, S21_CONVERSION_OK);
}

void test_from_decimal_to_float_fail(s21_decimal decimal) {
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);

    ck_assert_int_eq(code, S21_CONVERSION_ERROR);
}
