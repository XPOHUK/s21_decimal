//
// Created by gubankov on 27.07.22.
//

#ifndef DECIMAL_MANT_OPS_H
#define DECIMAL_MANT_OPS_H

#include "../types.h"
#include "../binary/binary.h"



s21_decimal s21_decimal_add_mant(s21_decimal a, s21_decimal b);
int s21_decimal_div_mant(s21_decimal dividend, s21_decimal divisor, s21_decimal* res, s21_decimal* remainder);
s21_decimal s21_decimal_shift_mant_left(s21_decimal decimal, int index, s21_decimal* over);
s21_decimal s21_decimal_shift_mant_right(s21_decimal decimal, int index);

int s21_decimal_mant_is_zero(s21_decimal decimal);
int s21_decimal_mant_compare(s21_decimal x, s21_decimal y);

#endif //DECIMAL_MANT_OPS_H
