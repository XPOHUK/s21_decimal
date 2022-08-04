#include "../../s21_decimal.h"
#include "./_debug.h"

int test_decimal_get_sign(s21_decimal value) {
    union {
        struct s21_decimal d;
        struct {
            uint32_t part0;
            uint32_t part1;
            uint32_t part2;
            uint32_t empty2 : 16;
            uint32_t power : 8;
            uint32_t empty1 : 7;
            uint32_t sign : 1;
        } parts;
    } decimal_bytes;

    decimal_bytes.d = value;

    return decimal_bytes.parts.sign;
}
