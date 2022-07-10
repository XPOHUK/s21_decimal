#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_conversion_result result = S21_CONVERSION_OK;
    if (!dst) {
        result = S21_CONVERSION_ERROR;
    } else {
        s21_clear_decimal(dst);
        float_cast cast;
        cast.f = src;
        // cast.parts.sign = 0;
        // cast.parts.exponent = 124;
        // cast.parts.mantisa = 2097152;

        s21_print_bit(cast.parts.sign, 0); putchar('\n');
        s21_print_bit(cast.parts.exponent, 0); putchar('\n');
        s21_print_bit(cast.parts.mantisa, 0); putchar('\n');putchar('\n');
        
        s21_print_bit(cast.bytes, 0); putchar('\n');putchar('\n');

        uint32_t nnnn = cast.parts.mantisa;
        unsigned char *b = (unsigned char*) &nnnn;
        unsigned char byte;
        size_t size = sizeof(uint32_t);
        int cnt = 0;
        char str[1024] = {0};
        for (int i = size - 1; i >= 0; i--) {
            for (int j = 7; j >= 0; j--) {
                if ((size_t)i == size - 1 || ((size_t) i == size - 2 && j == 7))
                    continue;

                byte = (b[i] >> j) & 1;
                
                if (byte == 1) {
                    str[cnt] = '1';
                } else {
                    str[cnt] = '0';                    
                }
                cnt++;
            }
            // putchar(' ');
        }
        str[cnt] = '\0';   
        float f = 0.0;
        int step = cast.parts.exponent - 127;
        f += 1 * pow(2, step);

        printf("f = decimal.Add(f, s21_ipow(two, %d));\n", step);
        for (int i = 0; i < (int) strlen(str); i++) {
            if (str[i] == '1') {
                f += pow(2, -i-1 + step);
                printf("f = decimal.Add(f, s21_ipow(two, %d));\n", -i-1 + step);
            }
        }
        
        printf("%s\n", str);
        printf("[%.80f]\n", f);

        s21_print_decimal_bits(*dst);
        s21_print_decimal_string(*dst);
        printf("%.50f\n", src);
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }

    return result;
}
