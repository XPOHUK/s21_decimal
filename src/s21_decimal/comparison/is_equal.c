#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2) {
    int decimal1_sign = s21_decimal_get_sign(decimal1);
    int decimal2_sign = s21_decimal_get_sign(decimal2);
    int decimal1_power = s21_decimal_get_power(decimal1);
    int decimal2_power = s21_decimal_get_power(decimal2);

    int sign_is_equal = decimal1_sign == decimal2_sign ? 1 : 0;
    int power_is_equal = decimal1_power == decimal2_power ? 1 : 0;
    int lbits_are_equal = decimal1.bits[0] == decimal2.bits[0] ? 1 : 0;
    int mbits_are_equal = decimal1.bits[1] == decimal2.bits[1] ? 1 : 0;
    int hbits_are_equal = decimal1.bits[2] == decimal2.bits[2] ? 1 : 0;

    return sign_is_equal && power_is_equal && lbits_are_equal && mbits_are_equal && hbits_are_equal ? 1 : 0;
}
