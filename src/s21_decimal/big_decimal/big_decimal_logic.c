//
// Created by gubankov on 06.08.22.
//

#include "big_decimal.h"
#include "../binary/binary.h"

int big_decimal_and(big_decimal first, big_decimal second, big_decimal* result) {
    result->low = s21_decimal_binary_and(first.low, second.low);
    result->over = s21_decimal_binary_and(first.over, second.over);
}

int big_decimal_xor(big_decimal first, big_decimal second, big_decimal* result) {
    result->low = s21_decimal_binary_xor(first.low, second.low);
    result->over = s21_decimal_binary_xor(first.over, second.over);
}

int big_decimal_not(big_decimal first, big_decimal second, big_decimal* result) {
    result->low = s21_decimal_binary_not(first.low, second.low);
}