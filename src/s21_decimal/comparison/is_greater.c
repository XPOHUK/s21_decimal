#include "./comparison.h"
#include "../binary/binary.h"
#include "./../helpers/helpers.h"
/**
 * @file is_greater.c
 * @author Isle Annamae (isleanna@student.21-school.ru)
 * @brief Возвращает значение, позволяющее определить, действительно ли
 * заданное значение типа Decimal больше другого заданного значения типа Decimal.
 * Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.
 * @param value_1 Первое сравниваемое значение.
 * @param value_2 Второе сравниваемое значение.
 * @return Код возврата:
 *         0 - FALSE
 *         1 - TRUE
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;

    // Извлекаем знаки обоих значений и записываем их в соответствующие переменные.
    int value_1_sign = s21_decimal_get_sign(value_1);
    int value_2_sign = s21_decimal_get_sign(value_2);

    // Если оба значения равны.
    if (s21_is_equal(value_1, value_2)) {
        code = S21_COMPARISON_FALSE;
    // Если знак первого значения отрицательный, а второго - положительный.
    } else if (value_1_sign > value_2_sign) {
        code = S21_COMPARISON_FALSE;
    // Если знак первого значения положительный, а второго - отрицательный.
    } else if (value_1_sign < value_2_sign) {
        code = S21_COMPARISON_TRUE;
    // Если знаки обоих значений равны, то выполняется побитовое сравнение.
    } else if (value_1_sign == value_2_sign) {
        // Здесь необходима функция для выравнивания степеней(&value_1, &value_2);
        for (int i = 95; i >= 0; i--) {
            int value_1_bit = s21_decimal_is_set_bit(value_1, i);
            int value_2_bit = s21_decimal_is_set_bit(value_2, i);

            if (value_1_bit > value_2_bit) {
                code = S21_COMPARISON_TRUE;
                break;
            } else if (value_1_bit < value_2_bit) {
                code = S21_COMPARISON_FALSE;
                break;
            }
        }
        // Обработка ситуации, когда знаки обоих значений отрицательные.
        if (value_1_sign == 1) {
            if (code == S21_COMPARISON_TRUE) {
                code = S21_COMPARISON_FALSE;
            } else {
                code = S21_COMPARISON_TRUE;
            }
        }
    }
    return code;
}
