#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "square.h"
#include "math_equation_solver.h"
#include "real_number_utils.h"

#include "square_tests.h"
#include "io_utils.h"

struct TEST_DATA_square_solver {
    uint32_t ss_test_n;
    double ss_kf_a, ss_kf_b, ss_kf_c;
    enum solutions_count ss_reference_nRoots;
    double ss_reference_ans1, ss_reference_ans2;
};
static int ONE_TEST_square_solver(struct TEST_DATA_square_solver const * test_data) {
    int is_failed = 0;

    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = test_data->ss_kf_a,
        .kf_b   = test_data->ss_kf_b,
        .kf_c   = test_data->ss_kf_c,
        .ans1   = NAN,
        .ans2   = NAN,
    };

    enum solutions_count n_roots =
        square_solver(&eq);

    if (n_roots == test_data->ss_reference_nRoots) {
        switch (test_data->ss_reference_nRoots){
            case INF:
                break;
            case NO:
                break;
            case ONE:
                if (!(compare_double(eq.ans1, test_data->ss_reference_ans1) == 0))
                    is_failed = 1;
                break;
            case TWO:
                if (!((compare_double(eq.ans1, test_data->ss_reference_ans1) == 0 && compare_double(eq.ans2, test_data->ss_reference_ans2) == 0) ||
                      (compare_double(eq.ans2, test_data->ss_reference_ans1) == 0 && compare_double(eq.ans1, test_data->ss_reference_ans2) == 0)))
                    is_failed = 1;
                break;
            case ERR:
            default:
                is_failed = 2;
                break;
        }
    }
    else{
        is_failed = 1;
    }

    if (is_failed)
        fprintf(stderr,
            RED("TEST %u FAILED:\n") // test_n
            "square_solver(%lg, %lg, %lg, ...) ->\n" // kf_a, kf_b, kf_c
            "\t-> n_roots = %d, x1 = %lf, x2 = %lf       \n" // n_r, x1, x2
            "(should be %d, %lf, %lf)                  \n\n", // ref n_r, ref x1, ref x2
            test_data->ss_test_n,
            test_data->ss_kf_a, test_data->ss_kf_b, test_data->ss_kf_c,
            n_roots, eq.ans1, eq.ans2,
            test_data->ss_reference_nRoots, test_data->ss_reference_ans1, test_data->ss_reference_ans1
        );
    return is_failed;
}
int TEST_square_solver(FILE *fp, uint32_t * const count_tests) {
    /*
    #1 (1, -3, 2) -> TWO, 1, 2
    #2 (1, 2, 0) -> TWO, 0, -2
    #3 (1, 0, 0) -> ONE, 0
    #4 (1, 2, 1) -> ONE, -1
    #5 (0, 2, 0) -> ONE, 0
    #6 (0, 2, 5) -> ONE, -2.5
    #7 (1, 0, 2) -> NO
    #8 (0, 0, 2) -> NO
    #9 (0, 0, -5) -> NO
    #10(0, 0, 0) -> INF
    */
    if (!fp){
        errno = EBADF;
        return -1;
    }
    size_t line_num = lines_in_file(fp);
    int is_failed = 0;

    struct TEST_DATA_square_solver * tests =
        (TEST_DATA_square_solver *) calloc(line_num, sizeof(TEST_DATA_square_solver));

    size_t num_of_tests = 0;

    if (fp) {
        for(int i = 0;;++i) {
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
                ++num_of_tests;
            }

            if (getc(fp) == EOF)
                break;
        }
        fclose(fp);
    }

    for (size_t i = 0; i<num_of_tests; ++i) {
        int test_failed = ONE_TEST_square_solver(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |= test_failed;
    }

    return is_failed;
}

