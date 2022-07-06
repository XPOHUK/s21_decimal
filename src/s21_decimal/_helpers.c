
#include <stdint.h>

#include "../s21_decimal.h"

int s21_is_correct_decimal(s21_decimal decimal) {
    if (s21_decimal_get_empty1(decimal) != 0 || s21_decimal_get_empty2(decimal) != 0) {
        return 0;
    }

    int power = s21_decimal_get_power(decimal);
    if (power < 0 || power > 28) {
        return 0;
    }

    return 1;
}

/**
 * @brief возвращает знак decimal
 * 
 * @param decimal проверяемый decimal
 * @return int 1 - отрицательный decimal, 0 - положительный decimal
 */
int s21_decimal_get_sign(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.sign;
}

int s21_decimal_get_power(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.power;
}

int s21_decimal_get_empty1(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.empty1;
}

int s21_decimal_get_empty2(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.empty2;
}
