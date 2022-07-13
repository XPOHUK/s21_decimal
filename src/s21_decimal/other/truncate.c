#include <stdio.h>
#include "./other.h"
#include "./../_debug/_debug.h"
#include "./../helpers/helpers.h"
#include "./../binary/binary.h"

/**
 * 
 * @param value 
 * @param result 
 * @return int 
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;
    s21_clear_decimal(result);
    // *result = value;

    // 10 = 2^3 + 2^2

    s21_print_decimal_string(value);
    printf("(%d)(%d)\n", value.bits[0], value.bits[1]);
    printf("(%d)(%d)\n", value.bits[1] / 10, value.bits[1] / 10);

    result->bits[0] = value.bits[0] / 10;
    result->bits[1] = value.bits[1] / 10;
    s21_print_decimal_string(*result);
    printf("\n\n");

    int a = 213;
    // int a = 2000000;
    int b = 17;
    // int b = 7;
    int a_left = 0;
    int b_left = 0;

    printf("a:\n");s21_print_bit(a, 0);printf("\n");
    for (int i = 0; i < 32; i++) {
        // printf("{%d}", s21_is_set_bit(a, 31-i));
        if (s21_is_set_bit(a, 31-i) != 0) {
            a_left = i;
            break;
        }
    }
    printf("\n{%d}\n", a_left);

    printf("b:\n");s21_print_bit(b, 0);printf("\n");
    for (int i = 0; i < 32; i++) {
        // printf("{%d}", s21_is_set_bit(b, 31-i));
        if (s21_is_set_bit(b, 31-i) != 0) {
            b_left = i;
            break;
        }
    }
    printf("\n{%d}\n", b_left);
    printf("\n{%d}\n", b_left - a_left);

    int shifted_b = b << (b_left - a_left);
    s21_print_bit(shifted_b, 0);printf("\n");
    int inverse_shifted_b = ~shifted_b;
    s21_print_bit(inverse_shifted_b, 0); printf("\n");

    int ones_complement_b = inverse_shifted_b + 1;
    printf("comp:\n");s21_print_bit(ones_complement_b, 0); printf("\n");printf("\n");printf("\n");

    int k = b_left - a_left;
    // int tmp;
    int del = a;
    unsigned int ostatok = 0;
    int is_overflow = 1;

    int rrrrr = 0;
    int kk = k;
    while (kk >= 0) {

        unsigned int val2;

        if (is_overflow == 1)
            val2 = ones_complement_b; 
        else
            val2 = shifted_b;

        is_overflow = 0;
        unsigned int sum = del;

        while (val2 > 0) {
            printf("------------\n");
            printf("+");s21_print_bit(sum, 0); printf("\n");
            printf("+");s21_print_bit(val2, 0); printf("\n");
            int overflow = sum & val2;

            overflow = overflow << 1;
            if (s21_is_set_bit(overflow, 31) != 0 && is_overflow == 0) {
                is_overflow = 1;
            }
            // s21_print_bit(overflow, 0); printf("\n");
            sum = sum^val2;
            printf("=");s21_print_bit(sum, 0); printf("\n");
            val2 = overflow;
            printf("overflow:\n ");s21_print_bit(overflow, 0); printf("\n");
            printf("------------\n");
        }
        rrrrr = rrrrr << 1;
        if (is_overflow == 1) {
            rrrrr = s21_set_bit(rrrrr, 0);
        }

        printf("is_overflow{%d}\n", is_overflow);
        // tmp = del + ones_complement_b;
        // printf("++:\n");s21_print_bit(tmp, 0); printf("\n");
        ostatok = sum;
        del = sum << 1;
        printf("++:\n");s21_print_bit(sum, 0); printf("\n");
        printf("<<:\n");s21_print_bit(del, 0); printf("\n");
        kk--;
        printf("\n");
    }
s21_print_bit(ostatok, 0); printf("\n");
    if (s21_is_set_bit(ostatok, 31)) {
        ostatok = ostatok + shifted_b;
    }
s21_print_bit(ostatok, 0); printf("\n");
    ostatok = ostatok >> k;
s21_print_bit(ostatok, 0); printf("\n");
    printf("[[%d]]\n", rrrrr);
    printf("[[%d]]\n", ostatok);
    s21_print_bit(rrrrr, 0); printf("\n");
    s21_print_bit(ostatok, 0); printf("\n");



    printf("\n\n");

    s21_decimal decimal_a = s21_decimal_get_zero();
    s21_decimal decimal_b = s21_decimal_get_zero();
    decimal_a.bits[0] = 1073741823;
    // decimal_a.bits[0] = 8590751;
    // decimal_a.bits[0]= 523986431;
    
    // decimal_a = s21_create_decimal_from_strings(
    //     "11111111 11111111 11111111 11111111",
    //     "11111111 11111111 11111111 11111111",
    //     "11000000 00000000 00000000 00000001",
    //     "10000000 00011100 00000000 00000000");
    decimal_b.bits[0] = 1073741;
    // decimal_b.bits[0] = 1073741;
    // decimal_b.bits[0] = 1073741;
    
    // decimal_b = s21_create_decimal_from_strings(
    //     "11111111 11111111 11111111 11111111",
    //     "11111111 11111111 11111111 11111111",
    //     "11000000 00000000 00000000 00000001",
    //     "10000000 00011100 00000000 00000000");

    printf("a:");s21_print_decimal_bits(decimal_a);
    printf("b:");s21_print_decimal_bits(decimal_b);

    s21_decimal decimal_a_plus_b;
    s21_decimal decimal_a_minus_b;
    s21_decimal decimal_a_del_b;

    decimal_a_plus_b = s21_decimal_binary_addition(decimal_a, decimal_b);

    printf("\n\n");
    printf("+:");s21_print_decimal_bits(decimal_a_plus_b);

    decimal_a_minus_b = s21_decimal_binary_subtraction(decimal_a, decimal_b);
    printf("\n\n");
    printf("-:");s21_print_decimal_bits(decimal_a_minus_b);

    decimal_a_del_b = s21_decimal_binary_division(decimal_a, decimal_b);
    printf("\n\n");
    printf("\\:");s21_print_decimal_bits(decimal_a_del_b);

    // printf("\n\n");
    // s21_decimal decimal = s21_create_decimal_from_strings(
    //     "11111110 11111110 11111110 11111110",
    //     "11111100 11111100 11111100 11111100",
    //     "11111000 11111000 11111000 11111000",
    //     "11110000 11110000 11110000 11110000");
    // printf("d:");s21_print_decimal_bits(decimal);
    // s21_decimal rrr = s21_decimal_binary_shift_right(decimal, 64);
    // printf("r:");s21_print_decimal_bits(rrr);

    printf("\n\n");
    return code;
}
