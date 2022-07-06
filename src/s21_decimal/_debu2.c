#include <stdint.h>
#include <stdio.h>

#include "./_debug.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Функции ниже не используются, но пригодятся для общего понимания
И являются универсальными
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @brief Функция определяет, какой порядок байтов использует наш процессор
 * 
 * Статья "Порядок байтов" на вики: https://w.wiki/5QfP
 * 
 * От этого зависит то, каким образом печатать биты в функциях типа print_bit
 * В идеале, чтобы было универсально, необходимо сделать проверку little-endian / big-endian и сделать 
 * разные версии функций печати битов
 * Но у нас все версии под процессоры архитектуры x86 (little-endian), т.к. на другой архитектуре мы
 * не будем запускать нашу программу
 */
void what_endian() {
    uint16_t xx = 0x0001;
    printf("%s-endian\n", *((uint8_t *) &xx) ? "little" : "big");
}

/**
 * @brief Универсальная функция, печатающая биты переданного целочисленного числа любого типа
 * (для little-endian)
 * 
 * @param size 
 * @param ptr 
 */
void print_bits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        putchar(' ');
    }
    putchar('\n');
}

/**
 * @brief функции-обёртки над print_bits с разными типами аргументов
 * 
 * @param number 
 */
void print_bit_ui64(uint64_t number) {
    print_bits(sizeof(number), &number);
}

void print_bit_i64(int64_t number) {
    print_bits(sizeof(number), &number);
}

void print_bit_i32(int32_t number) {
    print_bits(sizeof(number), &number);
}

void print_bit_ui32(uint32_t number) {
    print_bits(sizeof(number), &number);
}
