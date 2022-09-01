#include "./binary.h"

/**
 * @brief Функция бинарного сложения двоичных положительных чисел.
 * 
 * Функция берет двоичное представление всех 128 бит числа decimal1 и прибавляет двоичное представление
 * всех 128 бит числа decimal2
 * 
 * Складываем, начиная с младших разрядов:
 * 1) Если соответствующие разряды обоих слагаемых содержат ноли, то и сумма ноль. 
 * 2) Если в соответствующих разрядах только одно из слагаемых содержит единицу, то и сумма единица.
 * 3) Если соответствующие разряды обоих слагаемых содержат единицы, то сумма двух единиц дает число два,
 * которое в двоичной системе отображается как 10, т.е. это уже двухразрядное число с нулем в младшем
 * разряде. Поэтому в тот же разряд суммы ставим ноль, а единицу переносим в следующий разряд.
 * 
 * Например, для 8 бит:
 * A:   1 0 1 0 0 1 1 1
 * B: + 0 0 0 1 0 0 0 1
 *      ---------------
 * C: = 1 0 1 1 1 0 0 0
 * 
 * Это можно сделать циклом в 8 операций. Но для ускорения расчета можно использовать битовые операции:
 * побитовое И (&), сдвиг влево(<<) и исключающее ИЛИ(^), что в среднем использует меньшее количество
 * операций, чем цикл.
 * 
 * Алгоритм:
 * 1) A & B, мы получаем все биты, где потребуется перенос единицы в следующий разряд:
 *   A: 1 0 1 0 0 1 1 1
 *   B: 0 0 0 1 0 0 0 1
 *      ---------------
 * A&B: 0 0 0 0 0 0 0 1
 * 
 * 2) Сдвигаем полученное число на 1 влево (т.к. полученные единицы переносятся в следующий разряд):
 * A&B: 0 0 0 0 0 0 0 1
 *      ---------------
 * <<1: 0 0 0 0 0 0 1 0
 * 3) Выполняем A^B (фактически получим результат сложения битов, без учета переносов единиц
 * в следующие разряды):
 *   A: 1 0 1 0 0 1 1 1
 *   B: 0 0 0 1 0 0 0 1
 *      ---------------
 * A^B: 1 0 1 1 0 1 1 0
 * 
 * 4) Получаем промежуточный результат сложения, теперь нам необходимо к этому результату прибавить результат
 * из п.2. Фактически алгоритм 1-3 повторяется, только вместо B прибавляется теперь результат п.2. Повторяем
 * до тех пор, пока в п.2 не получим 0 0 0 0 0 0 0 0:
 * 
 *   A: 1 0 1 1 0 1 1 0
 *   B: 0 0 0 0 0 0 1 0
 * A&B: 0 0 0 0 0 0 1 0
 * <<1: 0 0 0 0 0 1 0 0
 * A^B: 1 0 1 1 0 1 0 0
 * 
 *   A: 1 0 1 1 0 1 0 0
 *   B: 0 0 0 0 0 1 0 0
 * A&B: 0 0 0 0 0 1 0 0
 * <<1: 0 0 0 0 1 0 0 0
 * A^B: 1 0 1 1 0 0 0 0
 * 
 *   A: 1 0 1 1 0 0 0 0
 *   B: 0 0 0 0 1 0 0 0
 * A&B: 0 0 0 0 0 0 0 0
 * <<1: 0 0 0 0 0 0 0 0
 * A^B: 1 0 1 1 1 0 0 0
 * 
 * Итого сумма:
 * 1 0 1 1 1 0 0 0
 * 
 * Ситуация с переполнением при сложении никак не контролируется, т.к. это бинарная операция (как и при
 * складывании интов). Т.к. у decimal основание занимает только 96бит, то переполнение децимал можно
 * контролировать по биту 96.
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal1 первое слагаемое
 * @param decimal2 второе слагаемое
 * @return s21_decimal сумма decimal1 и decimal2
 * 
 */
s21_decimal s21_decimal_binary_addition(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = decimal1;
    s21_decimal tmp = decimal2;

    while (!s21_decimal_binary_equal_zero(tmp)) {
        s21_decimal overflow_bits = s21_decimal_binary_and(result, tmp);
        overflow_bits = s21_decimal_binary_shift_left(overflow_bits, 1);
        result = s21_decimal_binary_xor(result, tmp);
        tmp = overflow_bits;
    }

    return result;
}
