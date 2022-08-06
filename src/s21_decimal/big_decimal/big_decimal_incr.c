//
// Created by gubankov on 06.08.22.
//
#include "big_decimal.h"

big_decimal big_decimal_incr(big_decimal in) {
    for (register int i = 0; i < 192; ++i) {
        int bit = big_decimal_is_set_bit(in, i);
        in = big_decimal_flip_bit(in, i);
        if (!bit)
            break;
    }
    return in;
}