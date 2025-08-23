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

    // ------------ TEST 1 -------------
    // (-5) -> 0
    {
    if (!((ans = is_zero(-5)) == 0)) {
        fprintf(stderr, "TEST 1 FAILED:\n"
               "is_zero(-5) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 2 -------------
    // (-1) -> 0
    {
    if (!((ans = is_zero(-1)) == 0)) {
        fprintf(stderr, "TEST 2 FAILED:\n"
               "is_zero(-1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 3 -------------
    // (1) -> 0
    {
    if (!((ans = is_zero(1)) == 0)) {
        fprintf(stderr, "TEST 3 FAILED:\n"
               "is_zero(1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 4 -------------
    // (10) -> 0
    {
    if (!((ans = is_zero(10)) == 0)) {
        fprintf(stderr, "TEST 4 FAILED:\n"
               "is_zero(10) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 5 -------------
    // (0.1) -> 0
    {
    if (!((ans = is_zero(0.1)) == 0)) {
        fprintf(stderr, "TEST 5 FAILED:\n"
               "is_zero(0.1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 6 -------------
    // (-0.1) -> 0
    {
    if (!((ans = is_zero(-0.1)) == 0)) {
        fprintf(stderr, "TEST 6 FAILED:\n"
               "is_zero(-0.1) -> ans = %d\n"
               "(should be 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 7 -------------
    // (0) -> 1
    {
    if (!((ans = is_zero(0)) == 1)) {
        fprintf(stderr, "TEST 7 FAILED:\n"
               "is_zero(0) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 8 -------------
    // (-0) -> 1
    {
    if (!((ans = is_zero(-0)) == 1)) {
        fprintf(stderr, "TEST 8 FAILED:\n"
               "is_zero(-0) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 9 -------------
    // (1E-15) -> 1
    {
    if (!((ans = is_zero(1E-15)) == 1)) {
        fprintf(stderr, "TEST 9 FAILED:\n"
               "is_zero(1E-15) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 10 -------------
    // (-1E-16) -> 1
    {
    if (!((ans = is_zero(-1E-16)) == 1)) {
        fprintf(stderr, "TEST 10 FAILED:\n"
               "is_zero(-1E-16) -> ans = %d\n"
               "(should be 1)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

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

    // ------------ TEST 1 -------------
    // (1, 2) < 0
    {
    if (!((ans = compare_double(1, 2)) < 0)) {
        fprintf(stderr, "TEST 1 FAILED:\n"
               "compare_double(1, 2) -> ans = %d\n"
               "(should be < 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 2 -------------
    // (0, 5) < 0
    {
    if (!((ans = compare_double(0, 5)) < 0)) {
        fprintf(stderr, "TEST FAILED:\n"
               "compare_double(0, 5) -> ans = %d\n"
               "(should be < 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 3 -------------
    // (2, 1) > 0
    {
    if (!((ans = compare_double(2, 1)) > 0)) {
        fprintf(stderr, "TEST 3 FAILED:\n"
               "compare_double(2, 1) -> ans = %d\n"
               "(should be > 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 4 -------------
    // (10, 0) > 0
    {
    if (!((ans = compare_double(10, 0)) > 0)) {
        fprintf(stderr, "TEST 4 FAILED:\n"
               "compare_double(10, 0) -> ans = %d\n"
               "(should be > 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 5 -------------
    // (10, 10) == 0
    {
    if (!((ans = compare_double(10, 10)) == 0)) {
        fprintf(stderr, "TEST 5 FAILED:\n"
               "compare_double(10, 10) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 6 -------------
    // (10, 10) == 0
    {
    if (!((ans = compare_double(0, 0)) == 0)) {
        fprintf(stderr, "TEST 6 FAILED:\n"
               "compare_double(0, 0) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 7 -------------
    // (0, 1E-16) == 0
    {
    if (!((ans = compare_double(0, 1E-16)) == 0)) {
        fprintf(stderr, "TEST 7 FAILED:\n"
               "compare_double(0, 1E-16) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 7 -------------
    // (-15, -15.00000000001) == 0
    {
    if (!((ans = compare_double(-15, -15.00000000001)) == 0)) {
        fprintf(stderr, "TEST FAILED:\n"
               "compare_double(-15, -15.00000000001) -> ans = %d\n"
               "(should be == 0)",
               ans);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

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

    // ------------ TEST 1 -------------
    // (1)  -> -1, 1
    {
    x = 1;
    if (!(
        ((ans = minus_zero_fix(&x)) == -1) && (compare_double(x, 1) == 0)
        )) {
        fprintf(stderr, "TEST 1 FAILED:\n"
               "minus_zero_fix(1) -> ans = %d\n, x = %lf"
               "(should be -1, 1)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 2 -------------
    // (-1)  -> -1, -1
    {
    x = -1;
    if (!(
        ((ans = minus_zero_fix(&x)) == -1) && (compare_double(x, -1) == 0)
        )) {
        fprintf(stderr, "TEST 2 FAILED:\n"
               "minus_zero_fix(-1) -> ans = %d\n, x = %lf"
               "(should be -1, -1)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 3 -------------
    // (0)  -> 1, 0
    {
    x = 0;
    if (!(
        ((ans = minus_zero_fix(&x)) == 1) && (is_zero(x))
        )) {
        fprintf(stderr, "TEST 3 FAILED:\n"
               "minus_zero_fix(0) -> ans = %d\n, x = %lf"
               "(should be 1, 0)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 4 -------------
    // (-0)  -> 1, 0
    {
    x = 0;
    x = -x;
    if (!(
        ((ans = minus_zero_fix(&x)) == 1) && (is_zero(x))
        )) {
        fprintf(stderr, "TEST 4 FAILED:\n"
               "minus_zero_fix(-0) -> ans = %d\n, x = %lf"
               "(should be 1, 0)",
               ans, x);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    return is_passed;
}
