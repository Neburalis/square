#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "math_equation_solver.h"
#include "real_number_utils.h"
#include "io_utils.h"

// ----- Testing solve_square_equation func -----
struct TEST_DATA_solve_square_equation {
    uint32_t                ss_test_n;
    double                  ss_kf_a, ss_kf_b, ss_kf_c;
    enum solutions_count    ss_reference_nRoots;
    double                  ss_reference_ans1, ss_reference_ans2;
};
static int ONE_TEST_solve_square_equation(const TEST_DATA_solve_square_equation * const test_data) {
    assert(test_data != NULL && "You must pass test_data struct to func");

    if (test_data == NULL) {
        errno = EINVAL;
        return -1;
    }

    double x1 = NAN, x2 = NAN;
    int is_failed = 0;

    enum solutions_count n_roots =
        solve_square_equation(test_data->ss_kf_a,
                              test_data->ss_kf_b,
                              test_data->ss_kf_c,
                                &x1, &x2);

    if (n_roots == test_data->ss_reference_nRoots) {
        switch (test_data->ss_reference_nRoots){
            case INF:
                break;
            case NO:
                break;
            case ONE:
                if (!(compare_double(x1, test_data->ss_reference_ans1) == 0))
                    is_failed = 1;
                break;
            case TWO:
                if (!((compare_double(x1, test_data->ss_reference_ans1) == 0 && compare_double(x2, test_data->ss_reference_ans2) == 0) ||
                      (compare_double(x2, test_data->ss_reference_ans1) == 0 && compare_double(x1, test_data->ss_reference_ans2) == 0)))
                    is_failed = 1;
                break;
            case ERR:
            default:
                is_failed = 2;
                break;
        }
    }
    else {
        is_failed = 1;
    }

    if (is_failed)
        fprintf(stderr,
            RED("TEST %u FAILED:                         \n")   // test_n
            "solve_square_equation(%lg, %lg, %lg, ...) ->\n"    // kf_a, kf_b, kf_c
            "\t-> n_roots = %d, x1 = %lf, x2 = %lf       \n"    // n_r, x1, x2
            "(should be %d, %lf, %lf)                    \n\n", // ref n_r, ref x1, ref x2
            test_data->ss_test_n,
            test_data->ss_kf_a, test_data->ss_kf_b, test_data->ss_kf_c,
            n_roots, x1, x2,
            test_data->ss_reference_nRoots, test_data->ss_reference_ans1, test_data->ss_reference_ans1
        );
    return is_failed;
}
int TEST_solve_square_equation(FILE * const fp, uint32_t * const count_tests) {
    /*
    (1, -3, 2) -> TWO, 1, 2
    (1, 2, 0) -> TWO, 0, -2
    (1, 0, 0) -> ONE, 0
    (1, 2, 1) -> ONE, -1
    (1, 0, 2) -> NO
    */
    assert(fp != NULL           && "You must pass FILE to func");
    assert(count_tests != NULL  && "You must pass count_test value to func");

    if (!fp){
        errno = EBADF;
        return -1;
    }
    if (count_tests == NULL){
        errno = EBADF;
        return -1;
    }

    size_t line_num = lines_in_file(fp);
    int is_failed = 0;

    struct TEST_DATA_solve_square_equation *tests =
        (TEST_DATA_solve_square_equation *) calloc(line_num, sizeof(TEST_DATA_solve_square_equation));
    if (tests == NULL){
        errno = ENOMEM;
        return -1;
    }

    size_t test_count = 0;

    for(int i = 0; ; ++i) {
        uint32_t num = 0;
        double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
        int n_roots = 0;
        if (fscanf(fp, "#%u (%lf, %lf, %lf) -> %d, %lf, %lf", &num, &a, &b, &c, &n_roots, &x1, &x2) == 7){
            tests[i] = {
                .ss_test_n = num,
                .ss_kf_a = a, .ss_kf_b = b, .ss_kf_c = c,
                .ss_reference_nRoots = (solutions_count) n_roots,
                .ss_reference_ans1 = x1, .ss_reference_ans2 = x2,
            };
            ++test_count;
        }

        if (getc(fp) == EOF)
            break;
    }
    for (size_t i = 0; i < test_count; ++i) {
        int test_failed = ONE_TEST_solve_square_equation(&tests[i]);
        if (!test_failed)
            ++*count_tests;
        is_failed |= test_failed;
    }

    free(tests);
    return is_failed;
}

// ----- Testing solve_linear_equation func -----
struct TEST_DATA_solve_linear_equation { // TODO to the top of the file
    uint32_t                ss_test_n;
    double                  ss_kf_a, ss_kf_b;
    enum solutions_count    ss_reference_nRoots;
    double                  ss_reference_ans;
};
static int ONE_TEST_solve_linear_equation(const TEST_DATA_solve_linear_equation * const test_data) {
    assert(test_data != NULL && "You must pass test_data struct to func");

    if (test_data == NULL) {
        errno = EINVAL;
        return -1;
    }

    double x = NAN;
    int is_failed = 0;

    enum solutions_count n_roots =
        solve_linear_equation(test_data->ss_kf_a,
                              test_data->ss_kf_b, &x);

    if (n_roots == test_data->ss_reference_nRoots) {
        switch (test_data->ss_reference_nRoots){
            case INF:
                break;
            case NO:
                break;
            case ONE:
                if (!(compare_double(x, test_data->ss_reference_ans) == 0))
                    is_failed = 1;
                break;
            case TWO:
                is_failed = 1;
                break;
            case ERR:
            default:
                is_failed = 2;
                break;
        }
    }
    else {
        is_failed = 1;
    }

    if (is_failed)
        fprintf(stderr,
            RED("TEST %u FAILED:                        \n")    // test_n
            "solve_linear_equation(%lg, %lg, ...) ->    \n"     // kf_a, kf_b
            "\t-> n_roots = %d, x = %lf                 \n"     // n_r, x
            "(should be %d, %lf)                        \n\n",  // ref n_r, ref x
            test_data->ss_test_n,
            test_data->ss_kf_a, test_data->ss_kf_b,
            n_roots, x,
            test_data->ss_reference_nRoots, test_data->ss_reference_ans
        );
    return is_failed;
}
int TEST_solve_linear_equation(FILE * const fp, uint32_t * const count_tests) {
    /*
    (2, 0) -> ONE, 0
    (2, 5) -> ONE, -2.5
    (0, 2) -> NO
    (0, -5) -> NO
    (0, 0) -> INF
    */
    assert(fp != NULL           && "You must pass FILE to func");
    assert(count_tests != NULL  && "You must pass count_test value to func");

    if (!fp){
        errno = EBADF;
        return -1;
    }
    if (count_tests == NULL){
        errno = EBADF;
        return -1;
    }

    size_t line_num = lines_in_file(fp);
    int is_failed = 0;

    struct TEST_DATA_solve_linear_equation *tests =
        (TEST_DATA_solve_linear_equation *) calloc(line_num, sizeof(TEST_DATA_solve_linear_equation));
    if (tests == NULL) {
        errno = ENOMEM;
        return -1;
    }

    size_t num_of_tests = 0;

    uint32_t num = 0;
    if (fp) {
        for(int i = 0; ; ++i) {
            double a = 0, b = 0, x = 0;
            int n_roots = 0;
            if (fscanf(fp, "#%u (%lf, %lf) -> %d, %lf", &num, &a, &b, &n_roots, &x) == 5){
                tests[i] = {
                    .ss_test_n              = num,
                    .ss_kf_a = a, .ss_kf_b = b,
                    .ss_reference_nRoots    = (solutions_count) n_roots,
                    .ss_reference_ans       = x,
                };
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
        fclose(fp);
    }

    for (size_t i = 0; i<num_of_tests; ++i) {
        int test_failed = ONE_TEST_solve_linear_equation(&tests[i]);
        if (!test_failed)
            ++*count_tests;
        is_failed |= test_failed;

    }
    free(tests);
    return is_failed;
}
