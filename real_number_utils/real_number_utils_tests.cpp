#include <stdio.h>
#include <math.h>

#include "../macro.h"

#include "real_number_utils.h"

struct TEST_DATA_is_zero {
    uint32_t test_n;
    double input;
    int reference_output;
};
static int ONE_TEST_is_zero(const TEST_DATA_is_zero * const test_data) {
    int is_failed = 0;
    int ans = 0;

    if (!((ans = is_zero(test_data->input)) == test_data->reference_output)) {
        fprintf(stderr, RED("TEST %d FAILED:\n")
               "is_zero(%lf) -> ans = %lf\n"
               "(should be %lf)\n\n",
               test_data->test_n, test_data->input, ans, test_data->reference_output);
        is_failed = 1;
    }

    return is_failed;
}
int TEST_is_zero(int * const count_tests) {
    /*
    #1 (-5) -> 0
    #2 (-1) -> 0
    #3 (1) -> 0
    #4 (10) -> 0
    #5 (0.1) -> 0
    #6 (-0.1) -> 0
    #7 (0) -> 1
    #8 (-0) -> 1
    #9 (1E-15) ->1
    #10 (-1E-16) -> 1
    */

    int is_failed = 0;

    FILE *fp = fopen("test/is_zero_test_data.txt", "r");
    struct TEST_DATA_is_zero tests[1000];
    size_t num_of_tests = 0;

    uint32_t num = 0;
    if (fp) {
        for(int i = 0;;++i) {
            double var = 0;
            int ref_out = 0;
            if (fscanf(fp, "#%d (%lf) -> %d", &num, &var, &ref_out) == 3){

                tests[i] = {
                    .test_n = num,
                    .input = var,
                    .reference_output = ref_out,
                };
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
        fclose(fp);
    }

    for (size_t i = 0; i < num_of_tests; ++i) {
        int test_failed = ONE_TEST_is_zero(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |=test_failed;
    }

    return is_failed;
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

struct TEST_DATA_minus_zero_fix {
    uint32_t test_n;
    double value, reference_value;
    int reference_output;
};
static int ONE_TEST_minus_zero_fix(const TEST_DATA_minus_zero_fix * const test_data) {
    int is_failed = 0;
    int ans = 0;
    double var = test_data->value;
    if (!(
        ((ans = minus_zero_fix(&var)) == test_data->reference_output) && (compare_double(var, test_data->reference_value) == 0)
        )) {
        fprintf(stderr, "TEST %d FAILED:\n"
               "minus_zero_fix(#ld) -> ans = %d\n, x = %lf"
               "(should be %d, %lf)",
               test_data->test_n, test_data->value, ans, var, test_data->reference_output, test_data->reference_value);
        is_failed = 1;
    }

    return is_failed;
}
int TEST_minus_zero_fix(int * const count_tests) {
    /*
    #1 (1)  -> -1, 1
    #2 (-1) -> -1, -1
    #3 (0)  -> 1, 0
    #4 (-0) -> 1, 0
    */

    int is_failed = 0;

    FILE *fp = fopen("test/minus_zero_fix_test_data.txt", "r");
    struct TEST_DATA_minus_zero_fix tests[1000] = {};
    size_t num_of_tests = 0;

    uint32_t num = 0;
    if (fp) {
        for(int i = 0;;++i) {
            double var = 0, ref_var;
            int ref_out = 0;
            if (fscanf(fp, "#%d (%lf) -> %d, %lf", &num, &var, &ref_out, &ref_var) == 4){

                tests[i] = {
                    .test_n = num,
                    .value = var, .reference_value = ref_var,
                    .reference_output = ref_out,
                };
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
        fclose(fp);
    }

    for (size_t i = 0; i < num_of_tests; ++i) {
        int test_failed = ONE_TEST_minus_zero_fix(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |=test_failed;
    }

    return is_failed;
}
