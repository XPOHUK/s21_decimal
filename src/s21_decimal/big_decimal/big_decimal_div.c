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
    int rounded = 0;
    int sign = big_decimal_get_sign(*result);
    int temp_exp = big_decimal_get_exp(dividend) - big_decimal_get_exp(divisor);
    printf("remainder:\n");
    s21_print_big_decimal_bits(remainder);
    if (!big_decimal_is_zero(remainder)) {
        // Сбрасываем знак делителя

        divisor = big_decimal_set_sign(divisor, 0);
        while (!big_decimal_is_zero(remainder)) {

            printf("Current result: \n");
            s21_print_big_decimal_bits(*result);
            printf("temp_exp: %d\n", temp_exp);
            
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
                printf("result_mul: \n");
                s21_print_big_decimal_bits(result_mul);
            
            // Если при этом умножении основной результат вышел за пределы s21_decimal, значит результат промежуточного деления
            // это уже округляемая цифра
            printf("result get not zero bit: %d, %u\n", big_decimal_get_not_zero_bit(result_mul), big_decimal_get_not_zero_bit(result_mul));
            
            if ((!big_decimal_is_zero(result_mul) && big_decimal_get_not_zero_bit(result_mul) > 95 ) || temp_exp + 1 > 28) {
                printf("in first if\n");
                printf("temp_res: \n");
                    rounded = 1;
                s21_print_big_decimal_bits(temp_res);

                if (big_decimal_get_not_zero_bit(result_mul) > 95 && temp_exp <= 0 && big_decimal_get_not_zero_bit(*result) > 95) {
                    if (sign) {
                        code = S21_ARITHMETIC_SMALL;
                    } else {
                        printf("tuta\n");
                        code = S21_ARITHMETIC_BIG;
                    }
                } else if (temp_res.parts[0] > 5 || (temp_res.parts[0] == 5 && (!big_decimal_is_zero(remainder) || big_decimal_is_set_bit(*result, 0)))) {
                    *result = big_decimal_incr(*result);
                    printf("Popal pod okrug\n");
                    // Если при инкременте произошло переполнение и при этом есть экспонента, то число можно округлить ещё раз. При переполнении во время инкремента на конце десятичного числа получилось 6.
                    // Значит можно просто разделить результат на 10 и увеличить на 1
                    if (big_decimal_get_not_zero_bit(*result) > 95) {
                        if ( temp_exp > 0) {
                            big_decimal_div_big_int(*result, decimal_to_big_decimal(s21_decimal_get_ten()), result, NULL);
                            *result = big_decimal_incr(*result);
                            temp_exp--;
                        } else {
                            if(sign)
                                code = S21_ARITHMETIC_SMALL;
                            else
                                code = S21_ARITHMETIC_BIG;
                        }
                    }
                    s21_print_big_decimal_bits(temp_res);
                }

                break;
            } else {
                // В противном случае прибавляем к домноженному результату промежуточный и сохраняем в основной.
                    *result = big_decimal_add_big_int(result_mul, temp_res);
                printf("blia\n");
                // И увеличиваем экспоненту
                s21_print_big_decimal_bits(temp_res);
                temp_exp++;
            }

        }
        if (temp_exp < 0 && !rounded && code == S21_ARITHMETIC_OK) {
            // Пробуем поднять экспоненту до 0
            big_decimal raized_res = *result;
            while (temp_exp < 0 && big_decimal_get_not_zero_bit(raized_res) < 96) {
                *result = raized_res;
                big_decimal shifted_one = big_decimal_shift_left(raized_res, 1);
                big_decimal shifted_three = big_decimal_shift_left(raized_res, 3);
                raized_res = big_decimal_add_big_int(shifted_one, shifted_three);
                temp_exp++;
            }
            if (big_decimal_get_not_zero_bit(raized_res) < 96) {
                *result = raized_res;
            }

        }
            // Если результат 0 с экспонентой 28, значит получили очень маленькое число
        if (big_decimal_is_zero(*result) && temp_exp == 28) {
            code = S21_ARITHMETIC_SMALL;
        } else if (temp_exp < 0) {
            if (sign) {
                code = S21_ARITHMETIC_SMALL;
            } else {
                code = S21_ARITHMETIC_BIG;
            }
            printf("Или тут?");
        } else {
            big_decimal_set_exp(result, temp_exp);
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
                if (sign) {
                    code = S21_ARITHMETIC_SMALL;
                } else {
                    code = S21_ARITHMETIC_BIG;
                }
                printf("Тут шоль?");
                break;
            }
            temp_exp++;
            *result = temp_res;
            // big_decimal_set_exp(result, temp_exp);
        }
    }
    big_decimal_set_exp(result, temp_exp);
    *result = big_decimal_set_sign(*result, sign);
    if (big_decimal_get_not_zero_bit(*result) > 95) {
        printf("tuta blia\n");
        printf("exp: %d\n", temp_exp);
        if (sign)
            code = S21_ARITHMETIC_SMALL;
        // else
            // code = S21_ARITHMETIC_BIG;
    } else {
        *result = remove_trail_zero(*result);
    }
    return code;
}
