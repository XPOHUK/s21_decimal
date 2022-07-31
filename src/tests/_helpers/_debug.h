#ifndef SRC_TESTS__HELPERS__DEBUG_H_
#define SRC_TESTS__HELPERS__DEBUG_H_

#include "../../s21_decimal.h"

#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW  "\033[93m"
#define OKCYAN  "\033[96m"
#define RESET   "\033[0m"

void s21_print_bits(size_t const size, void const * const ptr, int color);
void s21_print_bit(int number, int color);
void s21_decimal_to_string(s21_decimal decimal, char *res);
void s21_format_decimal_to_str(s21_decimal decimal, char *res);
void s21_print_decimal_bits(s21_decimal decimal);
void s21_print_decimal_string(s21_decimal decimal);
char* s21_bin128_to_string(s21_decimal decimal);

#endif  //  SRC_TESTS__HELPERS__DEBUG_H_
