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
        *to_balance = big_decimal_shift_left(*to_balance, diff);
        big_decimal_set_exp(to_balance, big_decimal_get_exp(*to_balance) + diff);
    }
}