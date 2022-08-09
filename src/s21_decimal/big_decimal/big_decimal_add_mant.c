//
// Created by gubankov on 08.08.22.
//

#include "big_decimal.h"

/**
 * @brief Перед вызовом этой функции желательно занулить экспоненты у слагаемых (если одно из них отрицательное, то
 * экспоненту надо занулять до получения дополнительного кода)
 * @param first
 * @param second
 * @return
 */
big_decimal big_decimal_add_mant(big_decimal first, big_decimal second) {
    big_decimal result = first;
    int expected_sign = big_decimal_get_sign(first) ^ big_decimal_get_sign(second);
    while (!big_decimal_is_zero(second)) {
        // Получаем carry
        big_decimal carry = big_decimal_and(result, second);
        int carry_bit = big_decimal_is_set_bit(carry,95);
        // Если есть carry-bit под индексом 95, то его надо перенести в позицию 0 старшего decimal. Можно записать его
        // туда после сдвига (на то место попадает carry знаков low-части, а там по любому 0)
        big_decimal shifted_carry = big_decimal_shift_left(carry, 1);
        if (carry_bit) {
            big_decimal_set_bit(shifted_carry, 96);
        }
        result = big_decimal_xor(result, second);
        second = shifted_carry;
    }
    // TODO Не забыть решить вопрос со знаком.
    // Возвращаемый результат может иметь знаковый бит, а соответственно это будет дополнительный код
    return result;
}