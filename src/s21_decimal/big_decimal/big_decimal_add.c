//
// Created by gubankov on 10.08.22.
//
#include "big_decimal.h"

/**
 * @brief Функция производит сложение двух big_decimal
 * @param first положительное или отрицательное в прямом коде
 * @param second положительное или отрицательное в прямом коде
 * @return положительное или отрицательное в доп.коде.
 */
big_decimal big_decimal_add(big_decimal first, big_decimal second) {
    big_decimal_balance_exp(&first, &second);
    return big_decimal_add_big_int(first, second);
}

