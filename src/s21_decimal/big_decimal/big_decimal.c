#include "big_decimal.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"

/**
 * @brief Функция возвращает big_decimal с одним единственным битом выставленным по индексу. Такое число удобно для
 * проверки, установки или переворачивания одного бита другого числа.
 * @param index Индекс бита. Биты четвёртого инта в decimal не считаются. Т.е. в младшем decimal индексы 0-95,
 * а в старшем индексы 96-191
 * @return
 */
big_decimal big_decimal_get_bit(int index) {
    return big_decimal_set_bit(big_decimal_get_zero(), index);
}

/**
 * @brief Функция возвращает 1 если бит установлен, иначе возвращает 0
 * @param in
 * @param index Индекс бита. Биты четвёртого инта в decimal не считаются. Т.е. в младшем decimal индексы 0-95,
 * а в старшем индексы 96-191
 * @return
 */
int big_decimal_is_set_bit(big_decimal in, int index) {
    big_decimal bit = big_decimal_get_bit(index);
    return (big_decimal_shift_right(big_decimal_and(in, bit), index)).low.bits[0];
}
/**
 * @brief Функция устанваливает в указанный бит 1, если там был 0, либо ничего не делает.
 * (x OR y) = NOT(NOT(x) AND NOT(y))
 * @param in
 * @param index Индекс бита. Биты четвёртого инта в decimal не считаются. Т.е. в младшем decimal индексы 0-95,
 * а в старшем индексы 96-191
 * @return
 */
big_decimal big_decimal_set_bit(big_decimal in, int index) {
    big_decimal bit = big_decimal_get_bit(index);
    return big_decimal_not(big_decimal_and(big_decimal_not(in), big_decimal_not(bit)));
}
/**
 * @brief Функция меняет значение указанного бита на противоположное
 * @param in
 * @param index Индекс бита. Биты четвёртого инта в decimal не считаются. Т.е. в младшем decimal индексы 0-95,
 * а в старшем индексы 96-191
 * @return
 */
big_decimal big_decimal_flip_bit(big_decimal in, int index) {
    big_decimal bit = big_decimal_get_bit(index);
    return big_decimal_xor(in, bit);
}

/**
 * @brief Функция возвращает 1 если знак установлен. Знак хранится в младшем decimal
 * @param in
 * @return
 */
int big_decimal_get_sign(big_decimal in) {
    return s21_decimal_get_sign(in.low);
}

/**
 * @brief Функция устанавливает знак
 * @param in
 * @param sign
 * @return
 */
big_decimal big_decimal_set_sign(big_decimal in, int sign) {
    s21_decimal_set_sign(&(in.low), sign);
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
    result.low = s21_decimal_get_zero();
    result.over = s21_decimal_get_zero();
}

/**
 * @brief Функция возвращает дополнительный код полученного big_decimal
 * @param direct_code
 * @return
 */
big_decimal big_decimal_to_twos_complement(big_decimal direct_code) {
    return big_decimal_incr(big_decimal_not(direct_code));
}

int big_decimal_is_zero(big_decimal in) {
    return s21_decimal_mant_is_zero(in.low) && s21_decimal_mant_is_zero(in.over);
}

int big_decimal_get_exp(big_decimal in) {
    return s21_decimal_get_power(in.low);
}

void big_decimal_set_exp(big_decimal in, int exp) {
    s21_decimal_set_power(&(in.low), exp)
}
