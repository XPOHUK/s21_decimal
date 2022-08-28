#include "./binary.h"
#include "./../helpers/helpers.h"
#include "./../comparison/comparison.h"

#include <stdlib.h>

/**
 * @brief Функция бинарного деления двоичных чисел. 
 * 
 * Функция берет двоичное представление всех 128 бит числа decimal1 и делит на двоичное представление
 * всех 128 бит числа decimal2 (скорее всего 127 бит только работает верно - см. описание проблемы ниже)
 * 
 * Деление двоичных чисел реализуется методом без восстановления остатка.
 * 
 * Валидация входных данных не осуществляется, как и во всех бинарных функциях. Проверка деления на ноль
 * должна осуществляться перед вызовом функции.
 * 
 * A:   1 0 1 0 0 1 1 1
 * B: / 0 0 0 0 1 1 0 1
 *      ---------------
 * C: = 0 0 0 0 1 1 0 0
 * и 1 0 1 1 в остатке
 * 
 * Так как для выполнения деления требуется производить операцию вычитания, это требует использования 
 * знаковой арифметики. И поэтому в примере ниже 8-й разряд является знаковым (0 - соответствует
 * положительному числу, 1 - отрицательному), а старшим разрядом числа является 7-й разряд.
 * Эти знаковые разряды будут показывать нам знаки, образующихся в процессе деления, частичных остатков.
 * Они не имеет никакого отношения к знакам исходных операндов и знаку результата, а играют чисто
 * технологическую роль.
 * Знак результата необходимо будет определить отдельно, путем анализа знаков исходных операндов.
 * 
 * Т.к. у нас старшие 32 бита носят технический характер и фактически мы делим 96 бит, то у нас проблем
 * никаких не возникнет. Поэтому не тестировал сильно на таких огромных числах, но по идее 127 бит должны
 * делиться корректно, а вот если заполнить 128й бит - могут быть ошибки, т.к. для деления нужно 
 * будет уже 129 бит)
 * 
 * Алгоритм:
 * 1) Предварительный сдвиг делителя. Сдвинем делитель B влево так, чтобы позиция старшей значащей единицы,
 * в нем, совпала с позицией старшей значащей единицы в делимом A. Количество необходимых для этого сдвигов
 * запомним в числе k. В нашем случае старшая значащая единица в делимом A расположена в 7-м разряде,
 * a в делителе B - в 3-м разряде. Следовательно, нам необходимо сдвинуть число B влево на 4 разряда (k = 4).
 * Сдвинутый делитель выглядит следующим образом:
 * B: 0 1 1 0 1 0 0 0 0
 * 
 * 2) Вычитаем из делимого А сдвинутый делитель В.
 * Для понимания проще прибавлять B в дополнительном коде (см. описание
 * функции s21_decimal_binary_subtraction())
 * B в дополнительном коде:
 * B: 1 0 0 1 1 0 0 0 0
 * 
 * 3) Анализируем знак полученного частичного остатка (старший разряд). В регистр результата записываем 0,
 * если остаток отрицательный (старший бит == 1) и единицу в противном случае.
 * 4) Сдвигаем частичный остаток на один разряд влево. При этом знаковый разряд (старший) в процессе
 * сдвига не участвует.
 * 5) Прибавляем к частичному остатку делитель В если остаток отрицательный, либо вычитаем
 * делитель в противном случае.
 * 6) Анализируем знак полученного частичного остатка (старший разряд). В регистр результата
 * записываем "0", если остаток отрицательный, или единицу, если остаток положительный.
 * 7) Действия описанные в пунктах 4-6 выполняем k раз (если k=0, то ни разу не выполняем).
 * 
 * В нашем примере процесс деления выглядит следующим образом:
 *  A: 0 1 0 1 0 0 1 1 1    Частное:
 * -B: 1 0 0 1 1 0 0 0 0
 *     -----------------
 *  =: 1 1 1 0 1 0 1 1 1    Пишем 0 в младший бит: 0 0 0 0 0 0 0 0 (перед записью сдвигаем влево)
 * <<: 1 1 0 1 0 1 1 1 0
 * +B: 0 1 1 0 1 0 0 0 0
 *     -----------------
 *  =: 0 0 1 1 1 1 1 1 0    Пишем 1 в младший бит: 0 0 0 0 0 0 0 1 (перед записью сдвигаем влево)
 * <<: 0 1 1 1 1 1 1 0 0
 * -B: 1 0 0 1 1 0 0 0 0
 *     -----------------
 *  =: 0 0 0 1 0 1 1 0 0    Пишем 1 в младший бит: 0 0 0 0 0 0 1 1 (перед записью сдвигаем влево)
 * <<: 0 0 1 0 1 1 0 0 0
 * -B: 1 0 0 1 1 0 0 0 0
 *     -----------------
 *  =: 1 1 0 0 0 1 0 0 0    Пишем 0 в младший бит: 0 0 0 0 0 1 1 0 (перед записью сдвигаем влево)
 * <<: 1 0 0 0 1 0 0 0 0
 * +B: 0 1 1 0 1 0 0 0 0
 *     -----------------
 *  =: 1 1 1 1 0 0 0 0 0    Пишем 0 в младший бит: 0 0 0 0 1 1 0 0 (перед записью сдвигаем влево)
 * 
 * 8) Определяем остаток от деления. Для этого анализируем последний частичный остаток. В нашем случае
 * он равен 1 1 1 1 0 0 0 0 0. Анализируем старший бит. В знаковом разряде содержится единица, значит
 * требуется коррекция остатка (в противном случае оставляем как есть). Для коррекции прибавим к нему
 * делитель B:
 *     1 1 1 1 0 0 0 0 0 
 * +B: 0 1 1 0 1 0 0 0 0
 *     -----------------
 *  =: 0 1 0 1 1 0 0 0 0
 * 9) Так как в процессе деления частичные остатки были сдвинуты 4 раза влево, то для получения верного
 * значения последний полученный остаток необходимо сдвинуть 4 раза вправо (вернуть на место).
 * После сдвига имеем:
 * 0 0 0 0 0 1 0 1 1
 * 
 * Итого, частное 1 1 0 0, остаток 1 0 1 1
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal1 Делимое
 * @param decimal2 Делитель
 * @param remainder Остаток. Если нам не требуется получать остаток, то можно передать NULL
 * @return s21_decimal Частное чисел decimal1 и decimal2
 */
s21_decimal s21_decimal_binary_division(s21_decimal decimal1, s21_decimal decimal2, s21_decimal *remainder) {
    // TODO(hubdertfuu): п.4 алгоритма реализован не совсем так, знаковый разряд мы тоже двигаем.
    // Встретил упоминание такого нюанса только в одном месте, не уверен в этом
    // Работает и без этого во всех тестах (возможно из-за того, что у нас знаковый разряд 127, а
    // мы старшие 32 бита по сути не используем)

    // Результат работы функции
    s21_decimal result;  // = s21_decimal_get_zero();

    // Рассчитываемый в алгоритме частичный остаток при расчетах
    s21_decimal partial_remainder = s21_decimal_get_zero();
    // Рассчитываемое в алгоритме частное
    s21_decimal quotient = s21_decimal_get_zero();

    if (s21_decimal_binary_equal_zero(decimal1)) {
        // Сначала заполняем результаты для частного случая, когда делимое равно 0
        quotient = s21_decimal_get_zero();
        partial_remainder = s21_decimal_get_zero();
    } else if (s21_decimal_binary_compare(decimal1, decimal2) == -1) {
        // Затем заполняем результаты для частного случая, когда делимое меньше делителя
        quotient = s21_decimal_get_zero();
        partial_remainder = decimal1;
    } else {
        // В остальных случаях используем деление двоичных чисел методом без восстановления остатка.

        // Рассчитываем предварительный сдвиг делителя
        int left1 = s21_decimal_get_not_zero_bit(decimal1);
        int left2 = s21_decimal_get_not_zero_bit(decimal2);
        int shift = left1 - left2;

        // Сдвинутый делитель
        s21_decimal shifted_divisor = s21_decimal_binary_shift_left(decimal2, shift);
        // Делимое для промежуточных расчетов, на первом этапе равно decimal1
        s21_decimal dividend = decimal1;

        // Флаг необходимости проводить вычитание (Шаг 5 алгоритма).
        // На первой итерации всегда требуется вычитать
        int need_subtraction = 1;

        // Повторяем действия k+1 раз (один раз пп.2-3 алгоритма и k раз пп.4-6)
        while (shift >= 0) {
            // Определяем необходимое действие (Прибавлять или вычитать Сдвинутый делитель)
            if (need_subtraction == 1) {
                partial_remainder = s21_decimal_binary_subtraction(dividend, shifted_divisor);
            } else {
                partial_remainder = s21_decimal_binary_addition(dividend, shifted_divisor);
            }

            // Сдвигаем влево на 1 частное и записываем в младший бит 1,
            // если старший бит частичного остатка равен 1
            quotient = s21_decimal_binary_shift_left(quotient, 1);
            if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1) == 0) {
                quotient = s21_decimal_set_bit(quotient, 0);
            }

            // Рассчитываем делимое для следующей итерации цикла (сдвиг влево на 1 частичного остатка)
            dividend = s21_decimal_binary_shift_left(partial_remainder, 1);

            // Если старший бит частичного остатка равен 0, то на следующей итерации
            // необходимо проводить вычитание (Шаг 5 алгоритма)
            if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1) == 0) {
                need_subtraction = 1;
            } else {
                need_subtraction = 0;
            }
            --shift;
        }
        // Определяем, требуется ли коррекция остатка (п.8 алгоритма)
        if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1)) {
            partial_remainder = s21_decimal_binary_addition(partial_remainder, shifted_divisor);
        }
        // Возвращаем на место частичный остаток (п.9 алгоритма)
        partial_remainder = s21_decimal_binary_shift_right(partial_remainder, left1 - left2);
    }

    // Заполняем переменные результата (частное и остаток)
    result = quotient;
    if (remainder != NULL) {
        *remainder = partial_remainder;
    }

    return result;
}
