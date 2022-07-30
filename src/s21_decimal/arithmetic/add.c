#include "./arithmetic.h"
#include "../helpers/helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int raise_exp_over = 0;
    while (s21_decimal_get_power(value_1) != s21_decimal_get_power(value_2)) {
        if (s21_decimal_get_power(value_1) > s21_decimal_get_power(value_2)) {
            raise_exp_over = raise_exp(&value_2);
        } else {
            raise_exp_over = raise_exp(&value_1);
        }
        // Тут наверное надо проверять переполнение.
        // Что делать, если переполнение возникло раньше завершения выравнивания?
        // Судя по всему, переполнение надо было записывать в "занулённый" bits[3], т.к. в него оно полностью влезет.
    }
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    result->bits[0] = value_1.bits[0] + value_2.bits[0];
    return code;
}
