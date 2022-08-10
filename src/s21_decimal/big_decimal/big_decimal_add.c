//
// Created by gubankov on 10.08.22.
//
#include "big_decimal.h"

/**
 * @brief Функция производит сложение двух big_decimal
 * @param first положительное в прямом коде
 * @param second положительное или отрицательное в прямом коде
 * @return
 */
big_decimal big_decimal_add(big_decimal first, big_decimal second) {
    int expected_sign = 0;
    big_decimal_balance_exp(&first, &second);
    // Для начала надо определить ожидаемый знак суммы
    // Если второе число отрицательное и по модулю больше первого, то знак ожидаем отрицательный
    if (big_decimal_get_sign(second) && big_decimal_get_not_zero_bit(second) > big_decimal_get_not_zero_bit(first)) {
        expected_sign = 1;
    }
    big_decimal sum = big_decimal_add_big_int(first, second);
    // Теперь надо сравнить ожидаемый и полученный знаки суммы. Если они отличаются, значит произошло переполнение
    if (big_decimal_get_sign(sum) != expected_sign) {

    }
    return sum;
}