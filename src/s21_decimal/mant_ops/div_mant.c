//
// Created by gubankov on 30.07.22.
//
#include "mant_ops.h"
#include "../helpers/helpers.h"
#include "../binary/binary.h"
#include "../arithmetic/arithmetic.h"

/**
 * @brief Функция производит целочисленное деление мантисс.
 * Решил реализовать с проверкой деления на 0. Потому что иначе эту проверку надо делать везде, где
 * вызывается эта функция, что не есть удобно. В случае деления на 0 возвращаем 3, как и в спецификации
 * арифметических операторов в задании.
 * Аналогично, чтобы не заниматься занулением экспонент и знаков во всех местах вызова, эта операция будет
 * производиться тут.
 * @param a делимое
 * @param b делитель
 * @param res Указатель для записи результата деления
 * @param remainder указатель для сохранения остатка
 * @return code
 * @author Rambton Ovtime (rambtono@student.21-school.ru)
 */
int s21_decimal_div_mant(s21_decimal dividend, s21_decimal divisor, s21_decimal* res, s21_decimal* remainder) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    if (s21_decimal_mant_is_zero(divisor)) {
        code = S21_ARITHMETIC_ZERO_DIV;  // Обработка деления на 0
    } else if (s21_decimal_mant_is_zero(dividend)) {
        // Обработка деления нуля
        *res = s21_decimal_get_zero();
        *remainder = s21_decimal_get_zero();
    } else if (s21_decimal_mant_compare(divisor, dividend)) {
        // Делитель больше делимого
        *res = s21_decimal_get_zero();
        *remainder = dividend;
    } else {
        // Зануляем экспоненты и знаки
        s21_decimal_set_power(&dividend, 0);
        s21_decimal_set_power(&divisor, 0);
        s21_decimal_set_sign(&dividend, 0);
        s21_decimal_set_sign(&divisor, 0);
        // Сдвиг делителя на уровень старшего значащего бита делимого
        // Сначала вычисляем размер сдвига
        int shift_size = s21_decimal_get_not_zero_bit(dividend) - s21_decimal_get_not_zero_bit(divisor);
        // Потом сдвигаем
        // Переполнения быть не может поэтому третьим аргументом передаём null
        s21_decimal shifted_divisor = s21_decimal_shift_mant_left(divisor, shift_size, null);
        // Получаем обратный код делителя
        shifted_b = s21_decimal_binary_not(shifted_divisor);
        // Получаем дополнительный код делителя
        shifted_divisor = s21_decimal_add_mant(shifted_divisor, s21_decimal_get_one());
        // Тут должен начинаться цикл длительностью shift_size
        s21_decimal sum = s21_decimal_get_zero();
        for (int i = 0; i <= shift_size; i++) {
            // Сдвигаем результат для записи нового бита
            *res = s21_decimal_shift_mant_left(*res, 1, null);
            // Складываем делимое и дополнительный код делителя
            sum = s21_decimal_add_mant(dividend, shifted_divisor);
            // Если сумма (промежуточный остаток) больше или равна 0, то сохраняем её в качестве делимого,
            // а в результат дописываем 1. Если же сумма отрицательная, то записывать ничего не надо -- там и так
            // ноль после сдвига результата. И делимое тоже не меняем чтобы сдвинулось ещё на один порядок.
            if (s21_decimal_get_sign(sum) == 0) {
                dividend = sum;
                *res = s21_decimal_set_bit(*res, 0);
            }
            // Сдвигаем делимое на один разряд влево
            dividend = s21_decimal_shift_mant_left(dividend, 1, null);
        }
        if (s21_decimal_get_sign(sum))
            *remainder = dividend;
        else
            *remainder = sum;
        *remainder = s21_decimal_shift_mant_right(*remainder, shift_size, null);
    }
    return code;
}