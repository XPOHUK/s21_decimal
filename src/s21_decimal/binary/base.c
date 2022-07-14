#include "./../types.h"

/**
 * @brief 
 * 
 * @author Rambton Neo (rambtono@student.21-school.ru)
 * @param number 
 * @param index 
 * @return int 
 */
int s21_is_set_bit(int number, int index) {
    return (number & (1 << index));
}

/**
 * @brief 
 * 
 * @author Rambton Neo (rambtono@student.21-school.ru)
 * @param number 
 * @param index 
 * @return int 
 */
int s21_set_bit(int number, int index) {
    return number | (1 << index);
}

/**
 * @brief 
 * 
 * @author Rambton Neo (rambtono@student.21-school.ru)
 * @param number 
 * @param index 
 * @return int 
 */
int s21_inverse_bit(int number, int index) {
    return number ^(1 << index);
}

/**
 * @brief 
 * 
 * @author Rambton Neo (rambtono@student.21-school.ru)
 * @param number 
 * @param index 
 * @return int 
 */
int s21_reset_bit(int number, int index) {
    return number &~(1 << index);
}

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
    return s21_is_set_bit(decimal.bits[index / MAX_BLOCK_BITS], index % MAX_BLOCK_BITS);
}

s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index) {
    decimal.bits[index / MAX_BLOCK_BITS] =
     s21_set_bit(decimal.bits[index / MAX_BLOCK_BITS], index % MAX_BLOCK_BITS);
    return decimal;
}

int s21_decimal_get_not_zero_bit(s21_decimal decimal) {
    int result = -1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        if (s21_decimal_is_set_bit(decimal, i)) {
            result = i;
            break;
        }
    }

    return result;
}
