#include "./../helpers/helpers.h"
#include "./arithmetic.h"

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
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param base decimal, возводимый в степень
 * @param exp степень, в которую возводится число
 * @param error int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * @return s21_decimal результат возведения в степнь числа decimal выполнения функции
 */
s21_decimal s21_ipow(s21_decimal base, int exp, int *error) {
    s21_decimal result;

    if (exp == 0) {
        result = s21_decimal_get_one();
    } else if (exp < 0) {
        s21_decimal div = s21_ipow(base, -exp, error);
        int code = s21_div(s21_decimal_get_one(), div, &result);
        if (code != S21_ARITHMETIC_OK) {
            result = s21_decimal_get_zero();
        }
        if (error) {
            *error = code;
        }
    } else {
        s21_decimal mul = s21_ipow(base, exp - 1, error);
        int code = s21_mul(base, mul, &result);
        if (code != S21_ARITHMETIC_OK) {
            result = s21_decimal_get_zero();
        }
        if (error) {
            *error = code;
        }
    }

    return result;
}
