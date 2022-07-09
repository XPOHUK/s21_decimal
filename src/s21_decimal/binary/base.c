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
int s21_inverseBit(int number, int index) {
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

/**
 * @brief устанавливает для decimal знак sign
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal меняемый decimal
 * @param sign устанавливаемый знак, 1 - отрицательный decimal, 0 - положительный decimal
 * любой sign, отличный от 0, установит знак 1
 */
void s21_set_sign(s21_decimal *decimal, int sign) {
    decimal_bit3 bits3;
    bits3.i = decimal->bits[3];
    if (sign == 0) {
        bits3.parts.sign = 0;
    } else {
        bits3.parts.sign = 1;
    }

    decimal->bits[3] = bits3.i;
}
