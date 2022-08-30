#include "./other.h"
#include "./../helpers/helpers.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    if (s21_is_correct_decimal(value)) {
        *result = s21_decimal_get_zero();
    }

    return 1;
}
