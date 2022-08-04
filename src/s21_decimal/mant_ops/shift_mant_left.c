//
// Created by gubankov on 30.07.22.
//
#include "./mant_ops.h"
#include "../helpers/helpers.h"
#include <stdio.h>
#include "../../tests/_helpers/_debug.h"


/**
 * @brief Функция принимает на входе decimal, количество сдвигов и указатель для записи переполнения, если
 * таковое будет. Сдвиг влево осуществляется для всех битов мантиссы.
 * @param decimal Пациент, но лечить будем не его, а копию.
 * @param index Количество сдвигов
 * @param over Указатель для записи переполнения
 * @return Новый decimal с нулевым знаком и нулевой экспонентой
 * @author Rambton Ovtime (rambtono@student.21-school.ru)
 */
s21_decimal s21_decimal_shift_mant_left(s21_decimal decimal, int index, s21_decimal* over) {
    s21_decimal res = decimal;
    s21_decimal_set_sign(&res, 0);
    s21_decimal_set_power(&res, 0);
    fprintf(stdout, "To shift:\n");
    s21_print_decimal_bits(res);
    fprintf(stdout, "Process shift:\n");
    while (index > 0) {
        // По хорошему, over тоже может переполниться, если запросить сдвиг очень большого числа
        // больше, чем на 96
        if (over) {
            *over = s21_decimal_shift_mant_left(*over, 1, NULL);
            if (s21_decimal_is_set_bit(res, 95))
                *over = s21_decimal_set_bit(*over, 0);
        }
        for (int i = 2; i >= 0; i--) {
            unsigned int part = res.bits[i];
            part = part << 1;
            if (i && s21_is_set_bit(res.bits[i - 1], 31)) {
                part = s21_set_bit(part, 0);
            }
            res.bits[i] = part;
        }
        s21_print_decimal_bits(res);
        index--;
    }
    return res;
}