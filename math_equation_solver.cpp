#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "math_equation_solver.h"
#include "real_number_utils.h"

// enum solutions_count {
//     NO  = 0,
//     ONE = 1,
//     TWO = 2,
//     INF = -1
// }

enum solutions_count solve_square_equation(double a, double b, double c,
                          double * const x1, double * const x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    assert(!is_zero(a));

    double d = b * b - 4 * a * c;
    if (d > 0) {
        double sqrt_d = sqrt(d);
        *x1 = ( -b + sqrt_d) / (2*a);
        *x2 = ( -b - sqrt_d) / (2*a);
        return TWO;
    }
    else if (is_zero(d)) {
        *x1 = *x2 = -b / (2*a);
        return ONE;
    }
    else { //if (d < 0)
        return NO;
    }
}

int TEST_solve_square_equation(int * const count_tests) {
    /*
    (1, -3, 2) -> TWO, 1, 2
    (1, 2, 0) -> TWO, 0, -2
    (1, 0, 0) -> ONE, 0
    (1, 2, 1) -> ONE, -1
    (1, 0, 2) -> NO
    */

    int is_passed = 0;
    double x1 = 0, x2 = 0;
    enum solutions_count n_roots = solve_square_equation(1, -3, 2, &x1, &x2);
    if (!
        (
        n_roots == TWO && (
        (compare_double(x1, 1) == 0 && compare_double(x2, 2) == 0) ||
        (compare_double(x2, 1) == 0 && compare_double(x1, 2) == 0))
        )
    ) {
        printf("TEST FAILED:\n"
               "solve_square_equation(1, -3, 2, ...) -> n_roots = %d, x1 = %lf, x2 = %lf\n"
               "(should be TWO, 1, 2)",
               n_roots, x1, x2);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x1 = 0, x2 = 0;
    n_roots = solve_square_equation(1, 2, 0, &x1, &x2);
    if (!
        (n_roots == TWO && (
        (compare_double(x1, 0) == 0 && compare_double(x2, -2) == 0) ||
        (compare_double(x2, 0) == 0 && compare_double(x1, -2) == 0)))
    ) {
        printf("TEST FAILED:\n"
               "solve_square_equation(1, 2, 0, ...) -> n_roots = %d, x1 = %lf, x2 = %lf\n"
               "(should be TWO, 0, -2)",
               n_roots, x1, x2);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x1 = 0, x2 = 0;
    n_roots = solve_square_equation(1, 0, 0, &x1, &x2);
    if (!
        (n_roots == ONE &&
        compare_double(x1, 0) == 0)
    ) {
        printf("TEST FAILED:\n"
               "solve_square_equation(1, 0, 0, ...) -> n_roots = %d, x1 = %lf, x2 = %lf\n"
               "(should be ONE, 0)",
               n_roots, x1, x2);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x1 = 0, x2 = 0;
    n_roots = solve_square_equation(1, 2, 1, &x1, &x2);
    if (!
        (n_roots == ONE &&
        compare_double(x1, -1) == 0)
    ) {
        printf("TEST FAILED:\n"
               "solve_square_equation(1, 2, 1, ...) -> n_roots = %d, x1 = %lf, x2 = %lf\n"
               "(should be NO)",
               n_roots, x1, x2);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x1 = 0, x2 = 0;
    n_roots = solve_square_equation(1, 0, 2, &x1, &x2);
    if (!
        (n_roots == NO)
    ) {
        printf("TEST FAILED:\n"
               "solve_square_equation(1, 0, 2, ...) -> n_roots = %d, x1 = %lf, x2 = %lf\n"
               "(should be NO)",
               n_roots, x1, x2);
        is_passed = -1;
    }
    else
        ++*count_tests;

    return is_passed;
}

enum solutions_count solve_linear_equation(double a, double b,
                          double * const x) {
    assert(isfinite(a));
    assert(isfinite(b));

    assert(x != NULL);

    if (!is_zero(a)) {
        *x = -b / a;
        return ONE;
    }
    else if (!is_zero(b)) {
        return NO;
    }
    else { // a = 0  b = 0
        return INF;
    }

}

int TEST_solve_linear_equation(int * const count_tests) {
    /*
    (2, 0) -> ONE, 0
    (2, 5) -> ONE, -2.5
    (0, 2) -> NO
    (0, -5) -> NO
    (0, 0) -> INF
    */

    int is_passed = 0;
    double x = 0;
    enum solutions_count n_roots = solve_linear_equation(2, 0, &x);
    if (!
        (n_roots == ONE &&
        compare_double(x, 0) == 0)
    ) {
        printf("TEST FAILED:\n"
               "solve_linear_equation(2, 0, ...) -> n_roots = %d, x = %lf\n"
               "(should be ONE, 0)",
               n_roots, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = 0;
    n_roots = solve_linear_equation(2, 5, &x);
    if (!
        (n_roots == ONE &&
        compare_double(x, -2.5) == 0)
    ) {
        printf("TEST FAILED:\n"
               "solve_linear_equation(2, 5, ...) -> n_roots = %d, x = %lf\n"
               "(should be ONE, -2.5)",
               n_roots, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = 0;
    n_roots = solve_linear_equation(0, 2, &x);
    if (!
        (n_roots == NO)
    ) {
        printf("TEST FAILED:\n"
               "solve_linear_equation(0, 2, ...) -> n_roots = %d, x = %lf\n"
               "(should be NO)",
               n_roots, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = 0;
    n_roots = solve_linear_equation(0, -5, &x);
    if (!
        (n_roots == NO)
    ) {
        printf("TEST FAILED:\n"
               "solve_linear_equation(0, -5, ...) -> n_roots = %d, x = %lf\n"
               "(should be NO)",
               n_roots, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    x = 0;
    n_roots = solve_linear_equation(0, 0, &x);
    if (!
        (n_roots == INF)
    ) {
        printf("TEST FAILED:\n"
               "solve_linear_equation(0, 0, ...) -> n_roots = %d, x = %lf\n"
               "(should be INF)",
               n_roots, x);
        is_passed = -1;
    }
    else
        ++*count_tests;

    return is_passed;
}
