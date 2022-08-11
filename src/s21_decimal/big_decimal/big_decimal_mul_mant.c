//
// Created by gubankov on 08.08.22.
//

#include "big_decimal.h"

/**
 * @brief Целочисленное умножение мантисс (соответственно без учёта экспоненты)
 * @param first
 * @param second
 * @return
 */
big_decimal big_decimal_mul_mant(big_decimal first, big_decimal second) {
    return big_decimal_add(first, second);

}