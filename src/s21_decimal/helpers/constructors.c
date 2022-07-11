#include <string.h>
#include "./helpers.h"
#include "./../binary/binary.h"

/**
 * @brief Возвращает заполненный decimal по данным аргументов
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param data1 int для bits[0]
 * @param data2 int для bits[1]
 * @param data3 int для bits[2]
 * @param data4 int для bits[3]
 * @return s21_decimal заполненный decimal
 */
s21_decimal s21_create_matrix_from_array(int data1, int data2, int data3, int data4) {
    s21_decimal decimal;

    decimal.bits[0] = data1;
    decimal.bits[1] = data2;
    decimal.bits[2] = data3;
    decimal.bits[3] = data4;

    return decimal;
}

/**
 * @brief Возвращает заполненный decimal по данным аргументов
 * 
 * @param sign знак для заполнения в bits[3]
 * @param power степень для заполнения в bits[3]
 * @param data1 int для bits[0]
 * @param data2 int для bits[1]
 * @param data3 int для bits[2]
 * @return s21_decimal заполненный decimal
 */
s21_decimal s21_create_matrix_from_data(int sign, int power, int data1, int data2, int data3) {
    s21_decimal decimal;
    s21_clear_decimal(&decimal);

    decimal.bits[0] = data1;
    decimal.bits[1] = data2;
    decimal.bits[2] = data3;

    s21_decimal_set_power(&decimal, power);
    s21_decimal_set_sign(&decimal, sign);

    return decimal;
}

/**
 * @brief зануляет все биты числа *decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal зануляемый decimal
 */
void s21_clear_decimal(s21_decimal *decimal) {
    decimal->bits[0] = 0;
    decimal->bits[1] = 0;
    decimal->bits[2] = 0;
    decimal->bits[3] = 0;
}

/**
 * @brief формирует и возвращает число (1) в виде decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (1)
 */
s21_decimal s21_decimal_get_one(void) {
    s21_decimal result;
    s21_clear_decimal(&result);
    result.bits[0] = 1;

    return result;
}

/**
 * @brief формирует и возвращает число (0) в виде decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (0)
 */
s21_decimal s21_decimal_get_zero(void) {
    s21_decimal result;
    s21_clear_decimal(&result);

    return result;
}
