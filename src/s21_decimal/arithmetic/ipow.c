#include "./arithmetic.h"
#include "./../helpers/helpers.h"
#include "./../_debug/_debug.h"
#include <stdio.h>

/**
 * @brief Функция для возведения decimal value в целую степень exp
 *
 * Для вычисления используем рекурсию и свойства степени из математики:
 * x^0 = 1
 * x^n = x*x^(n-1)
 * x^(-n) = 1 / x^n
 * 
 * Т.к. работаем с decimal, то используем в функции значения decimal и арифметику decimal
 * 
 * @param value decimal, возводимый в степень
 * @param exp степень, в которую возводится число
 * @param result указатель на decimal, куда запишется результат выполнения функции
 * @return int код ошибки:
0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
 */
int s21_ipow(s21_decimal value, int exp, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    s21_decimal tmp = s21_decimal_get_zero();

    if (exp == 0) {
        tmp = s21_decimal_get_one();
    } else if (exp < 0) {
        code = s21_ipow(value, -exp, &tmp);
        if (code == S21_ARITHMETIC_OK) {
            code = s21_div(s21_decimal_get_one(), tmp, result);
        }
    } else {
        code = s21_ipow(value, exp - 1, &tmp);
        if (code == S21_ARITHMETIC_OK) {
            code = s21_mul(value, tmp, result);
        }
    }
    *result = tmp;
    return code;
}
