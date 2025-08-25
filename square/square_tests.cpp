#include <stdio.h>
#include <math.h>

#include "square.h"
#include "math_equation_solver.h"
#include "real_number_utils.h"

#include "square_tests.h"

struct TEST_DATA_square_solver {
    uint16_t ss_test_n;
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
            "TEST %d FAILED:                             \n" // test_n
            "square_solver(%lg, %lg, %lg, ...) ->\n" // kf_a, kf_b, kf_c
            "\t-> n_roots = %d, x1 = %lf, x2 = %lf       \n" // n_r, x1, x2
            "(should be %d, %lf, %lf)                    \n", // ref n_r, ref x1, ref x2
            test_data->ss_test_n,
            test_data->ss_kf_a, test_data->ss_kf_b, test_data->ss_kf_c,
            n_roots, eq.ans1, eq.ans2,
            test_data->ss_reference_nRoots, test_data->ss_reference_ans1, test_data->ss_reference_ans1
        );
    return is_failed;
}

int TEST_square_solver(int * const count_tests) {
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
    int is_failed = 0;

    struct TEST_DATA_square_solver tests[] = {
        {
            .ss_test_n           = 1,
            .ss_kf_a             = 1,
            .ss_kf_b             = -3,
            .ss_kf_c             = 2,
            .ss_reference_nRoots = TWO,
            .ss_reference_ans1   = 1,
            .ss_reference_ans2   = 2,
        },
        {
            .ss_test_n           = 2,
            .ss_kf_a             = 1,
            .ss_kf_b             = 2,
            .ss_kf_c             = 0,
            .ss_reference_nRoots = TWO,
            .ss_reference_ans1   = 0,
            .ss_reference_ans2   = -2,
        },
        {
            .ss_test_n           = 3,
            .ss_kf_a             = 1,
            .ss_kf_b             = 0,
            .ss_kf_c             = 0,
            .ss_reference_nRoots = ONE,
            .ss_reference_ans1   = 0,
            .ss_reference_ans2   = 0,
        },
        {
            .ss_test_n           = 4,
            .ss_kf_a             = 1,
            .ss_kf_b             = 2,
            .ss_kf_c             = 1,
            .ss_reference_nRoots = ONE,
            .ss_reference_ans1   = -1,
            .ss_reference_ans2   = -1,
        },
        {
            .ss_test_n           = 5,
            .ss_kf_a             = 0,
            .ss_kf_b             = 2,
            .ss_kf_c             = 0,
            .ss_reference_nRoots = ONE,
            .ss_reference_ans1   = 0,
            .ss_reference_ans2   = 0,
        },
        {
            .ss_test_n           = 6,
            .ss_kf_a             = 0,
            .ss_kf_b             = 2,
            .ss_kf_c             = 5,
            .ss_reference_nRoots = ONE,
            .ss_reference_ans1   = -2.5,
            .ss_reference_ans2   = -2.5,
        },
        {
            .ss_test_n           = 7,
            .ss_kf_a             = 1,
            .ss_kf_b             = 0,
            .ss_kf_c             = 2,
            .ss_reference_nRoots = NO,
            .ss_reference_ans1   = NAN,
            .ss_reference_ans2   = NAN,
        },
        {
            .ss_test_n           = 8,
            .ss_kf_a             = 0,
            .ss_kf_b             = 0,
            .ss_kf_c             = 2,
            .ss_reference_nRoots = NO,
            .ss_reference_ans1   = NAN,
            .ss_reference_ans2   = NAN,
        },
        {
            .ss_test_n           = 9,
            .ss_kf_a             = 0,
            .ss_kf_b             = 0,
            .ss_kf_c             = -5,
            .ss_reference_nRoots = NO,
            .ss_reference_ans1   = NAN,
            .ss_reference_ans2   = NAN,
        },
        {
            .ss_test_n           = 10,
            .ss_kf_a             = 0,
            .ss_kf_b             = 0,
            .ss_kf_c             = 0,
            .ss_reference_nRoots = INF,
            .ss_reference_ans1   = NAN,
            .ss_reference_ans2   = NAN,
        },
    };

    size_t n = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i<n; ++i) {
        int test_failed = ONE_TEST_square_solver(&tests[i]);
        if (!(test_failed))
            ++*count_tests;
        is_failed |= test_failed;
    }

    return is_failed;
}

