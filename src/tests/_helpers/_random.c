#include <stdlib.h>
/**
 * @brief генерирует случайное число double в диапазоне [min, max]
 * Распределение у ряда не очень, но для наших целей хватит
 * 
 * например, 
 * для диапазона 0 - DBL_MAX при генерации 100млн чисел они все лежат в диапазоне [1.88267e+302, 1.79769e+308]
 * для диапазона 0 - 10.0 уже лучше - [2.32831e-08, 10]
 * [1e16, 1e24] - [1.74506e+16, 1e+24]
 * [0.0, 1e8] - [1.21072, 1e+08]
 * В общем, разница между min и max должна быть <=1e8
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param min минимальное генерируемое число
 * @param max максимальное генерируемое число
 * @return double случайное число
 */
double s21_random_double(double min, double max) {
    return min + (double) (rand()) / ((double) RAND_MAX / (max - min));
}

/**
 * @brief генерирует случайное положительное число int в диапазоне [min, max]
 * если min < 0, то min будет считаться 0
 * если max < 0, то max будет считаться -max
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param min минимальное генерируемое число
 * @param max максимальное генерируемое число
 * @return int случайное число
 */
int s21_random_int(int min, int max) {
    if (min < 0) {
        min = 0;
    }

    if (max < 0) {
        max = -max;
    }

    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
