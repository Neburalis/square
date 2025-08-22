#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "real_number_utils.h"

const double MIN_TOLERANCE = 0.0001; // 1E-6

int is_zero(double a) {
    assert(isfinite(a));

    if (fabs(a) < MIN_TOLERANCE)
        return 1;
    return 0;
}

int compare_double(double a, double b) {
    assert(isfinite(a) && "a must be finite");
    assert(isfinite(b) && "b must be finite");

    if (fabs(a - b) < MIN_TOLERANCE)
        return 0;
    else if (a > b)
        return 1;
    // else if (b < a)
    return -1;
}

int minus_zero_fix(double * const variable) {
    assert(variable != NULL);
    assert(isfinite(*variable));

    if (is_zero(*variable)){
        *variable = 0;
        return 1;
    }
    return -1;
}
