#include <string.h>

#include "../../s21_decimal.h"

/**
 * @brief конвертирует float src в decimal dst
 * 
 * Т.к. минимальное число в decimal 1e-28, то алгоритм конвертации денормализованных float нам не нужен.
 * Нормализованные float конвертируем в decimal, исходя из алгоритма хранения чисел одинарной точности в
 * памяти: https://w.wiki/5RpW (Число одинарной точности)
 * 
 * Float занимает в памяти 8 байт и хранит три параметра:
 * - Знак
 * - Порядок
 * - Мантисса
 * (Более подробное описание структуры есть в union float_cast или по ссылке в вики выше)
 * 
 * Проще всего рассмотреть конвертацию на примере:
 * 
 * Возьмем число 0.15625
 * Представление впамяти 00111110 00100000 00000000 00000000
 * Знак: 0 - число положительное
 * Порядок: 01111100
 * Мантисса: 0100000 00000000 00000000
 * 
 * Порядок 01111100 - это 124. Но формат хранит степень со смещением 127, чтобы получить стпень вычисляем её
 * как 124 - 127 = -3
 * 
 * В нормализованном виде (а мы только такой вид и рассматриваем, как я писал выше) целая часть мантиссы
 * всегда равна 1 и не хранится в памяти. Поэтому реальная мантисса будет 1.01000000000000000000000
 * 
 * Значение float рассчитывается по следующей формуле:
 * float = мантисса * 2^степень
 * 
 * Для расчета необходимо мантиссу из двоичного вида перевести в десятичный:
 * Целая часть мантиссы (у нас всегда 1) = 1 * 2^0
 * Дробная часть мантиссы считается как: первый бит * 2^-1 + второй бит * 2^-2 + третий бит * 2^-3 + и т.д.
 * В нашей дробной части (01000000000000000000000) только второй бит равен 1 (остальное все 0,
 * поэтому суммируемые буду 0), получаем дробную мантиссу:
 * 0 * 2^-1 + 1 * 2^-2 + 0 * 2^-3 + ... = 1 * 2^-2
 * 
 * С учетом целой части мантисса = 1 * 2^0 + 1 * 2^-2
 * 
 * Итого наш float = мантисса * 2^степень = (1 * 2^0 + 1 * 2^-2) * 2^-3 = 2^0 * 2^-3 + 2^-2 * 2^-3
 * 
 * Чтобы не производить лишние вычисления степеней и умножения, можно использовать свойство степеней:
 * a^m * a^n = a^(m+n)
 * 
 * таким образом наше выражение примет вид:
 * 2^0 * 2^-3 + 2^-2 * 2^-3 = 2^(0 + -3) + 2^(-2 + -3) = 2^(-3) + 2^(-5)
 * 
 * Собственно вычисление 2^(-3) + 2^(-5) и даёт 0.15625
 * Т.к. в результате вычисления мы хотим получить число в формате decimal, то вычисление производим, 
 * используя математику decimal (числа decimal и функции арифметики decimal)
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый float
 * @param dst указатель на decimal, в который запишется результат функции
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации 
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    // TODO(hubertfu): добавить комментарии по коду
    // TODO(hubertfu): навести порядок
    s21_conversion_result code = S21_CONVERSION_OK;
    if (!dst) {
        code = S21_CONVERSION_ERROR;
    } else {
        s21_clear_decimal(dst);
        float_cast cast;
        cast.f = src;

        char float_bits_str[24];
        s21_get_float_mantissa_bits_string(src, float_bits_str);
        // s21_print_bit(cast.bytes, 0);
        // TODO(hubertfu): src == 0.0 float_exponent = -127, что делает много лишних расчетов
        int float_exponent = cast.parts.exponent - 127;
        // float f = 0.0;
        // f += 1 * pow(2, float_exponent);
        s21_decimal one = s21_decimal_get_one();
        s21_decimal two = s21_decimal_get_zero();
        s21_add(one, one, &two);
        // printf("one:");s21_print_decimal_bits(one);
        // printf("two:");s21_print_decimal_bits(two);
        s21_ipow(two, float_exponent, dst);
        // printf("\ndst:");s21_print_decimal_bits(*dst);
        // printf("f = decimal.Add(f, s21_ipow(two, %d));\n", float_exponent);
        for (int i = 0; i < (int) strlen(float_bits_str); i++) {
            if (float_bits_str[i] == '1') {
                s21_decimal tmp = s21_decimal_get_zero();
                s21_ipow(two, -i - 1 + float_exponent, &tmp);
                // printf("tmp:");s21_print_decimal_bits(tmp);
                s21_add(*dst, tmp, dst);
                // printf("dst:");s21_print_decimal_bits(*dst);
                // f += pow(2, -i-1 + float_exponent);
                // printf("f = decimal.Add(f, s21_ipow(two, %d));\n", -i-1 + float_exponent);
            }
        }

        if (cast.parts.sign == 1) {
            s21_decimal_set_sign(dst, 1);
        }

        // printf("%s\n", float_bits_str);
        // printf("[%.80f]\n", f);

        // s21_print_decimal_bits(*dst);
        // s21_print_decimal_string(*dst);
        // printf("%.50f\n", src);
        // printf("----------------------------------------------------------------------------------------\n");
    }

    return code;
}
