//
// Created by gubankov on 11.08.22.
//
#include "big_decimal.h"
/**
 * @brief Деление
 * @param dividend
 * @param divisor
 * @return
 */
big_decimal big_decimal_div(big_decimal dividend, big_decimal divisor) {
    // Сначала получаем целую часть (экспонента позже может её "подвинуть")
    // Знак результата уже учтён при этом вычислении, поэтому дальнейшие надо выполнять без знака
    big_decimal result = big_decimal_get_zero();
    big_decimal remainder = big_decimal_get_zero();
    big_decimal_div_big_int(dividend, divisor, &result, &remainder);
    int temp_exp = big_decimal_get_exp(dividend) - big_decimal_get_exp(divisor);
    if (!big_decimal_is_zero(remainder)) {
        // Сбрасываем знак делителя
        divisor = big_decimal_set_sign(divisor, 0);
        while (!big_decimal_is_zero(remainder)) {
            // Домножаем остаток на 10 и увеличиваем экспоненту
            big_decimal shifted_one = big_decimal_shift_left(remainder, 1);
            big_decimal shifted_three = big_decimal_shift_left(remainder, 3);
            remainder = big_decimal_add_big_int(shifted_three, shifted_one);
            temp_exp++;
            big_decimal temp_res = big_decimal_get_zero();
            // Делим домноженный остаток на делитель
            big_decimal_div_big_int(remainder, divisor, &temp_res, &remainder);
            // Домножаем основной результат на 10
            shifted_one = big_decimal_shift_left(result, 1);
            shifted_three = big_decimal_shift_left(result, 3);
            result = big_decimal_add_big_int(shifted_one, shifted_three);
            // Прибавляем к основному результату результат промежуточного деления
            result = big_decimal_add_big_int(result, temp_res);
            // Если появилось переполнение, значит надо прекращать вычисление следующих знаков
    }
}
