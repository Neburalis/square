#include <stdio.h>
#include <math.h>

#include "square.h"
#include "math_equation_solver.h"
#include "real_number_utils.h"

#include "square_tests.h"

int TEST_square_solver(int * const count_tests) {
    /*
    (1, -3, 2) -> TWO, 1, 2
    (1, 2, 0) -> TWO, 0, -2
    (1, 0, 0) -> ONE, 0
    (1, 2, 1) -> ONE, -1
    (0, 2, 0) -> ONE, 0
    (0, 2, 5) -> ONE, -2.5
    (1, 0, 2) -> NO
    (0, 0, 2) -> NO
    (0, 0, -5) -> NO
    (0, 0, 0) -> INF
    */

    int is_passed = 0;

    // ------------ TEST 1 -------------
    // (1, -3, 2) -> TWO, 1, 2
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 1,
        .kf_b   = -3,
        .kf_c   = 2,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == TWO &&
        eq.status == SOLVED_TWO && (
        (compare_double(eq.ans1, 1) == 0 && compare_double(eq.ans2, 2) == 0) ||
        (compare_double(eq.ans2, 1) == 0 && compare_double(eq.ans1, 2) == 0))
        )
    ) {
        printf("TEST 1 FAILED:\n"
               "square_solver(1, -3, 2, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be TWO, SOLVED_TWO, 1, 2)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 2 -------------
    // (1, 2, 0) -> TWO, 0, -2
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 1,
        .kf_b   = 2,
        .kf_c   = 0,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == TWO &&
        eq.status == SOLVED_TWO && (
        (compare_double(eq.ans1, 0) == 0 && compare_double(eq.ans2, -2) == 0) ||
        (compare_double(eq.ans2, 0) == 0 && compare_double(eq.ans1, -2) == 0))
        )
    ) {
        printf("TEST 2 FAILED:\n"
               "square_solver(1, 2, 0, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be TWO, SOLVED_TWO, 0, -2)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 3 -------------
    // (1, 0, 0) -> ONE, 0
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 1,
        .kf_b   = 0,
        .kf_c   = 0,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == ONE &&
        eq.status == SOLVED_ONE &&
        compare_double(eq.ans1, 0) == 0
        )
    ) {
        printf("TEST 3 FAILED:\n"
               "square_solver(1, 0, 0, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be ONE, SOLVED_ONE, 0)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 4 -------------
    // (1, 2, 1) -> ONE, -1
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 1,
        .kf_b   = 2,
        .kf_c   = 1,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == ONE &&
        eq.status == SOLVED_ONE &&
        compare_double(eq.ans1, -1) == 0
        )
    ) {
        printf("TEST 4 FAILED:\n"
               "square_solver(1, 2, 1, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be ONE, SOLVED_ONE, -1)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 5 -------------
    // (0, 2, 0) -> ONE, 0
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 0,
        .kf_b   = 2,
        .kf_c   = 0,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == ONE &&
        eq.status == SOLVED_ONE &&
        compare_double(eq.ans1, 0) == 0
        )
    ) {
        printf("TEST 5 FAILED:\n"
               "square_solver(0, 2, 0, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be ONE, SOLVED_ONE, 0)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 6 -------------
    // (0, 2, 5) -> ONE, -2.5
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 0,
        .kf_b   = 2,
        .kf_c   = 5,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == ONE &&
        eq.status == SOLVED_ONE &&
        compare_double(eq.ans1, -2.5) == 0
        )
    ) {
        printf("TEST 6 FAILED:\n"
               "square_solver(0, 2, 5, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be ONE, SOLVED_ONE, -2.5)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 7 -------------
    // (1, 0, 2) -> NO
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 1,
        .kf_b   = 0,
        .kf_c   = 2,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == NO &&
        eq.status == SOLVED_NO
        )
    ) {
        printf("TEST 7 FAILED:\n"
               "square_solver(1, 0, 2, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be NO, SOLVED_NO)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 8 -------------
    // (0, 0, 2) -> NO
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 0,
        .kf_b   = 0,
        .kf_c   = 2,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == NO &&
        eq.status == SOLVED_NO
        )
    ) {
        printf("TEST 8 FAILED:\n"
               "square_solver(0, 0, 2, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be NO, SOLVED_NO)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 9 -------------
    // (0, 0, -5) -> NO
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 0,
        .kf_b   = 0,
        .kf_c   = -5,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == NO &&
        eq.status == SOLVED_NO
        )
    ) {
        printf("TEST 9 FAILED:\n"
               "square_solver(0, 0, -5, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be NO, SOLVED_NO)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    // ------------ TEST 10 -------------
    // (0, 0, 0) -> INF
    {
    struct square_equation eq = {
        .status = NOT_SOLVE,
        .kf_a   = 0,
        .kf_b   = 0,
        .kf_c   = 0,
        .ans1   = NAN,
        .ans2   = NAN,
    };
    enum solutions_count n_roots = square_solver(&eq);
    if (!
        (
        n_roots == INF &&
        eq.status == SOLVED_INF
        )
    ) {
        printf("TEST 10 FAILED:\n"
               "square_solver(0, 0, 0, ...) -> n_roots = %d, status = %d, ans1 = %lf, ans2 = %lf\n"
               "(should be INF, SOLVED_INF)",
               n_roots, eq.status, eq.ans1, eq.ans2);
        is_passed = -1;
    }
    else
        ++*count_tests;
    }

    return is_passed;
}

