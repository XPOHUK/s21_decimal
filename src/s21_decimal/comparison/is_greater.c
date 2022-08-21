#include "./comparison.h"
#include "./../binary/binary.h"
#include "./../big_decimal/big_decimal.h"
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
    big_decimal big_decimal_1 = decimal_to_big_decimal(value_1);
    big_decimal big_decimal_2 = decimal_to_big_decimal(value_2);

    // Извлекаем знаки обоих значений и записываем их в соответствующие переменные.
    int big_decimal_1_sign = big_decimal_get_sign(big_decimal_1);
    int big_decimal_2_sign = big_decimal_get_sign(big_decimal_2);

    // Если оба значения равны.
    if (s21_is_equal(value_1, value_2)) {
        code = S21_COMPARISON_FALSE;
    // Если знак первого значения отрицательный, а второго - положительный.
    } else if (big_decimal_1_sign > big_decimal_2_sign) {
        code = S21_COMPARISON_FALSE;
    // Если знак первого значения положительный, а второго - отрицательный.
    } else if (big_decimal_1_sign < big_decimal_2_sign) {
        code = S21_COMPARISON_TRUE;
    // Если знаки обоих значений равны, то выполняется побитовое сравнение.
    } else if (big_decimal_1_sign == big_decimal_2_sign) {
        big_decimal_balance_exp(&big_decimal_1, &big_decimal_2);
        for (int i = 191; i >= 0; i--) {
            int big_decimal_1_bit = big_decimal_is_set_bit(big_decimal_1, i);
            int big_decimal_2_bit = big_decimal_is_set_bit(big_decimal_2, i);

            if (big_decimal_1_bit > big_decimal_2_bit) {
                code = S21_COMPARISON_TRUE;
                break;
            } else if (big_decimal_1_bit < big_decimal_2_bit) {
                code = S21_COMPARISON_FALSE;
                break;
            }
        }
        // Обработка ситуации, когда знаки обоих значений отрицательные.
        if (big_decimal_1_sign == 1) {
            if (code == S21_COMPARISON_TRUE) {
                code = S21_COMPARISON_FALSE;
            } else {
                code = S21_COMPARISON_TRUE;
            }
        }
    }
    return code;
}
