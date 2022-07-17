#include <stdlib.h>
#include <string.h>

#include "./conversion.h"

/**
 * @brief записывает в строку str битовое представление мантиссы числа number в виде строки
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

void s21_get_float_mantissa_bits_string(float number, char *str) {
    float_cast cast;
    cast.f = number;
    uint32_t mantissa = cast.parts.mantisa;
    char bits[33];
    char *ptr = str;

    s21_get_uint32_bits_string(mantissa, bits);

    for (size_t i = 0; i < strlen(bits); i++) {
        if (i < strlen(bits) - 23) {
            continue;
        }
        *(ptr++) = bits[i];
    }
    *(ptr++) = '\0';
}

/**
 * @brief записывает битовое представление переменной number в строку str
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param number переменная, битовое представление которой мы хотим получить
 * @param str строка, в которую записывается битовое представление переменная
 */
void s21_get_uint32_bits_string(uint32_t number, char *str) {
    s21_get_bits_string(sizeof(number), &number, str);
}

/**
 * @brief записывает битовое представление переменной размера size, указатель на которую размещен в ptr,
 * в строку str
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param size количество байт в переменной
 * @param ptr указатель на переменную
 * @param str строка, в которую записывается битовое представление переменной
 */
void s21_get_bits_string(size_t const size, void const * const ptr, char *str) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    char *sptr = str;

    for (int i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            if (byte == 1) {
                *(sptr++) = '1';
            } else {
                *(sptr++) = '0';
            }
        }
    }
    *(sptr++) = '\0';
}




