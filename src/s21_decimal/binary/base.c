
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
