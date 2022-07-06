#ifndef SRC_S21_DECIMAL__DEBUG_H_
#define SRC_S21_DECIMAL__DEBUG_H_

#include <stdint.h>

#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW  "\033[93m"
#define OKCYAN  "\033[96m"
#define RESET   "\033[0m"

void s21_print_bits(size_t const size, void const * const ptr, int color);
void s21_print_bit(int number, int color);
void s21_reverse_string(char *str);
void int128_to_str(unsigned __int128 x, char *res);
void format_decimal_to_str(s21_decimal decimal, char *res);
void s21_print_decimal_bits(s21_decimal decimal);
void s21_print_decimal_string(s21_decimal decimal);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Функции ниже не используются, но пригодятся для общего понимания
И являются универсальными
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @brief макрос, который позволяет для любого типа целочисленных данных использовать для печати
 * одно название print_bit(). 
 * После сборки программы макросы заменяются соответствующими макроопределениями в зависимости от типа данных
 * Например код:
 * 
 * int32_t a = 25;
 * print_bit(a);
 * uint32_t b = 25;
 * print_bit(b);
 * 
 * После сборки автоматиески будет заменен на:
 * 
 * int32_t a = 25;
 * print_bit_i32(a);
 * uint32_t b = 25;
 * print_bit_ui32(b);
 * 
 * При необходимости использования других типов, например, __int128,легко добавить новую функцию по аналогии
 */
#define print_bit(X)            \
    _Generic((X),               \
    uint64_t: print_bit_ui64,   \
    int64_t: print_bit_i64,     \
    int32_t: print_bit_i32,     \
    uint32_t: print_bit_ui32,   \
    default: print_bit_ui64     \
)(X)

void what_endian();
void print_bit_ui64(uint64_t number);
void print_bit_i64(int64_t number);
void print_bit_i32(int32_t number);
void print_bit_ui32(uint32_t number);

#endif  //  SRC_S21_DECIMAL__DEBUG_H_
