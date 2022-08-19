#include <stdio.h>
#include <stdlib.h>

#include "./test.h"
#include "./../s21_decimal.h"

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(NULL);


    
    srunner_add_suite(sr, from_int_to_decimal_suite());

    // srunner_add_suite(sr, from_float_to_decimal_suite0());
    // srunner_add_suite(sr, from_float_to_decimal_suite1());
    // srunner_add_suite(sr, from_float_to_decimal_suite2());
    // srunner_add_suite(sr, from_float_to_decimal_suite3());
    // srunner_add_suite(sr, from_float_to_decimal_suite4());
    // srunner_add_suite(sr, from_float_to_decimal_suite5());
    // srunner_add_suite(sr, from_float_to_decimal_suite6());
    // srunner_add_suite(sr, from_float_to_decimal_suite7());

    srunner_add_suite(sr, from_decimal_to_int_suite0());
    srunner_add_suite(sr, from_decimal_to_int_suite1());
    srunner_add_suite(sr, from_decimal_to_int_suite2());
    srunner_add_suite(sr, from_decimal_to_int_suite3());

    srunner_add_suite(sr, from_decimal_to_float_suite1());
    srunner_add_suite(sr, from_decimal_to_float_suite2());
    srunner_add_suite(sr, from_decimal_to_float_suite3());
    srunner_add_suite(sr, from_decimal_to_float_suite4());
    srunner_add_suite(sr, from_decimal_to_float_suite5());
    srunner_add_suite(sr, from_decimal_to_float_suite6());
    srunner_add_suite(sr, from_decimal_to_float_suite7());
    srunner_add_suite(sr, from_decimal_to_float_suite8());
    srunner_add_suite(sr, from_decimal_to_float_suite0());

    srunner_add_suite(sr, is_greater_suite());
    srunner_add_suite(sr, is_less_suite());
    srunner_add_suite(sr, is_equal_suite());

    srunner_add_suite(sr, truncate_suite0());
    srunner_add_suite(sr, truncate_suite1());
    srunner_add_suite(sr, truncate_suite2());
    srunner_add_suite(sr, truncate_suite3());

    srunner_add_suite(sr, negate_suite());

    srunner_add_suite(sr, binary_division_suite1());
    srunner_add_suite(sr, binary_division_suite2());
    srunner_add_suite(sr, binary_division_suite3());
    srunner_add_suite(sr, binary_division_suite4());
    srunner_add_suite(sr, binary_division_suite5());
    srunner_add_suite(sr, binary_division_suite6());

    // srunner_add_suite(sr, division_suite1());
    // srunner_add_suite(sr, addition_suite1());

    srunner_add_suite(sr, add_suite0());
    srunner_add_suite(sr, add_suite1());
    // srunner_add_suite(sr, add_suite2());
    // srunner_add_suite(sr, add_suite3());
    // srunner_add_suite(sr, add_suite4());
    // srunner_add_suite(sr, add_suite5());
    // srunner_add_suite(sr, add_suite6());
    // srunner_add_suite(sr, add_suite7());
    // srunner_add_suite(sr, add_suite8());
    // srunner_add_suite(sr, add_suite9());

    // srunner_add_suite(sr, div_suite0());
    // srunner_add_suite(sr, div_suite1());
    // srunner_add_suite(sr, div_suite2());
    // srunner_add_suite(sr, div_suite3());
    // srunner_add_suite(sr, div_suite4());
    // srunner_add_suite(sr, div_suite5());
    // srunner_add_suite(sr, div_suite6());
    // srunner_add_suite(sr, div_suite7());
    // srunner_add_suite(sr, div_suite8());
    // srunner_add_suite(sr, div_suite9());
    // srunner_add_suite(sr, div_suite10());
    // srunner_add_suite(sr, div_suite11());
    // srunner_add_suite(sr, div_suite12());
    // srunner_add_suite(sr, div_suite13());
    // srunner_add_suite(sr, div_suite14());
    // srunner_add_suite(sr, div_suite15());
    // srunner_add_suite(sr, div_suite16());
    // srunner_add_suite(sr, div_suite17());
    // srunner_add_suite(sr, div_suite18());

    srunner_add_suite(sr, debug0());
    srunner_add_suite(sr, debug1());
    srunner_add_suite(sr, debug2());
    srunner_add_suite(sr, debug3());

    // TODO(rambo): расскоментировать nofork-режим для проверки valgrind/leaks
    // srunner_set_fork_status(sr, CK_NOFORK);
    // Используем данный блок для вывода подробно про каждый тест с разбиением по блокам
    // srunner_set_log(sr, "-");
    // srunner_run_all(sr, CK_SILENT);  // CK_SILENT || CK_MINIMAL || CK_NORMAL || CK_VERBOSE
    // Либо данный блок вместо предыдущего для вывода только ошибок и общего результата
    srunner_run_all(sr, CK_NORMAL);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
