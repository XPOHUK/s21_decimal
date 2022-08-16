#include "big_decimal.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"
#include <stdio.h>
#include "../../tests/_helpers/_debug.h"

big_decimal decimal_to_big_decimal(s21_decimal in) {
    big_decimal result = big_decimal_get_zero();
    result.parts[0] = (unsigned int)in.bits[0];
    result.parts[1] = (unsigned int)in.bits[1];
    result.parts[2] = (unsigned int)in.bits[2];
    result.parts[6] = (unsigned int)in.bits[3];
    if (s21_decimal_get_sign(in))
        result = big_decimal_change_sign(result);
    return result;
}

s21_decimal big_decimal_to_decimal(big_decimal in) {
    // Число может быть отрицательным в доп.коде.
    printf("before convert res: \n");
    s21_print_big_decimal_bits(in);
    int sign = big_decimal_get_sign(in);
    if (sign) {
        int exp = big_decimal_get_exp(in);
        printf("exp = %d\n", exp);
        in = big_decimal_to_twos_complement(in);
        big_decimal_set_exp(&in, exp);
    }
    s21_decimal result = s21_decimal_get_zero();
    result.bits[0] = in.parts[0];
    result.bits[1] = in.parts[1];
    result.bits[2] = in.parts[2];
    // Теперь прописать экспоненту и знак
    s21_decimal_set_sign(&result, big_decimal_get_sign(in));
    s21_decimal_set_power(&result, big_decimal_get_exp(in));
    return result;
}

/**
 * @brief Функция возвращает big_decimal с одним единственным битом мантиссы выставленным по индексу. Такое число
 * удобно для проверки, установки или переворачивания одного бита другого числа.
 * @param index Индекс бита.
 * @return
 */
big_decimal big_decimal_get_bit(int index) {
    big_decimal result = big_decimal_get_zero();
    result.parts[index/32] = 1U << index%32;
    return result;
}

/**
 * @brief Функция возвращает 1 если бит мантиссы установлен, иначе возвращает 0
 * @param in
 * @param index Индекс бита.
 * @return
 */
unsigned int big_decimal_is_set_bit(big_decimal in, int index) {
    unsigned int res = 0;
    big_decimal bit = big_decimal_get_bit(index);
    if (!big_decimal_is_zero(big_decimal_and(in, bit)))
        res = 1U;
    return res;
}
/**
 * @brief Функция устанваливает в указанный бит мантиссы 1, если там был 0, либо ничего не делает.
 * (x OR y) = NOT(NOT(x) AND NOT(y))
 * Экспонента и знак не затрагиваются
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
 * @brief Функция возвращает 1 если знак (192 индекс) установлен. 
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
    if (big_decimal_get_sign(in) && sign == 0) {
        in.parts[6] = in.parts[6] - 1;
    } else if (!big_decimal_get_sign(in) && sign) {
        in.parts[6] = in.parts[6] + 1;
    }
    return in;
}

big_decimal big_decimal_change_sign(big_decimal in) {
    if (big_decimal_get_sign(in))
        in = big_decimal_set_sign(in, 0);
    else
        in = big_decimal_set_sign(in, 1);
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
 * @brief Функция возвращает дополнительный код мантиссы полученного big_decimal. Знак превдварительно зануляется,
 * чтобы не перевернулся. Экспонента обнуляется.
 * @param direct_code
 * @return
 */
big_decimal big_decimal_to_twos_complement(big_decimal direct_code) {
    direct_code = big_decimal_set_sign(direct_code, 0);
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
    unsigned int result = 1U;
    for (int i = 0; i < 6; ++i) {
        if (in.parts[i] != 0) {
            result = 0U;
            break;
        }
    }
    return result;
}

int big_decimal_get_exp(big_decimal in) {
    return (in.parts[6] & (255U << 16)) >> 16;
}

void big_decimal_set_exp(big_decimal* in, int exp) {
    unsigned int sign = big_decimal_get_sign(*in);
    (*in).parts[6] = ((unsigned int)exp) << 16;
    *in = big_decimal_set_sign(*in, sign);
}

unsigned int big_decimal_get_not_zero_bit(big_decimal in) {
    int i = 191;
    for (; i >=0; i--) {
        if (big_decimal_is_set_bit(in, i))
            break;
    }
    return i;
}
