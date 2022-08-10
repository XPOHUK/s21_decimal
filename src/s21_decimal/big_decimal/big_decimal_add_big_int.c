//
// Created by gubankov on 08.08.22.
//

#include "big_decimal.h"

/**
 * @brief Функция принимает на входе два big_decimal, но экспоненту игнорирует и ни как не обрабатывает. Поэтому
 * фактически это обработка двух больших целых чисел в прямом коде со знаком. Отсюда и название.
 * Возможное переполнение попадает в знаковый бит
 * @param first -- положительное целое
 * @param second -- положительное либо отрицательное целое в прямом коде
 * @return
 */
big_decimal big_decimal_add_big_int(big_decimal first, big_decimal second) {
    big_decimal result;
    if (big_decimal_get_sign(first)) {
        if (big_decimal_get_sign(second)) {
            first = big_decimal_change_sign(first);
            second = big_decimal_change_sign(second);
            result = big_decimal_add_big_int(first, second);
            // Ожидаемый результат -- положительный
            if (!big_decimal_get_sign(result)) {
                result = big_decimal_change_sign(result);
            } else {
                // Произошло переполнение
            }
        } else {
            result = big_decimal_add_big_int(second, first);
            // Ожидаемый результат зависит от величины second по модулю
            int bit1 = big_decimal_get_not_zero_bit(first);
            int bit2 = big_decimal_get_not_zero_bit(second);
            if (bit1 > bit2) {
                // Ожидаемый результат -- отрицательный
                if (!big_decimal_get_sign(result)) {
                    // Произошло переполнение
                }
            } else if (bit1 < bit2) {
                // Ожидаемый результат -- положительный
                if (big_decimal_get_sign(result)) {
                    // Произошло переполнение
                }
            }
        }
    } else {
        if (big_decimal_get_sign(second))
            second = big_decimal_to_twos_complement(second);
        while (!big_decimal_is_zero(second)) {
            // Получаем carry
            big_decimal carry = big_decimal_and(result, second);
            big_decimal shifted_carry = big_decimal_shift_left(carry, 1);
            result = big_decimal_xor(result, second);
            second = shifted_carry;
        }
    }
    return result;
}