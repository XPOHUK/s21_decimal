#include "./helpers.h"

/**
 * @brief проверяет корректность данных, записаных в decimal
 * 
 * 
 * Данные некорректны если выполняется хотя бы одно условие:
 * 1) в bits[3] биты от 0 до 15 не равны нулю.
 * 2) в bits[3] биты с 16 по 23 содержат показатель степени вне диапазона [0, 28].
 * 3) в bits[3] биты с 24 по 30 не равны нулю.
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal проверяемый decimal
 * @return int 1 - ок, 0 - некорректные данные
 */
int s21_is_correct_decimal(s21_decimal decimal) {
    if (s21_decimal_get_empty1(decimal) != 0 || s21_decimal_get_empty2(decimal) != 0) {
        return 0;
    }

    int power = s21_decimal_get_power(decimal);
    if (power < 0 || power > 28) {
        return 0;
    }

    return 1;
}

/**
 * @brief возвращает знак decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal проверяемый decimal
 * @return int 1 - отрицательный decimal, 0 - положительный decimal
 */
int s21_decimal_get_sign(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.sign;
}

/**
 * @brief возвращает степень decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal проверяемый decimal
 * @return int значение степени decimal
 */
int s21_decimal_get_power(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.power;
}

/**
 * @brief возвращает значение битов с 24 по 30 в bits[3]
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal проверяемый decimal
 * @return int значение битов
 */
int s21_decimal_get_empty1(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.empty1;
}

/**
 * @brief возвращает значение битов с 0 до 15 в bits[3]
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal проверяемый decimal
 * @return int значение битов
 */
int s21_decimal_get_empty2(s21_decimal decimal) {
    decimal_bit3 bits3;
    bits3.i = decimal.bits[3];

    return bits3.parts.empty2;
}

/**
 * @brief устанавливает для decimal знак sign
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal меняемый decimal
 * @param sign устанавливаемый знак, 1 - отрицательный decimal, 0 - положительный decimal.
 * Любой sign, отличный от 0, установит знак 1
 */
void s21_decimal_set_sign(s21_decimal *decimal, int sign) {
    decimal_bit3 bits3;
    bits3.i = decimal->bits[3];
    if (sign == 0) {
        bits3.parts.sign = 0;
    } else {
        bits3.parts.sign = 1;
    }

    decimal->bits[3] = bits3.i;
}

/**
 * @brief устанавливает для decimal степень
 *  
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal меняемый decimal
 * @param power устанавливаемая степень
 * 
 */
void s21_decimal_set_power(s21_decimal *decimal, int power) {
    decimal_bit3 bits3;
    bits3.i = decimal->bits[3];
    bits3.parts.power = power;

    decimal->bits[3] = bits3.i;
}
