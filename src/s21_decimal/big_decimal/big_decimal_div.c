//
// Created by gubankov on 11.08.22.
// TODO Rambtono: Все умножения на 10 переделать на использование умножения после его реализации
#include "../arithmetic/arithmetic.h"
#include "big_decimal.h"
#include <stdio.h>
#include "../../tests/_helpers/_debug.h"
/**
 * @brief Деление
 * @param dividend
 * @param divisor
 * @return
 */
int big_decimal_div(big_decimal dividend, big_decimal divisor, big_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    // Сначала получаем целую часть (экспонента позже может её "подвинуть")
    // Знак результата уже учтён при этом вычислении, поэтому дальнейшие надо выполнять без знака
    *result = big_decimal_get_zero();
    big_decimal remainder = big_decimal_get_zero();
    big_decimal_div_big_int(dividend, divisor, result, &remainder);
    int temp_exp = big_decimal_get_exp(dividend) - big_decimal_get_exp(divisor);
    if (!big_decimal_is_zero(remainder)) {
        // Сбрасываем знак делителя
        divisor = big_decimal_set_sign(divisor, 0);
        while (!big_decimal_is_zero(remainder)) {
            // Домножаем остаток на 10
            big_decimal shifted_one = big_decimal_shift_left(remainder, 1);
            big_decimal shifted_three = big_decimal_shift_left(remainder, 3);
            remainder = big_decimal_add_big_int(shifted_three, shifted_one);
            big_decimal temp_res = big_decimal_get_zero();
            // Делим домноженный остаток на делитель
            big_decimal_div_big_int(remainder, divisor, &temp_res, &remainder);
            // Домножаем основной результат на 10
            shifted_one = big_decimal_shift_left(*result, 1);
            shifted_three = big_decimal_shift_left(*result, 3);
            big_decimal result_mul = big_decimal_add_big_int(shifted_one, shifted_three);
            // Если при этом умножении основной результат вышел за пределы s21_decimal, значит результат промежуточного деления
            // это уже округляемая цифра
            if (big_decimal_get_not_zero_bit(result_mul) > 95 || temp_exp + 1 > 28) {
                if (temp_res.parts[0] > 5 || (temp_res.parts[0] == 5 && (!big_decimal_is_zero(remainder) || big_decimal_is_set_bit(*result, 0)))) {
                    *result = big_decimal_incr(*result);
                    printf("Popal pod okrug\n");
                    s21_print_big_decimal_bits(temp_res);
                    break;
                }
            } else {
                // В противном случае прибавляем к домноженному результату промежуточный и сохраняем в основной.
                *result = big_decimal_add_big_int(result_mul, temp_res);
                // И увеличиваем экспоненту
                temp_exp++;
            }
            // Если результат 0 с экспонентой 28, значит получили очень маленькое число
            if (big_decimal_is_zero(*result) && temp_exp == 28) {
                code = S21_ARITHMETIC_SMALL;
            } else if (temp_exp < 0) {
                code = S21_ARITHMETIC_BIG;
            } else {
                big_decimal_set_exp(result, temp_exp);
            }
        }
    } else {
        // Если остаток от первоначального деления 0 и если предварительная экспонента отрицательная, то
        // результат надо домножить на 10 в степени модуля предварительной экспоненты, а экспоненту поставить 0. 
        // В противном случае просто сохраняем экспоненту.
        // В результате умножения может случиться переполнение, что говорит об очень большом числе. 
        while (temp_exp < 0) {
            big_decimal shifted_one = big_decimal_shift_left(*result, 1);
            big_decimal shifted_three = big_decimal_shift_left(*result, 3);
            big_decimal temp_res = big_decimal_add_big_int(shifted_one, shifted_three);
            if (big_decimal_get_not_zero_bit(temp_res) > 95) {
                code = S21_ARITHMETIC_BIG;
                break;
            }
            temp_exp++;
            *result = temp_res;
            big_decimal_set_exp(result, temp_exp);
        }
    }
    return code;
}
