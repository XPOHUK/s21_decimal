#include "./arithmetic.h"
#include "../helpers/helpers.h"
#include "../big_decimal/big_decimal.h"
#include "../../tests/_helpers/_debug.h"

#include <stddef.h>
#include <stdio.h>
/**
 * @brief Функция принимает на входе два числа в формате Decimal и указатель для записи результата
 * Отрицательные числа записаны в прямом коде и в отдельном бите выставлен знак.
 * @param value_1 Первое слагаемое.
 * @param value_2 Второе слагаемое.
 * @param result Указатель для записи суммы.
 * @return Код возврата.
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2) || result == NULL) {
        return -1;
    }
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    big_decimal big_decimal1 = decimal_to_big_decimal(value_1);
    big_decimal big_decimal2 = decimal_to_big_decimal(value_2);
    printf("args in add after convert to big");
    s21_print_big_decimal_bits(big_decimal1);
    s21_print_big_decimal_bits(big_decimal2);
    big_decimal big_decimal1_abs = big_decimal_set_sign(big_decimal1, 0);
    big_decimal big_decimal2_abs = big_decimal_set_sign(big_decimal2, 0);
    int value_1_sign = s21_decimal_get_sign(value_1);
    int value_2_sign = s21_decimal_get_sign(value_2);
    big_decimal res = big_decimal_add(big_decimal1, big_decimal2);
    fprintf(stdout, "res = ");
    s21_print_big_decimal_bits(res);
    fprintf(stdout, "res sign = %d\n", big_decimal_get_sign(res));
    int res_sign = big_decimal_get_sign(res);
    // Оценка результата
    // С правильными кодами ошибок ещё надо разобраться
    if (value_1_sign == value_2_sign) {  // Если знаки аргументов одинаковые
        if ((!value_1_sign && res_sign) || (value_1_sign && !res_sign)) {  // но не совпадают со знаком результата
            code = S21_ARITHMETIC_BIG;  // значит произошло переполнение мантиссы
        }
    } else if (value_1_sign){  // Если первый аргумент отрицательный
        if (big_decimal_compare(big_decimal2_abs, big_decimal1_abs)) {  // и по модулю меньше второго
            // знак результата должен быть положительный
            if (res_sign) {
                // знак результата отрицательный, неудача
            }
        } else if (big_decimal_compare(big_decimal1_abs, big_decimal2_abs)) {  // если же больше
            // знак результата должен быть отрицательный
            if (!res_sign) {
                // знак результата положительный, неудача
            }
        } else {  // в этом случае результат должен быть 0

        }
    } else {  // Если второй аргумент отрицательный
        if (big_decimal_compare(big_decimal1_abs, big_decimal2_abs)) {  // и по модулю меньше первого
            // знак результата должен быть положительный
            if (res_sign) {
                // знак результата отрицательный, неудача
            }
        } else if (big_decimal_compare(big_decimal2_abs, big_decimal1_abs)) {  // если же больше
            // знак результата должен быть отрицательный
            if (!res_sign) {
                // знак результата положительный, неудача
            }
        }
    }
    // Если код результата остался ОК, то можно попробовать округлить до decimal
    printf("\n");
    printf("code: %d\n", code);
    if (code == S21_ARITHMETIC_OK) {
    int sign = big_decimal_get_sign(res);
    if (sign) {
        int exp = big_decimal_get_exp(res);
        printf("exp = %d\n", exp);
        res = big_decimal_to_twos_complement(res);
        big_decimal_set_exp(&res, exp);
    }
        code = big_decimal_round_to_decimal(res, result);
    }
    // *result = big_decimal_to_decimal(res);
    return code;
}
