//
// Created by gubankov on 30.07.22.
//
#include "mant_ops.h"
#include "../helpers/helpers.h"
#include "../binary/binary.h"
#include "../arithmetic/arithmetic.h"
#include "../../tests/_helpers/_debug.h"
#include <stdio.h>

/**
 * @brief Функция производит целочисленное деление мантисс.
 * Решил реализовать с проверкой деления на 0. Потому что иначе эту проверку надо делать везде, где
 * вызывается эта функция, что не есть удобно. В случае деления на 0 возвращаем 3, как и в спецификации
 * арифметических операторов в задании.
 * Аналогично, чтобы не заниматься занулением экспонент и знаков во всех местах вызова, эта операция будет
 * производиться тут?
 * @param a делимое
 * @param b делитель
 * @param res Указатель для записи результата деления
 * @param remainder указатель для сохранения остатка
 * @return code
 * @author Rambton Ovtime (rambtono@student.21-school.ru)
 */
int s21_decimal_div_mant(s21_decimal dividend, s21_decimal divisor, s21_decimal* res, s21_decimal* remainder) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    fprintf(stdout, "tut7\n");
    fprintf(stdout, "tut8\n");
    if (s21_decimal_mant_is_zero(divisor)) {
        fprintf(stdout, "tut9\n");
        fprintf(stdout, "tut10\n");
        code = S21_ARITHMETIC_ZERO_DIV;  // Обработка деления на 0
    } else if (s21_decimal_mant_is_zero(dividend)) {
        fprintf(stdout, "tut11\n");
        fprintf(stdout, "tut12\n");
        // Обработка деления нуля
        *res = s21_decimal_get_zero();
        *remainder = s21_decimal_get_zero();
    } else if (s21_decimal_mant_compare(divisor, dividend) == 1) {
        fprintf(stdout, "tut13\n");
        fprintf(stdout, "tut14\n");
        // Делитель больше делимого
        *res = s21_decimal_get_zero();
        *remainder = dividend;
    } else {
        fprintf(stdout, "tut15\n");
        fprintf(stdout, "tut16\n");
        // Зануляем экспоненты и знаки
        s21_decimal_set_power(&dividend, 0);
        s21_decimal_set_power(&divisor, 0);
        s21_decimal_set_sign(&dividend, 0);
        s21_decimal_set_sign(&divisor, 0);
        // Сдвиг делителя на уровень старшего значащего бита делимого
        // Сначала вычисляем размер сдвига
        int shift_size = s21_decimal_get_not_zero_bit(dividend) - s21_decimal_get_not_zero_bit(divisor);
        fprintf(stdout, "shift_size = %d\n", shift_size);
        // Потом сдвигаем
        // Переполнения быть не может поэтому третьим аргументом передаём null
        s21_decimal shifted_divisor = s21_decimal_shift_mant_left(divisor, shift_size, NULL);
        // Получаем обратный код делителя
        fprintf(stdout, "shifted, reversed and added divisor:\n");
        s21_print_decimal_bits(shifted_divisor);
        shifted_divisor = s21_decimal_binary_not(shifted_divisor);
        s21_print_decimal_bits(shifted_divisor);
        // Получаем дополнительный код делителя
        shifted_divisor = s21_decimal_add_mant(shifted_divisor, s21_decimal_get_one());
        s21_print_decimal_bits(shifted_divisor);
        // Тут должен начинаться цикл длительностью shift_size
        s21_decimal sum = s21_decimal_get_zero();

            for (int i = 0; i <= shift_size; i++) {
                fprintf(stdout, "tut17\n");
                fprintf(stdout, "tut18\n");
                // Сдвигаем результат для записи нового бита
                *res = s21_decimal_shift_mant_left(*res, 1, NULL);
                // Складываем делимое и дополнительный код делителя
                sum = s21_decimal_add_mant(dividend, shifted_divisor);
                // Если сумма (промежуточный остаток) больше или равна 0, то сохраняем её в качестве делимого,
                // а в результат дописываем 1. Если же сумма отрицательная, то записывать ничего не надо -- там и так
                // ноль после сдвига результата. И делимое тоже не меняем чтобы сдвинулось ещё на один порядок.
                if (s21_decimal_get_sign(sum) == 0) {
                    fprintf(stdout, "sum > 0\n");
                    dividend = sum;
                    *res = s21_decimal_set_bit(*res, 0);
                }
                // Сдвигаем делимое на один разряд влево
                if (shift_size != 0) {
                    dividend = s21_decimal_shift_mant_left(dividend, 1, NULL);
                }
                fprintf(stdout, "loop number = %d\n", i);
                fprintf(stdout, "res in div mant in loop = %u %u\n", res->bits[1], res->bits[0]);
            }
        if (s21_decimal_get_sign(sum))
            *remainder = dividend;
        else
            *remainder = sum;
        *remainder = s21_decimal_shift_mant_right(*remainder, shift_size);

    }
    fprintf(stdout, "res in div mant = %u\n", res->bits[0]);
    return code;
}