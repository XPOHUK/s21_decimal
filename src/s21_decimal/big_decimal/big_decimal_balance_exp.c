//
// Created by gubankov on 10.08.22.
//
#include <stddef.h>

#include "big_decimal.h"

void big_decimal_balance_exp(big_decimal* first, big_decimal* second) {
    big_decimal* to_balance = NULL;
    int diff = big_decimal_get_exp(*first) - big_decimal_get_exp(*second);
    if (diff > 0) {
        to_balance = first;
    } else if (diff < 0) {
        to_balance = second;
        diff *= -1;
    }
    if (to_balance) {
        for (int i = 0; i < diff; i++) {
            big_decimal shifted_one = big_decimal_shift_left(*to_balance, 1);
            big_decimal shifted_three = big_decimal_shift_left(*to_balance, 3);
            *to_balance = big_decimal_add_big_int(shifted_one, shifted_three);
        }
        big_decimal_set_exp(to_balance, big_decimal_get_exp(*to_balance) + diff);
    }
}