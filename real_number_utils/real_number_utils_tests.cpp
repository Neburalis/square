#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "real_number_utils.h"
#include "io_utils.h"

struct TEST_DATA_is_zero {
    uint32_t test_n;
    double input;
    int reference_output;
};
static int ONE_TEST_is_zero(const TEST_DATA_is_zero * const test_data) {
    int is_failed = 0;
    int ans = 0;

    if (!((ans = is_zero(test_data->input)) == test_data->reference_output)) {
        fprintf(stderr, RED("TEST %u FAILED:\n")
               "is_zero(%lf) -> ans = %d\n"
               "(should be %d)\n\n",
               test_data->test_n, test_data->input, ans, test_data->reference_output);
        is_failed = 1;
    }

    return is_failed;
}
int TEST_is_zero(FILE* fp, uint32_t * const count_tests) {
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
    if (!fp){
        errno = EBADF;
        return -1;
    }
    size_t line_num = lines_in_file(fp);
    int is_failed = 0;

    struct TEST_DATA_is_zero * tests =
        (TEST_DATA_is_zero *) calloc(line_num, sizeof(TEST_DATA_is_zero));
    if (tests == NULL){
        errno = ENOMEM;
        return -1;
    }

    size_t num_of_tests = 0;

    if (fp) {
        for(;;) {
            uint32_t num = 0;
            double var = 0;
            int ref_out = 0;
            if (fscanf(fp, "#%u (%lf) -> %d", &num, &var, &ref_out) == 3){

                tests[num_of_tests] = {
                    .test_n = num,
                    .input = var,
                    .reference_output = ref_out,
                };
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
    }

    for (size_t i = 0; i < num_of_tests; ++i) {
        int test_failed = ONE_TEST_is_zero(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |=test_failed;
    }
    free(tests);
    return is_failed;
}

struct TEST_DATA_compare_double {
    uint32_t test_n;
    double first, second;
    int reference_output;
};
static int ONE_TEST_compare_double(const TEST_DATA_compare_double * const test_data) {
    int is_failed = 0;
    int ans = 0;

    if (!((ans = compare_double(test_data->first, test_data->second)) == test_data->reference_output)) {
        fprintf(stderr, RED("TEST %u FAILED:\n")
               "compare_double(%lf, %lf) -> ans = %d\n"
               "(should be %d)\n\n",
               test_data->test_n, test_data->first, test_data->second, ans, test_data->reference_output);
        is_failed = 1;
    }

    return is_failed;
}
int TEST_compare_double(FILE* fp, uint32_t * const count_tests) {
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
    if (!fp){
        errno = EBADF;
        return -1;
    }
    size_t line_num = lines_in_file(fp);
    int is_failed = 0;

    struct TEST_DATA_compare_double * tests =
        (TEST_DATA_compare_double *) calloc(line_num, sizeof(TEST_DATA_compare_double));
    if (tests == NULL){
        errno = ENOMEM;
        return -1;
    }

    size_t num_of_tests = 0;

    if (fp) {
        for(;;) {
            uint32_t num = 0;
            double first, second = 0;
            int ref_out = 0;
            if (fscanf(fp, "#%u (%lf, %lf) -> %d", &num, &first, &second, &ref_out) == 4){

                tests[num_of_tests] = {
                    .test_n = num,
                    .first = first, .second = second,
                    .reference_output = ref_out,
                };
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
    }

    for (size_t i = 0; i < num_of_tests; ++i) {
        int test_failed = ONE_TEST_compare_double(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |=test_failed;
    }
    free(tests);
    return is_failed;
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
        fprintf(stderr, RED("TEST %u FAILED:\n")
               "minus_zero_fix(%lf) -> ans = %d\n, x = %lf"
               "(should be %d, %lf)",
               test_data->test_n, test_data->value, ans, var, test_data->reference_output, test_data->reference_value);
        is_failed = 1;
    }

    return is_failed;
}
int TEST_minus_zero_fix(FILE* fp, uint32_t * const count_tests) {
    /*
    #1 (1)  -> -1, 1
    #2 (-1) -> -1, -1
    #3 (0)  -> 1, 0
    #4 (-0) -> 1, 0
    */
    if (!fp){
        errno = EBADF;
        return -1;
    }
    size_t line_num = lines_in_file(fp);
    int is_failed = 0;

    struct TEST_DATA_minus_zero_fix * tests =
        (TEST_DATA_minus_zero_fix *) calloc(line_num, sizeof(TEST_DATA_minus_zero_fix));
    if (tests == NULL){
        errno = ENOMEM;
        return -1;
    }
    size_t num_of_tests = 0;

    if (fp) {
        for(;;) {
            uint32_t num = 0;
            double var = 0, ref_var;
            int ref_out = 0;
            if (fscanf(fp, "#%u (%lf) -> %d, %lf", &num, &var, &ref_out, &ref_var) == 4){

                tests[num_of_tests] = {
                    .test_n = num,
                    .value = var, .reference_value = ref_var,
                    .reference_output = ref_out,
                };
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
    }

    for (size_t i = 0; i < num_of_tests; ++i) {
        int test_failed = ONE_TEST_minus_zero_fix(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |=test_failed;
    }

    return is_failed;
}
