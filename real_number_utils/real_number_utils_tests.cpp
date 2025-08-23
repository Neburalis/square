#include <stdio.h>

#include "real_number_utils.h"

int TEST_is_zero(int * const count_tests) {
    /*
    (-5) -> 0
    (-1) -> 0
    (1) -> 0
    (10) -> 0
    (0.1) -> 0
    (-0.1) -> 0
    (0) -> 1
    (-0) -> 1
    (1E-15) ->1
    (-1E-16) -> 1
    */

    int is_passed = 0;
    int ans = 0;
    if (!((ans = is_zero(-5)) == 0)) {
        printf("TEST FAILED:\n"
               "is_zero(-5) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(-1)) == 0)) {
        printf("TEST FAILED:\n"
               "is_zero(-1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(1)) == 0)) {
        printf("TEST FAILED:\n"
               "is_zero(1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(10)) == 0)) {
        printf("TEST FAILED:\n"
               "is_zero(10) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(0.1)) == 0)) {
        printf("TEST FAILED:\n"
               "is_zero(0.1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(-0.1)) == 0)) {
        printf("TEST FAILED:\n"
               "is_zero(-0.1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(0)) == 1)) {
        printf("TEST FAILED:\n"
               "is_zero(0) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(-0)) == 1)) {
        printf("TEST FAILED:\n"
               "is_zero(-0) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(1E-15)) == 1)) {
        printf("TEST FAILED:\n"
               "is_zero(1E-15) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = is_zero(-1E-16)) == 1)) {
        printf("TEST FAILED:\n"
               "is_zero(-1E-16) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    return is_passed;
}

int TEST_compare_double(int * const count_tests) {
    /*
    (1, 2) < 0
    (0, 5) < 0
    (2, 1) > 0
    (10, 0) > 0
    (10, 10) == 0
    (0, 0) == 0
    (0, 1E-16) == 0
    (-15, -15.00000000001) == 0
    */

    int is_passed = 0;
    int ans = 0;

    if (!((ans = compare_double(1, 2)) < 0)) {
        printf("TEST FAILED:\n"
               "compare_double(1, 2) -> ans = %d\n"
               "(should be < 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(0, 5)) < 0)) {
        printf("TEST FAILED:\n"
               "compare_double(0, 5) -> ans = %d\n"
               "(should be < 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(2, 1)) > 0)) {
        printf("TEST FAILED:\n"
               "compare_double(2, 1) -> ans = %d\n"
               "(should be > 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(10, 0)) > 0)) {
        printf("TEST FAILED:\n"
               "compare_double(10, 0) -> ans = %d\n"
               "(should be > 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(10, 10)) == 0)) {
        printf("TEST FAILED:\n"
               "compare_double(10, 10) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(0, 0)) == 0)) {
        printf("TEST FAILED:\n"
               "compare_double(0, 0) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(0, 1E-16)) == 0)) {
        printf("TEST FAILED:\n"
               "compare_double(0, 1E-16) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    if (!((ans = compare_double(-15, -15.00000000001)) == 0)) {
        printf("TEST FAILED:\n"
               "compare_double(-15, -15.00000000001) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;

    return is_passed;
}

int TEST_minus_zero_fix(int * const count_tests) {
    /*
    (1)  -> -1, 1
    (-1) -> -1, -1
    (0)  -> 1, 0
    (-0) -> 1, 0
    */

    int is_passed = 0;
    double x = 0;
    int ans = 0;

    x = 1;
    if (!(
        ((ans = minus_zero_fix(&x)) == -1) && (compare_double(x, 1) == 0)
        )) {
        printf("TEST FAILED:\n"
               "minus_zero_fix(1) -> ans = %d\n, x = %lf"
               "(should be -1, 1)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = -1;
    if (!(
        ((ans = minus_zero_fix(&x)) == -1) && (compare_double(x, -1) == 0)
        )) {
        printf("TEST FAILED:\n"
               "minus_zero_fix(-1) -> ans = %d\n, x = %lf"
               "(should be -1, -1)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = 0;
    if (!(
        ((ans = minus_zero_fix(&x)) == 1) && (is_zero(x))
        )) {
        printf("TEST FAILED:\n"
               "minus_zero_fix(0) -> ans = %d\n, x = %lf"
               "(should be 1, 0)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = 0;
    x = -x;
    if (!(
        ((ans = minus_zero_fix(&x)) == 1) && (is_zero(x))
        )) {
        printf("TEST FAILED:\n"
               "minus_zero_fix(-0) -> ans = %d\n, x = %lf"
               "(should be 1, 0)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    return is_passed;
}
