#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "math_equation_solver.h"
#include "real_number_utils.h"
#include "io_utils.h"

// enum solutions_count {
//     NO  = 0,
//     ONE = 1,
//     TWO = 2,
//     INF = -1
// }

enum solutions_count solve_square_equation(double a, double b, double c,
                          double * const x1, double * const x2) {
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    assert(!is_zero(a));

    if (isnan(a) ||
        isnan(b) ||
        isnan(c)) {
        errno = EINVAL; // koefs must be finite
        ERROR_MSG("один из коэффициентов нан\na = %lg, b = %lg, c = %lg", a, b, c);
        return ERR;
    }

    if (x1 == NULL || x2 == NULL || x1 == x2) {
        errno = EINVAL; // ptrs must be not NULL and not the same
        ERROR_MSG("получил null ptr или одинаковые указатели");
        return ERR;
    }

    double d = b * b - 4 * a * c;

    if (isnan(d)) {
        errno = ERANGE; // d out of range
        ERROR_MSG(CYAN("message:") " %s\n", "результат вычисления дискриминанта некорректен (возможно, переполнение или несогласованные данные).");
        return ERR;
    }

    // printf("%lg\n", d);

    if (is_zero(d)) {
        *x1 = *x2 = -b / (2*a);
        return ONE;
    }
    else if (d > 0) {
        double sqrt_d = sqrt(d);
        *x1 = ( -b + sqrt_d) / (2*a);
        *x2 = ( -b - sqrt_d) / (2*a);
        if (compare_double(*x1, *x2) == 0){
            *x1 = *x2 = -b / (2*a);
            return ONE;
        }
        return TWO;
    }
    else { //if (d < 0)
        return NO;
    }
}

enum solutions_count solve_linear_equation(double a, double b,
                          double * const x) {
    assert(!isnan(a));
    assert(!isnan(b));

    assert(x != NULL);

    if (isnan(a) || isnan(b)) {
        errno = EINVAL; // koefs must be finite
        ERROR_MSG("один из коэффициентов нан");
        return ERR;
    }

    if (x == NULL) {
        errno = EINVAL; // ptr must be not NULL
        ERROR_MSG("передан null ptr");
        return ERR;
    }

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
