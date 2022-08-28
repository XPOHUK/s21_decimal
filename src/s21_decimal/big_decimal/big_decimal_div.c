//
// Created by gubankov on 11.08.22.
// TODO(Rambtono): Все умножения на 10 переделать на использование умножения после его реализации
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
    int sign = big_decimal_get_sign(*result);

    int over = 0;
    int over_in_sum = 0;
    int break_on_exp = 0;
    int temp_exp = big_decimal_get_exp(dividend) - big_decimal_get_exp(divisor);
    // printf("remainder:\n");
    // s21_print_big_decimal_bits(remainder);
    // Сбрасываем знак делителя
    divisor = big_decimal_set_sign(divisor, 0);
    big_decimal div_res = big_decimal_get_zero();
    while (!big_decimal_is_zero(remainder)) {
        // printf("Current result: \n");
        // s21_print_big_decimal_bits(*result);
        // printf("temp_exp: %d\n", temp_exp);

        // Домножаем остаток на 10
        big_decimal shifted_one = big_decimal_shift_left(remainder, 1);
        big_decimal shifted_three = big_decimal_shift_left(remainder, 3);
        remainder = big_decimal_add_big_int(shifted_three, shifted_one);


        // Делим домноженный остаток на делитель
        big_decimal_div_big_int(remainder, divisor, &div_res, &remainder);

        // printf("div_res: \n");
        // s21_print_big_decimal_bits(div_res);
        // printf("remainder: \n");
        // s21_print_big_decimal_bits(remainder);

        if (temp_exp != 28) {
            // Домножаем основной результат на 10
            shifted_one = big_decimal_shift_left(*result, 1);
            shifted_three = big_decimal_shift_left(*result, 3);
            big_decimal temp_res = big_decimal_add_big_int(shifted_one, shifted_three);

            // printf("result_mul: \n");
            // s21_print_big_decimal_bits(temp_res);

            // Если при этом умножении основной результат не вышел за пределы s21_decimal,
            // значит результат промежуточного деления
            // можно прибавить к этому временному результату.

            if (big_decimal_is_zero(temp_res) || big_decimal_get_not_zero_bit(temp_res) < 96) {
                temp_res = big_decimal_add_big_int(temp_res, div_res);
                // При этом сложении могло произойти переполнение decimal
                if (!big_decimal_is_zero(temp_res) && big_decimal_get_not_zero_bit(temp_res) > 95) {
                    over_in_sum = 1;
                    break;
                }
                // Если переполнения не произошло, то сохраняем основной результат и увеличиваем экспоненту
                *result = temp_res;
                temp_exp++;
            } else {
                // Произошло переполнение при умножении основного результата.
                // Отбрасываем переполненный результат, т.е. не сохраняем в result.
                // И выходим из цикла с флагом переполнения.
                over = 1;
                break;
            }
        } else {
            // При экспоненте 28 уже нет смысла домножать результат. Выходим из цикла.
            // printf("break on exp 28\n");
            break_on_exp = 1;
            break;
        }
    }
    // printf("After cycle:\n");
    // printf("result:\n");
    // s21_print_big_decimal_bits(*result);
    // printf("exp: %d, over: %d, over_in_sum: %d\n", temp_exp, over, over_in_sum);
    // printf("div_res:\n");
    // s21_print_big_decimal_bits(div_res);
    // printf("remainder:\n");
    // s21_print_big_decimal_bits(remainder);
    // Далее идёт обработка результатов. Отталкиваемся от состояния экспоненты.
    if (big_decimal_is_zero(*result)
            && big_decimal_is_zero(div_res)
            && temp_exp == 0 && over_in_sum) {
        code = S21_ARITHMETIC_SMALL;
    } else if ((temp_exp < 0 && over)
            || (temp_exp == 28 && big_decimal_is_zero(*result)
                && big_decimal_is_zero(div_res))) {
        // Если экспонента отрицательная, а разрядная сетка при этом заполнена,
        // то имеем неисправимое переполнение
        // Либо если экспонента 28, результат и результат деления равны 0, то имеем очень малое число.
        // printf("in first if\n");
        if (break_on_exp) {
            code = S21_ARITHMETIC_SMALL;
        } else if (sign && over) {
            code = S21_ARITHMETIC_SMALL;
        } else if (!sign && over) {
            code = S21_ARITHMETIC_BIG;
        }
    // } else if (temp_exp == 28 && !over && !over_in_sum && big_decimal_is_zero(remainder)) {
    //     printf("bug\n");
    } else if ((over && temp_exp >= 0) || (over_in_sum) || (temp_exp == 28 && break_on_exp)) {
        // Если экспонента больше либо равна 0 и есть флаг переполнения, то округляем
        // printf("in second if\n");
        if (div_res.parts[0] > 5
                || (div_res.parts[0] == 5
                    && (!big_decimal_is_zero(remainder)
                        || big_decimal_is_set_bit(*result, 0)))) {
            big_decimal temp = big_decimal_incr(*result);
            // При инкременте могло произойти переполнение
            if (big_decimal_get_not_zero_bit(temp) > 95) {
                big_decimal temp_rem = big_decimal_get_zero();
                big_decimal_div_big_int(*result,
                        decimal_to_big_decimal(s21_decimal_get_ten()),
                        result,
                        &temp_rem);
                *result = big_decimal_incr(*result);
                temp_exp--;
            }
            *result = temp;
        } else if (big_decimal_is_zero(*result) && temp_exp == 28) {
            code = S21_ARITHMETIC_SMALL;
        }
    }
    // else if (over && temp_exp == 0) {
    //     if (sign)
    //         code = S21_ARITHMETIC_SMALL;
    //     else
    //         code = S21_ARITHMETIC_BIG;
    // }
    if (temp_exp < 0 && code == S21_ARITHMETIC_OK) {
        // printf("in last if\n");
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
            } else {
                if (sign)
                    code = S21_ARITHMETIC_SMALL;
                else
                    code = S21_ARITHMETIC_BIG;
            }
    }
    // printf("result after ifs:\n");
    // s21_print_big_decimal_bits(*result);
    big_decimal_set_exp(result, temp_exp);
    *result = big_decimal_set_sign(*result, sign);
    if (code == S21_ARITHMETIC_OK)
        *result = remove_trail_zero(*result);
    // printf("result after trail:\n");
    // s21_print_big_decimal_bits(*result);
    // printf("code after trail: %d\n", code);
    return code;
}
