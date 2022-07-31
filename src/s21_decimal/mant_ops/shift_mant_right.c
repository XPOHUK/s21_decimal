//
// Created by gubankov on 30.07.22.
//
#include "./mant_ops.h"
#include "../helpers/helpers.h"


/**
 * @brief Функция принимает на входе decimal, количество сдвигов.
 * Сдвиг влево осуществляется для всех битов мантиссы.
 * @param decimal Пациент, но лечить будем не его, а копию.
 * @param index Количество сдвигов
 * @return Новый decimal с нулевым знаком и нулевой экспонентой
 * @author Rambton Ovtime (rambtono@student.21-school.ru)
 */
s21_decimal s21_decimal_shift_mant_right(s21_decimal decimal, int index) {
    s21_decimal res = decimal;
    s21_decimal_set_sign(&res, 0);
    s21_decimal_set_power(&res, 0);
    while (index > 0) {
        for (int i = 2; i >= 0; i++) {
            unsigned int part = res.bits[i];
            part = part << 1;
            if (i && s21_is_set_bit(decimal.bits[i - 1], 31))
                s21_set_bit(part, 0);
            res->bits[i] = part;
        }
        index--;
    }
    return res;
}