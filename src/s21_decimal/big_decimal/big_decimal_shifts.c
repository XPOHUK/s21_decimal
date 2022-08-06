//
// Created by gubankov on 06.08.22.
//
#include "big_decimal.h"
/**
 * @brief Функция сдвигает биты мантиссы младшего и старшего decimal влево на shifts разрядов.
 * Теоретически, возможно переполнение и старшего decimal, но я пока такую ситуацию не учитываю. Пока что при
 * переполнении будет изменяться знак числа
 * @param in
 * @param shifts Количество разрядов на которое необходимо произвести сдвиг.
 * @return
 */
big_decimal big_decimal_shift_left(big_decimal in, int shifts) {
    // Начинаем со старшего инта старшего decimal. Если есть переполнение -- меняем знак
    if (big_decimal_is_set_bit(in, 191))
        in = big_decimal_change_sign(in);
    while (shifts) {
        int index = 159;
        for (int i = 2; i >= 0; i--) {
            in.over[i] = ((unsigned int)in.over[i]) << 1;
            if (big_decimal_is_set_bit(in, index)) {
                in = big_decimal_set_bit(index + 1);
            }
            index -= 32;
        }
        for (int i = 2; i >= 0; i--) {
            in.low[i] = ((unsigned int)in.low[i]) << 1;
            if (i != 0 && big_decimal_is_set_bit(in, index)) {
                in = big_decimal_set_bit(index + 1);
            }
            index -= 32;
        }
        shifts--;
    }
}

/**
 * @brief Функция сдвигает биты мантиссы младшего и старшего decimal вправо на shifts разрядов
 * @param in
 * @param shifts
 * @return
 */
big_decimal big_decimal_shift_right(big_decimal in, int shifts) {
    while (shifts) {
        int index = 32;
        for (int i = 0; i <= 2; i++) {
            in.low[i] = ((unsigned int)in.low[i]) >> 1;
            if (big_decimal_is_set_bit(in, index)) {
                in = big_decimal_set_bit(index - 1);
            }
            index += 32;
        }
        for (int i = 0; i <= 2; i++) {
            in.over[i] = ((unsigned int)in.over[i]) >> 1;
            if (i != 2 && big_decimal_is_set_bit(in, index)) {
                in = big_decimal_set_bit(index - 1);
            }
            index += 32;
        }
        shifts--;
    }
}