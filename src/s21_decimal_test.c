#include <stdlib.h>
#include <stdio.h>

#include "./tests/test.h"
#include "./s21_decimal.h"

int main(void) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    s21_print_decimal_bits(decimal);
    s21_print_decimal_string(decimal);

    // 1000000000
    s21_decimal decimal2 = {{0x3B9ACA00, 0x0, 0x0, 0x0}};
    s21_print_decimal_bits(decimal2);
    s21_print_decimal_string(decimal2);

    // 4294967296000000000
    s21_decimal decimal3 = {{0x0, 0x3B9ACA00, 0x0, 0x0}};
    s21_print_decimal_bits(decimal3);
    s21_print_decimal_string(decimal3);

    // 18446744073709551616000000000
    s21_decimal decimal4 = {{0x0, 0x0, 0x3B9ACA00, 0x0}};   
    s21_print_decimal_bits(decimal4);
    s21_print_decimal_string(decimal4);

    // 79228162514264337593543950335
    s21_decimal decimal5 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};   
    s21_print_decimal_bits(decimal5);
    s21_print_decimal_string(decimal5);

    // -79228162514264337593543950335
    s21_decimal decimal6 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    s21_print_decimal_bits(decimal6);
    s21_print_decimal_string(decimal6);

    // 0.0000000000000000004294967295
    s21_decimal decimal7 = {{0xFFFFFFFF, 0x0, 0x0, 0x1C0000}};
    s21_print_decimal_bits(decimal7);
    s21_print_decimal_string(decimal7);

    // 0.0000004294967295
    s21_decimal decimal8 = {{0xFFFFFFFF, 0x0, 0x0, 0x100000}};
    s21_print_decimal_bits(decimal8);
    s21_print_decimal_string(decimal8);

    // 0.4294967295
    s21_decimal decimal9 = {{0xFFFFFFFF, 0x0, 0x0, 0xA0000}};
    s21_print_decimal_bits(decimal9);
    s21_print_decimal_string(decimal9);

    // 4.294967295
    s21_decimal decimal10 = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    s21_print_decimal_bits(decimal10);
    s21_print_decimal_string(decimal10);

    // -4.294967295
    s21_decimal decimal11 = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    s21_print_decimal_bits(decimal11);
    s21_print_decimal_string(decimal11);

    // 429496729.5
    s21_decimal decimal12 = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    s21_print_decimal_bits(decimal12);
    s21_print_decimal_string(decimal12);

    // 18133887298.441562272235520
    s21_decimal decimal13 = {{0xF0000, 0xF0000, 0xF0000, 0xF0000}};
    s21_print_decimal_bits(decimal13);
    s21_print_decimal_string(decimal13);

    // -0.000000000
    // но если делать по образу и подобию C#, то должно быть 0.000000000, там во всех операциях 0 вместо -0
    // включая toString
    s21_decimal decimal14 = {{0x0, 0x0, 0x0, 0x80090000}};
    s21_print_decimal_bits(decimal14);
    s21_print_decimal_string(decimal14);

    // 0.0000000000000000000000000000
    s21_decimal decimal15 = {{0x0, 0x0, 0x0, 0x1C0000}};
    s21_print_decimal_bits(decimal15);
    s21_print_decimal_string(decimal15);

    // s21_decimal decimal16 = {};
    // s21_print_decimal_bits(decimal16);
    // s21_print_decimal_string(decimal16);

    // printf("[%u][%d]\n", 0xFFFFFFFF, 0xFFFFFFFF);
    // printf("[%u][%d]\n", 0x80090000, 0x80090000);
    // printf("[%u][%d]\n", 0x80000000, 0x80000000);
    // printf("[%u][%d]\n", 0x8000001C, 0x8000001C);
    // printf("[%u][%d]\n", 0x401C0000, 0x401C0000);

    s21_decimal decimal_fail1 = {{0, 0, 0, 1000000000}};
    s21_print_decimal_bits(decimal_fail1);
    s21_print_decimal_string(decimal_fail1);

    s21_decimal decimal_fail2 = {{-1, 0, 0, 0x1D0000}};
    s21_print_decimal_bits(decimal_fail2);
    s21_print_decimal_string(decimal_fail2);

    s21_decimal decimal_fail3 = {{0, 0, 0, 0x1D0000}};
    s21_print_decimal_bits(decimal_fail3);
    s21_print_decimal_string(decimal_fail3);

    s21_decimal decimal_fail4 = {{-1, 0, 0, 0x1C0001}};
    s21_print_decimal_bits(decimal_fail4);
    s21_print_decimal_string(decimal_fail4);

    s21_decimal decimal_fail5 = {{-1, 0, 0, 0x1C8000}};
    s21_print_decimal_bits(decimal_fail5);
    s21_print_decimal_string(decimal_fail5);

    s21_decimal decimal_fail6 = {{-1, 0, 0, 0x11C0000}};
    s21_print_decimal_bits(decimal_fail6);
    s21_print_decimal_string(decimal_fail6);

    s21_decimal decimal_fail7 = {{-1, 0, 0, 0x401C0000}};
    s21_print_decimal_bits(decimal_fail7);
    s21_print_decimal_string(decimal_fail7);

// 00000000 00011100 10000000 00000000
// 00000001 00011100 00000000 00000000
// 01000000 00011100 00000000 00000000

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

    return EXIT_SUCCESS;
}
