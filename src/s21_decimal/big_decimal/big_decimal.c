#include "big_decimal.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"

/**
 * @brief Функция возвращает big_decimal с одним единственным битом мантиссы выставленным по индексу. Такое число
 * удобно для проверки, установки или переворачивания одного бита другого числа.
 * @param index Индекс бита.
 * @return
 */
big_decimal big_decimal_get_bit(int index) {
    return big_decimal_shift_left(big_decimal_incr(big_decimal_get_zero()), index);
}

/**
 * @brief Функция возвращает 1 если бит мантиссы установлен, иначе возвращает 0
 * @param in
 * @param index Индекс бита.
 * @return
 */
unsigned int big_decimal_is_set_bit(big_decimal in, int index) {
    big_decimal bit = big_decimal_get_bit(index);
    return (big_decimal_shift_right(big_decimal_and(in, bit), index)).parts[0];
}
/**
 * @brief Функция устанваливает в указанный бит мантиссы 1, если там был 0, либо ничего не делает.
 * (x OR y) = NOT(NOT(x) AND NOT(y))
 * @param in
 * @param index Индекс бита.
 * @return
 */
big_decimal big_decimal_set_bit(big_decimal in, int index) {
    big_decimal bit = big_decimal_get_bit(index);
    return big_decimal_not(big_decimal_and(big_decimal_not(in), big_decimal_not(bit)));
}
/**
 * @brief Функция меняет значение указанного бита мантиссы на противоположное
 * @param in
 * @param index Индекс бита
 * @return
 */
big_decimal big_decimal_flip_bit(big_decimal in, int index) {
    big_decimal bit = big_decimal_get_bit(index);
    return big_decimal_xor(in, bit);
}

/**
 * @brief Функция возвращает 1 если знак (192 индекс) установлен. Знак хранится в младшем decimal
 * @param in
 * @return
 */
unsigned int big_decimal_get_sign(big_decimal in) {
    return in.parts[6] & 1U;
}

/**
 * @brief Функция устанавливает знак
 * @param in
 * @param sign
 * @return
 */
big_decimal big_decimal_set_sign(big_decimal in, int sign) {
    if (big_decimal_get_sign(in) && sign == 0)
        in.parts[6] = in.parts[6] - 1;
    else if (!big_decimal_get_sign(in) && sign)
        in.parts[6] = in.parts[6] + 1;
    return in;
}

big_decimal big_decimal_change_sign(big_decimal in) {
    if (big_decimal_get_sign(in))
        big_decimal_set_sign(in, 0);
    else
        big_decimal_set_sign(in, 1);
    return in;
}

/**
 * @brief Функция для получения девственно-чистого big_decimal
 * @return
 */
big_decimal big_decimal_get_zero(void) {
    big_decimal result;
    for (int i = 0; i < 7; ++i) {
        result.parts[i] = 0U;
    }
    return result;
}

/**
 * @brief Функция возвращает дополнительный код мантиссы полученного big_decimal
 * Экспонента обнуляется
 * @param direct_code
 * @return
 */
big_decimal big_decimal_to_twos_complement(big_decimal direct_code) {
    big_decimal result = big_decimal_incr(big_decimal_not(direct_code));
    // Зануляем экспоненту просто сохраняя знак
    result.parts[6] = big_decimal_get_sign(result);
    return result;
}

big_decimal big_decimal_incr(big_decimal in) {
    for (register int i = 0; i < 192; ++i) {
        int bit = big_decimal_is_set_bit(in, i);
        in = big_decimal_flip_bit(in, i);
        if (!bit)
            break;
    }
    // TODO Не учтено возможное переполнение
    return in;
}

unsigned int big_decimal_is_zero(big_decimal in) {
    unsigned int result = 0U;
    for (int i = 0; i < 6; ++i) {
        result = result ^ in.parts[i];
    }
    if (result)
        result = 1U;
    return result;
}

int big_decimal_get_exp(big_decimal in) {
    return (in.parts[6] & (256U << 16)) >> 16;
}

void big_decimal_set_exp(big_decimal* in, int exp) {
    unsigned int sign = big_decimal_get_sign(*in);
    (*in).parts[6] = ((unsigned int)exp) << 16;
    *in = big_decimal_set_sign(*in, sign);
}
