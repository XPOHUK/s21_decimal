//
// Created by gubankov on 06.08.22.
//
#include "big_decimal.h"
#include <stdio.h>
/**
 * @brief Функция сдвигает биты мантиссы влево на shifts разрядов.
 * Теоретически, возможно переполнение и тогда изменяется знак числа
 * @param in
 * @param shifts Количество разрядов на которое необходимо произвести сдвиг.
 * @return
 */
big_decimal big_decimal_shift_left(big_decimal in, int shifts) {
    // Начинаем со старшего инта. Если есть переполнение -- меняем знак
    if (big_decimal_is_set_bit(in, 191))
        in = big_decimal_set_sign(in, 1);
    while (shifts) {
        int index = 159;
        for (int i = 5; i >= 0; i--) {
            in.parts[i] = in.parts[i] << 1;
            if (i && big_decimal_is_set_bit(in, index)) {
                in = big_decimal_set_bit(in, index + 1);
            }
            index -= 32;
        }
        shifts--;
    }
    return in;
}

/**
 * @brief Функция сдвигает биты мантиссы вправо на shifts разрядов
 * @param in
 * @param shifts
 * @return
 */
big_decimal big_decimal_shift_right(big_decimal in, int shifts) {
    while (shifts) {
        int index = 32;
        for (int i = 0; i <= 5; i++) {
            in.parts[i] = in.parts[i] >> 1;
            if (i != 5 && big_decimal_is_set_bit(in, index)) {
                in = big_decimal_set_bit(in, index - 1);
            }
            index += 32;
        }
        shifts--;
    }
    return in;
}
