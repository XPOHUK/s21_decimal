//
// Created by gubankov on 06.08.22.
//

#ifndef DECIMAL_BIG_DECIMAL_H
#define DECIMAL_BIG_DECIMAL_H

#include "../types.h"

typedef struct big_decimal {
    s21_decimal low;
    s21_decimal over;
} big_decimal;

big_decimal big_decimal_and(big_decimal first, big_decimal second);
big_decimal big_decimal_xor(big_decimal first, big_decimal second);
big_decimal big_decimal_not(big_decimal in);

big_decimal big_decimal_get_bit(int index);
int big_decimal_is_set_bit(big_decimal in, int index);
big_decimal big_decimal_set_bit(big_decimal in, int index);
big_decimal big_decimal_flip_bit(big_decimal in, int index);
int big_decimal_get_sign(big_decimal in);
big_decimal big_decimal_set_sign(big_decimal in, int sign);
big_decimal big_decimal_change_sign(big_decimal in);

big_decimal big_decimal_get_zero(void);
big_decimal big_decimal_to_twos_complement(big_decimal direct_code);

big_decimal big_decimal_incr(big_decimal in);

big_decimal big_decimal_shift_left(big_decimal in, int shifts);
big_decimal big_decimal_shift_right(big_decimal in, int shifts);

int big_decimal_div(big_decimal in, big_decimal divisor, big_decimal *result, big_decimal *remainder);

s21_decimal big_decimal_round_to_decimal(big_decimal in);

int big_decimal_is_zero(big_decimal in);
int big_decimal_get_exp(big_decimal in);
void big_decimal_set_exp(big_decimal in, int exp);
#endif //DECIMAL_BIG_DECIMAL_H
