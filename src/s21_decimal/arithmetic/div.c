#include "./arithmetic.h"
#include "../helpers/helpers.h"
#include "../mant_ops/mant_ops.h"
#include <stdio.h>

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    *result = s21_decimal_get_zero();
    int exp_diff = s21_decimal_get_power(value_1) - s21_decimal_get_power(value_2);
    s21_decimal remainder = s21_decimal_get_zero();
    s21_decimal_div_mant(value_1, value_2, result, &remainder);
    fprintf(stdout, "res bits in div = %u %u\n", result->bits[1], result->bits[0]);
    fprintf(stdout, "remainder = %u %u\n", remainder.bits[1], remainder.bits[0]);
    s21_decimal temp_res = s21_decimal_get_zero();
    s21_decimal raised_res;
    if (!s21_decimal_mant_is_zero(remainder)) {
        fprintf(stdout, "suda ne popal");
        while (!s21_decimal_mant_is_zero(remainder)) {
            // Умножаем остаток на 10. Пока так, потом переделать на умножение мантисс
            raise_exp(remainder, &remainder);  // TODO Rambton Ovtime
            // Делим увеличенный остаток на делитель
            s21_decimal_div_mant(remainder, value_2, &temp_res, &remainder);
            // Умножаем основной результат на 10 чтобы дописать к нему цифру.
            int raise_code = raise_exp(*result, &raised_res);
            if (raise_code == S21_ARITHMETIC_OK) {
                // Переполнения результата нет, дописываем цифру
                *result = s21_decimal_add_mant(raised_res, temp_res);
                // И сохраняем экспоненту, которая была повышена тремя строками выше, но обнулена при сложении мантисс
                // А надо было просто отправлять не в сложение мантисс, а в обычное. Тогда экспонента не сбросится.
                // TODO Переделать вызов функции выше, а выставление экспоненты убрать.
                s21_decimal_set_power(result, s21_decimal_get_power(raised_res));
            } else {
                // Если появилось переполнение, значит у результата слишком длинная дробная часть. При возникновении такого
                // переполнения надо делать округление и прекращать вычисления. Если при переполнении результат деления
                // увеличенного остатка не 5, то можно смело делать округление на 1 знак. Если же цифра 5, то надо проверить
                // остаток. Вообще нижеследующую цепочку ифов хочется переделать.
                if (temp_res.bits[0] != 5) {
                    if (temp_res.bits[0] > 5) {
                        *result = s21_decimal_add_mant(*result, s21_decimal_get_one());
                        // при этом сложении тоже могло в одном единственном случае возникнуть переполнение.
                        // TODO Обработать
                    }
                    break;
                } else {
                    // Если остаток 0, значит 5 это последняя цифра, поэтому делаем финансовое округление.
                    // Если нет, то результат рано или поздно перевалит за 0.5. Значит округляем в бОльшую сторону.
                    if (s21_decimal_mant_is_zero(remainder)) {
                        if (!s21_decimal_is_set_bit(*result, 0)) {
                            // Ничего не делаем с результатом, если он чётный
                            break;
                        }
                    }
                    *result = s21_decimal_add_mant(*result, s21_decimal_get_one());
                    // при этом сложении тоже могло в одном единственном случае возникнуть переполнение.
                    // TODO Обработать
                    break;
                }
            }
        }
        // Теперь надо обработать экспоненту
        s21_decimal_set_power(result, s21_decimal_get_power(*result) + exp_diff);
        // И знак. Через исключающее ИЛИ
        s21_decimal_set_sign(result, s21_decimal_get_sign(value_1) ^ s21_decimal_get_sign(value_2));
    }
    return code;
}
