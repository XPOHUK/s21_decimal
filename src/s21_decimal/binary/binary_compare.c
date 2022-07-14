#include "./binary.h"

/**
 * @brief 
 * 
 * @param decimal1 
 * @param decima2 
 * @return int результат сравнения:
 *          -1 - Значение d1 меньше d2.
 *           0 - Значения d1 и d2 равны.
 *           1 - Значение d1 больше значения d2.
 */
int s21_decimal_binary_compare(s21_decimal d1, s21_decimal d2) {
    int result = 0;

    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int b1 = s21_decimal_is_set_bit(d1, i);
        int b2 = s21_decimal_is_set_bit(d2, i);

        if (b1 == 0 && b2 != 0) {
            result = -1;
            break;
        }

        if (b1 != 0 && b2 == 0) {
            result = 1;
            break;
        }
    }

    return result;
}
