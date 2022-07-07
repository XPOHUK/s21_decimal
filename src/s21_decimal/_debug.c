#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../s21_decimal.h"
#include "./_debug.h"

void s21_print_decimal_bits(s21_decimal decimal) {
    s21_print_bit(decimal.bits[3], 1);
    s21_print_bit(decimal.bits[2], 0);
    s21_print_bit(decimal.bits[1], 0);
    s21_print_bit(decimal.bits[0], 0);
    putchar('\n');
}

void s21_print_bit(int number, int color) {
    s21_print_bits(sizeof(number), &number, color);
}

void s21_print_bits(size_t const size, void const * const ptr, int color) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    int cnt = 31;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            if (color == 1) {
                if (cnt == 31) {
                    printf("%s", GREEN);
                }
                if (cnt == 30 || cnt == 15) {
                    printf("%s", YELLOW);
                }
            }

            byte = (b[i] >> j) & 1;
            if (byte == 1) {
                if (color == 1 && cnt == 31) {
                    printf("%u", byte);
                } else {
                    printf("%s%u%s", RED, byte, RESET);
                }
            } else {
                printf("%u", byte);
            }
            if (color == 1) {
                if (cnt == 0 || cnt == 24 || cnt == 31) {
                    printf("%s", RESET);
                }
            }

            cnt--;
        }
        putchar(' ');
    }
    putchar('|');
    putchar(' ');
}

void s21_print_decimal_string(s21_decimal decimal) {
    char res[1024];
    memset(res, '\0', 1024);

    s21_decimal_to_string(decimal, res);

    if (res[0] == '(') {
        printf("%s%s%s\n", RED, res, RESET);
    } else {
        printf("%s\n", res);
    }
}

void s21_decimal_to_string(s21_decimal decimal, char *res) {
    res[0] = '\0';
    if (s21_is_correct_decimal(decimal) == 0) {
        strcat(res, "(Incorrect Decimal)");
    } else {
        format_decimal_to_str(decimal, res);
    }
}

void format_decimal_to_str(s21_decimal decimal, char *res) {
    char str[1024];
    memset(str, '\0', 1024);

    union {
        int bits[4];
        unsigned __int128 dec;
    } ex;

    ex.bits[0] = decimal.bits[0];
    ex.bits[1] = decimal.bits[1];
    ex.bits[2] = decimal.bits[2];
    ex.bits[3] = 0;

    int128_to_str(ex.dec, str);

    int power = s21_decimal_get_power(decimal);
    int sign = s21_decimal_get_sign(decimal);

    char *ptr = res;
    if (sign == 1 && ex.dec != 0) {
        *(ptr++) = '-';
    }

    if (strlen(str) <= (size_t) power) {
        *(ptr++) = '0';
        *(ptr++) = '.';

        for (size_t i = 0; i < power - strlen(str); i++) {
            *(ptr++) = '0';
        }
        for (int i = 0; i < power; i++) {
            *(ptr++) = str[i];
        }
    } else {
        size_t i;
        for (i = 0; i < strlen(str) - power; i++) {
            *(ptr++) = str[i];
        }

        for (int j = 0; j < power; j++) {
            if (j == 0) {
                *(ptr++) = '.';
            }
            *(ptr++) = str[i+j];
        }
    }
    *(ptr++) = '\0';
}

void int128_to_str(unsigned __int128 x, char *res) {
    char *ptr = res;

    if (x == 0) {
        *ptr = '0';
        ++ptr;
    } else {
        while (x != 0) {
            *ptr = x % 10 + '0';
            x = x / 10;
            ++ptr;
        }
    }

    *ptr = '\0';
    s21_reverse_string(res);
}

void s21_reverse_string(char *str) {
    size_t length;

    length = strlen(str);
    if (length > 0) {
        for (size_t i = length - 1, j = 0; i > (length - 1) / 2; i--, j++) {
            char c;
            c = str[i];
            str[i] = str[j];
            str[j] = c;
        }
    }
}
