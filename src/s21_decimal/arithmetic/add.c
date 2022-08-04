#include "./arithmetic.h"
#include "../helpers/helpers.h"

#include <stddef.h>
/**
 * @brief Функция принимает на входе два числа в формате Decimal и указатель для записи результата
 * Отрицательные числа записаны в прямом коде и в отдельном бите выставлен знак.
 * Сначала производится выравнивание экспонент. При выравнивании экспонент может произойти переполнение мантиссы. В
 * данном случае прекращаем повышать экспоненту у этого числа и понижаем экспоненту у второго, так как у него
 * больше знаков после запятой. Применяем округление сразу до нужного уровня экспоненты.
 * После выравнивания экспонент производим сложение мантисс, при котором тоже может возникнуть переполнение. Если
 * хотя бы у одного из чисел экспонента не равна 0, то можно произвести округление. В противном случае имеем окончатель-
 * ное переполнение разрядной сетки, о чём сообщаем в коде возврата.
 * @param value_1 Первое слагаемое.
 * @param value_2 Второе слагаемое.
 * @param result Указатель для записи суммы.
 * @return Код возврата.
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    s21_arithmetic_result raise_code;
    s21_decimal raised_exp = s21_decimal_get_zero();
    s21_decimal to_raise, second;
    int power_1 = s21_decimal_get_power(value_1);
    int power_2 = s21_decimal_get_power(value_2);
    if (power_1 != power_2) {
        if (power_1 > power_2) {
            to_raise = value_2;
            second = value_1;
        } else {
            to_raise = value_1;
            second = value_2;
        }
        while (s21_decimal_get_power(to_raise) != s21_decimal_get_power(second)) {
            raise_code = raise_exp(to_raise, &raised_exp);
            if (raise_code == S21_ARITHMETIC_OK) {
                to_raise = raised_exp;
            } else {
                break;
            }
        }
        if (s21_decimal_get_power(to_raise) != s21_decimal_get_power(second)) {
            // Выполнить округление второго числа на разницу текущих экспонент
            int exp_diff = s21_decimal_get_power(second) - s21_decimal_get_power(to_raise);
            // Надо второе число поделить с остатком на 10 в степени разницы
            s21_decimal div_res = s21_decimal_get_zero();
            s21_decimal remainder = s21_decimal_get_zero();
            s21_arithmetic_result div_code = s21_decimal_div_mant(second, s21_decimal_get_ten_pow(exp_diff - 1), &div_res, &remainder);
            if (div_code == S21_ARITHMETIC_OK) {
                s21_decimal second_div_res = s21_decimal_get_zero();
                s21_decimal second_remainder = s21_decimal_get_zero();
                s21_arithmetic_result second_div_code = s21_decimal_div_mant(div_res, s21_decimal_get_ten(),
                                                                             &second_div_res, &second_remainder);
                if (second_div_code == S21_ARITHMETIC_OK) {
                    if ((second_remainder.bits[0] == 5 && !s21_decimal_mant_is_zero(remainder)) ||
                        s21_decimal_is_set_bit(second_div_res, 0)) {
                        second_div_res = s21_decimal_add_mant(second_div_res, s21_decimal_get_one());
                    }
                    second = second_div_res;
                } else {
                    // Ошибка деления
                }
            } else {
                // Ошибка деления
            }
        }
    }
    *result = s21_decimal_add_mant(to_raise, second);
    if ((s21_decimal_get_sign(to_raise) ^ s21_decimal_get_sign(second)) != s21_decimal_get_sign(*result)) {
        // Произошло переполнение при сложении мантисс, но если есть экспонента, значит можно округлить

    }
    return code;
}
