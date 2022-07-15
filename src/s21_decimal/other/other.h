#ifndef SRC_S21_DECIMAL_OTHER_OTHER_H_
#define SRC_S21_DECIMAL_OTHER_OTHER_H_

#include "./../types.h"

int s21_truncate(s21_decimal value, s21_decimal *result);

/**
 * @brief коды ошибок других функций
 * 0 - OK
 * 1 - ошибка вычисления
 */
typedef enum s21_other_result {
    S21_OTHER_OK = 0,
    S21_OTHER_ERROR = 1
} s21_other_result;

#endif  //  SRC_S21_DECIMAL_OTHER_OTHER_H_
