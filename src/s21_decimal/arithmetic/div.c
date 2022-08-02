#include "./arithmetic.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"
#include <stdio.h>

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    int exp_diff = s21_decimal_get_power(value_1) - s21_decimal_get_power(value_2);
    s21_decimal remainder = s21_decimal_get_zero();
    s21_decimal_div_mant(value_1, value_2, result, &remainder);
    s21_decimal temp_res = s21_decimal_get_zero();
    s21_decimal raised_res;
    s21_decimal overflow = s21_decimal_get_zero();
    while (!s21_decimal_mant_is_zero(remainder)) {
        // Умножаем остаток на 10. Пока так, потом переделать на умножение мантисс
        remainder = raise_exp(remainder, NULL);  // TODO Rambton Ovtime
        // Делим увеличенный остаток на делитель
        s21_decimal_div_mant(remainder,value_2, &temp_res, &remainder);
        // Умножаем основной результат на 10 чтобы дописать к нему цифру. Результат умноженияя сохраняем во временный
        raised_res = raise_exp(*result, &overflow);
        if (s21_decimal_mant_is_zero(overflow)) {
            // Переполнения результата нет, дописываем цифру
            *result = s21_decimal_add_mant(raised_res, temp_res);
        } else {
            // Если появилось переполнение, значит у результата слишком длинная дробная часть. При возникновении такого
            // переполнения надо делать округление и прекращать вычисления. Если при переполнении результат деления
            // увеличенного остатка не 5, то можно смело делать округление на 1 знак. Если же цифра 5, то надо вычислить ещё одну
            // значащую цифру. Если она будет 0, то надо продолжить вычисления до первой ненулевой цифры. После чего произ-
            // вести округление.
            if (temp_res.bits[0] != 5) {
                if (temp_res.bits[0] > 5) {
                    *result = s21_decimal_add_mant(*result, s21_decimal_get_one());
                }
                break;
            } else {
                // Продолжать деление до тех пор, пока не получится округлить. Т.е. должно быть не 0 и не 5
                // Интересно, а если будет 5 в периоде?... ппц
                while (temp_res.bits[0] == 5 || temp_res.bits[0] == 0) {
                    remainder = raise_exp(remainder, NULL);
                    s21_decimal_div_mant(remainder,value_2, &temp_res, &remainder);
                }
            }
        }
    }
    return code;
}
