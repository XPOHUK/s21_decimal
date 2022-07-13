#include "../../s21_decimal.h"

int s21_is_equal_full_zero(s21_decimal decimal) {
    return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 && decimal.bits[3] == 0;
}
