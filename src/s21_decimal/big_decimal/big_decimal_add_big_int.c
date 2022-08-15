//
// Created by gubankov on 08.08.22.
//

#include "big_decimal.h"
#include "../../tests/_helpers/_debug.h"
#include <stdio.h>

/**
 * @brief Функция принимает на входе два big_decimal, но экспоненту игнорирует и ни как не обрабатывает. Поэтому
 * фактически это обработка двух больших целых чисел в прямом коде со знаком. Отсюда и название.
 * Возможное переполнение попадает в знаковый бит. Оценивать результат уже в вызывающей функции.
 * @param first -- первое положительное или отрицательное целое в прямом коде
 * @param second -- второе положительное или отрицательное целое в прямом коде
 * @return целое в прямом или доп.коде
 */
big_decimal big_decimal_add_big_int(big_decimal first, big_decimal second) {
    if (big_decimal_get_sign(first)) {
        first = big_decimal_to_twos_complement(first);
    }
    big_decimal result = first;
    if (big_decimal_get_sign(second))
        second = big_decimal_to_twos_complement(second);
    fprintf(stdout, "before cycle\n");
    while (!big_decimal_is_zero(second)) {
        // Получаем carry
        big_decimal carry = big_decimal_and(result, second);
        fprintf(stdout, "carry = %d\n", carry.parts[0]);
        big_decimal shifted_carry = big_decimal_shift_left(carry, 1);
        fprintf(stdout, "shifted carry = %d\n", shifted_carry.parts[0]);
        result = big_decimal_xor(result, second);
        fprintf(stdout, "res after xor = %d\n", result.parts[0]);
        second = shifted_carry;
    }
    return result;
}