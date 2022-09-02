#include "../helpers/helpers.h"
#include "./../arithmetic/arithmetic.h"
#include "./conversion.h"

/**
 * @brief возвращает число в виде decimal, соответствующее цифре в виде char
 * Допустимые значения char c: '0' - '9'
 * Валидация данных не осуществляется и должна происходить за пределами функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param c проверяемый символ
 * @return s21_decimal число в виде decimal
 */
s21_decimal s21_decimal_get_from_char(char c) {
  s21_decimal result;

  switch (c) {
    case '0':
      result = s21_decimal_get_zero();
      break;
    case '1':
      result = s21_decimal_get_one();
      break;
    case '2':
      s21_from_int_to_decimal(2, &result);
      break;
    case '3':
      s21_from_int_to_decimal(3, &result);
      break;
    case '4':
      s21_from_int_to_decimal(4, &result);
      break;
    case '5':
      s21_from_int_to_decimal(5, &result);
      break;
    case '6':
      s21_from_int_to_decimal(6, &result);
      break;
    case '7':
      s21_from_int_to_decimal(7, &result);
      break;
    case '8':
      s21_from_int_to_decimal(8, &result);
      break;
    case '9':
      s21_from_int_to_decimal(9, &result);
      break;
  }

  return result;
}

/**
 * @brief Получаем степень числа float в виде строки в научной нотации
 * Например:
 * 1.435412E-04 - получим -4
 * 1.435412E+03 - получим 3
 *
 * Если получить степень  не получится, то функция вернет 0
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param str float в научной нотации в виде строки
 * @return int полученная степень
 */
int s21_get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr) {
    if (*ptr == 'E') {
      ++ptr;
      result = strtol(ptr, NULL, 10);
      break;
    }
    ++ptr;
  }

  return result;
}

/**
 * @brief переводит строку с научной нотацией float в decimal. Научная нотация
 * должна содержать не более 6 цифр после запятой
 *
 * Например:
 *
 * 5.123456E+2 - обрабатываем каждую цифру и прибавляем к результату:
 *
 * result = 0;
 * 5: result += 5 * 1000000
 * 1: result += 1 * 100000
 * 2: result += 2 * 10000
 * 3: result += 3 * 1000
 * 4: result += 4 * 100
 * 5: result += 5 * 10
 * 6: result += 6 * 1
 * Итого: 5123456
 *
 * Далее корректируем decimal, анализируя степень float (умножая или деля
 * decimal): 5123456 / 10000 = 512.3456
 *
 * Если float содержит меньше цифр, то ничего страшного:
 *
 * 5.1E+2 - обрабатываем каждую цифру и прибавляем к результату:
 *
 * result = 0;
 * 5: result += 5 * 1000000
 * 1: result += 1 * 100000
 * Итого: 5100000
 * Корректируем decimal:
 * 5100000 / 10000 = 510.0000
 *
 *
 * Валидация данных не осуществляется, на вход поступают уже проверенные данные
 * из диапазона представимых в decimal чисел
 *
 * @param str строка с научной нотацией float в decimal
 * @return s21_decimal полученный decimal
 */
s21_decimal s21_float_string_to_decimal(char *str) {
  int digits_counter = 6;
  s21_decimal result = s21_decimal_get_zero();
  char *ptr = str;

  // Получаем в любом случае заново степень float из научной записи, а не
  // передаем полученную ранее в s21_from_float_to_decimal, т.к. она могла
  // измениться из-за округления
  int exp = s21_get_float_exp_from_string(str);

  while (*ptr) {
    if (*ptr == '.') {
      // Точку игнорируем, итоговую степень decimal мы будем отдельно считать
      ++ptr;
      continue;
    } else if (*ptr >= '0' && *ptr <= '9') {
      // Переводим цифры в строке в decimal, начиная с первой, используя
      // арифметику decimal
      s21_decimal tmp = s21_decimal_get_zero();
      s21_mul(s21_decimal_get_from_char(*ptr),
              s21_decimal_get_ten_pow(digits_counter), &tmp);
      s21_add(result, tmp, &result);
      --digits_counter;
      ++ptr;
    } else {
      break;
    }
  }
  // Учитываем, что в научной записи степень уже сдвинутая, чтобы далее
  // корректно выставить степень decimal
  exp = exp - 6;

  if (exp > 0) {
    // Для положительной степени производим умножение на 10^exp
    s21_mul(result, s21_decimal_get_ten_pow(exp), &result);
  } else if (exp < 0) {
    // Для отрицательной степени производим деление на 10^exp
    if (exp < -28) {
      // Отдельно обрабатываем очень маленькие степени, т.к. мы не сможем
      // поделить больше чем на 10^28
      s21_div(result, s21_decimal_get_ten_pow(28), &result);
      exp += 28;
    }
    s21_div(result, s21_decimal_get_ten_pow(-exp), &result);
  }

  // Наслаждаемся результатом
  return result;
}
