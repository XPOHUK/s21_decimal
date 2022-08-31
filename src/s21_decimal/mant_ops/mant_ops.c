/**
* @brief
*/
#include "mant_ops.h"

int s21_decimal_mant_is_zero(s21_decimal decimal) {
    return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0;
}

