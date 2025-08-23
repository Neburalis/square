#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "math_equation_solver.h"
#include "../real_number_utils/real_number_utils.h"

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
