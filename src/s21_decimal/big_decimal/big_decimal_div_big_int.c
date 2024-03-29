//
// Created by gubankov on 11.08.22.
//
#include <stdio.h>

#include "../../tests/_helpers/_debug.h"
#include "../arithmetic/arithmetic.h"
#include "big_decimal.h"

int big_decimal_div_big_int(big_decimal dividend, big_decimal divisor,
                            big_decimal *result, big_decimal *remainder) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;
  // Фиксируем знак результата
  int sign = big_decimal_get_sign(dividend) ^ big_decimal_get_sign(divisor);
  // Сбрасываем знак у делимого
  dividend = big_decimal_set_sign(dividend, 0);
  *result = big_decimal_get_zero();
  // Обработка частных случаев
  if (big_decimal_is_zero(divisor)) {  // Деление на 0
    code = S21_ARITHMETIC_ZERO_DIV;
  } else if (big_decimal_compare(big_decimal_set_sign(divisor, 0),
                                 big_decimal_set_sign(dividend, 0)) == 1) {
    //  Делитель больше делимого по модулю
    *result = big_decimal_get_zero();
    *remainder = dividend;
  } else {  // делим
    // Сдвиг делителя на уровень старшего значащего бита делимого
    // Сначала вычисляем размер сдвига
    int shift_size = big_decimal_get_not_zero_bit(dividend) -
                     big_decimal_get_not_zero_bit(divisor);
    // Потом сдвигаем делитель
    big_decimal shifted_divisor = big_decimal_shift_left(divisor, shift_size);
    // Проставляем знак
    shifted_divisor = big_decimal_set_sign(shifted_divisor, 1);
    big_decimal sum = big_decimal_get_zero();
    for (int i = 0; i <= shift_size; i++) {
      // Сдвигаем результат для записи нового бита
      *result = big_decimal_shift_left(*result, 1);
      // Складываем делимое и отрицательный делитель
      sum = big_decimal_add_big_int(dividend, shifted_divisor);
      // Если сумма (промежуточный остаток) больше или равна 0, то сохраняем её
      // в качестве делимого, а в результат дописываем 1. Если же сумма
      // отрицательная, то записывать ничего не надо -- там и так ноль после
      // сдвига результата. И делимое тоже не меняем чтобы сдвинулось ещё на
      // один порядок.
      if (!big_decimal_get_sign(sum)) {
        dividend = sum;
        *result = big_decimal_set_bit(*result, 0);
      }
      // Сдвигаем делитель на один разряд вправо
      if (i != shift_size) {
        shifted_divisor = big_decimal_shift_right(shifted_divisor, 1);
      }
    }
    if (big_decimal_get_sign(sum))
      *remainder = dividend;
    else
      *remainder = sum;
  }
  *result = big_decimal_set_sign(*result, sign);
  return code;
}
