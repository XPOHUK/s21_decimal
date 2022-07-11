#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2) {
    return decimal1.bits[0] == decimal2.bits[0] &&
           decimal1.bits[1] == decimal2.bits[1] &&
           decimal1.bits[2] == decimal2.bits[2] &&
           decimal1.bits[3] == decimal2.bits[3];
}
