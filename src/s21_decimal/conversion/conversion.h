#ifndef SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_
#define SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_

#include "./../types.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

/**
 * @brief коды ошибок функций-преобразователей
 * 0 - OK
 * 1 - ошибка конвертации
 */
typedef enum s21_conversion_result {
    S21_CONVERSION_OK = 0,
    S21_CONVERSION_ERROR = 1
} s21_conversion_result;

// Вспомогательные функции
void s21_get_float_mantissa_bits_string(float number, char *str);
void s21_get_uint32_bits_string(uint32_t number, char *str);
void s21_get_bits_string(size_t const size, void const * const ptr, char *str);

#endif  //  SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_
