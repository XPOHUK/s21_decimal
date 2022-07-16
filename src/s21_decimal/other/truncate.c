#include <stdio.h>
#include "./other.h"
#include "./../_debug/_debug.h"
#include "./../helpers/helpers.h"
#include "./../binary/binary.h"

/**
 * @brief Возвращает целые цифры указанного Decimal числа.
 * Любые дробные цифры отбрасываются, включая конечные нули.
 * 
 * 123.999 -> 123
 * 123.000 -> 123
 * 123 -> 123
 * 
 * Для получения целой части выполняем n раз (где n - показатель степени decimal)
 * деление 96-разрядного целого числа (bits[0], bits[1], bits[2]) на 10
 * 
 * Затем корректно выставляем знак, анализируя знак исходного числа
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value обрабатываемый decimal
 * @param result указатель на decimal, куда запишется результат выполнения функции
 * @return int код ошибки:
 *      0 - OK
 *      1 - ошибка вычисления
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    if (!result || !s21_is_correct_decimal(value)) {
        code = S21_OTHER_ERROR;
    } else {
        s21_clear_decimal(result);

        s21_decimal tmp = value;
        tmp.bits[3] = 0;

        int power = s21_decimal_get_power(value);
        while (power > 0) {
            tmp = s21_decimal_binary_division(tmp, s21_decimal_get_ten(), NULL);
            --power;
        }

        *result = tmp;
        if (s21_decimal_get_sign(value) == 1) {
            s21_decimal_set_sign(result, 1);
        }
    }
    return code;
}
