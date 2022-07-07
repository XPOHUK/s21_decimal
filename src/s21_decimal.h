#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdint.h>

typedef struct {
    int bits[4];
} s21_decimal;

typedef union {
    int i;
    struct {
        uint32_t empty2 : 16;
        uint32_t power : 8;
        uint32_t empty1 : 7;
        uint32_t sign : 1;
    } parts;
} decimal_bit3;

int s21_is_correct_decimal(s21_decimal decimal);
int s21_decimal_get_sign(s21_decimal decimal);
int s21_decimal_get_power(s21_decimal decimal);
int s21_decimal_get_empty1(s21_decimal decimal);
int s21_decimal_get_empty2(s21_decimal decimal);

void s21_print_decimal_bits(s21_decimal decimal);
void s21_print_decimal_string(s21_decimal decimal);

#endif  //  SRC_S21_DECIMAL_H_
