//
// Created by gubankov on 06.08.22.
//

#ifndef DECIMAL_BIG_DECIMAL_H
#define DECIMAL_BIG_DECIMAL_H

#include "../types.h"

// 0,1,2 -- соответствующие части decimal. Четвёртый int записываем в parts[6] и переставляем или дублируем
// знаковый бит из 31 в 0
typedef struct big_decimal {
    unsigned int parts[7];
} big_decimal;

big_decimal decimal_to_big_decimal(s21_decimal in);
s21_decimal big_decimal_to_decimal(big_decimal in);

big_decimal big_decimal_and(big_decimal first, big_decimal second);
big_decimal big_decimal_xor(big_decimal first, big_decimal second);
big_decimal big_decimal_not(big_decimal in);

big_decimal big_decimal_get_bit(int index);
unsigned int big_decimal_is_set_bit(big_decimal in, int index);
big_decimal big_decimal_set_bit(big_decimal in, int index);
big_decimal big_decimal_flip_bit(big_decimal in, int index);
unsigned int big_decimal_get_sign(big_decimal in);
big_decimal big_decimal_set_sign(big_decimal in, int sign);
big_decimal big_decimal_change_sign(big_decimal in);

big_decimal big_decimal_get_zero(void);
big_decimal big_decimal_to_twos_complement(big_decimal direct_code);

big_decimal big_decimal_incr(big_decimal in);

big_decimal big_decimal_shift_left(big_decimal in, int shifts);
big_decimal big_decimal_shift_right(big_decimal in, int shifts);

int big_decimal_div(big_decimal in, big_decimal divisor, big_decimal *result, big_decimal *remainder);

int big_decimal_round_to_decimal(big_decimal in, s21_decimal * res);

unsigned int big_decimal_is_zero(big_decimal in);
int big_decimal_get_exp(big_decimal in);
void big_decimal_set_exp(big_decimal* in, int exp);
unsigned int big_decimal_get_not_zero_bit(big_decimal in);

big_decimal big_decimal_add_mant(big_decimal first, big_decimal second);
big_decimal big_decimal_mul_mant(big_decimal first, big_decimal second);
#endif //DECIMAL_BIG_DECIMAL_H
