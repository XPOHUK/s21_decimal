//
// Created by gubankov on 11.08.22.
//
#include "big_decimal.h"

big_decimal big_decimal_sub(big_decimal minuend, big_decimal subtrahend) {
    big_decimal result;
    int minuend_sign = big_decimal_get_sign(minuend);
    int subtrahend_sign = big_decimal_get_sign(subtrahend);
    subtrahend = big_decimal_change_sign(subtrahend);
    result = big_decimal_add(minuend, subtrahend);
    // Заглушка
    return big_decimal_set_sign(result, minuend_sign ^ subtrahend_sign);

}
