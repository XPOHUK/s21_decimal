#include <stdio.h>
#include "./other.h"
#include "./../_debug/_debug.h"
#include "./../helpers/helpers.h"
#include "./../binary/binary.h"

/**
 * 
 * @param value 
 * @param result 
 * @return int 
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;
    s21_clear_decimal(result);

    s21_decimal tmp = value;
    tmp.bits[3] = 0;

    int power = s21_decimal_get_power(value);
    while (power > 0) {
        tmp = s21_decimal_binary_division(tmp, s21_decimal_get_ten(), NULL);
        --power;
    }

    *result = tmp;
    if (s21_decimal_get_sign(value) == 1) {
        s21_decimal_set_sign(result, 1);
    }

    return code;
}
