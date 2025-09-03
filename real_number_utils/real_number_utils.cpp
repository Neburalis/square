#include <assert.h>
#include <math.h>

#include "real_number_utils.h"

const double MIN_TOLERANCE = 1E-6;

int is_zero(double var) {
    assert(!isnan(var));

    if (fabs(var) < MIN_TOLERANCE)
        return 1;
    return 0;
}

int compare_double(double first, double second) {
    assert(!isnan(first)  && "first must be not nan");
    assert(!isnan(second) && "second must be not nan");

    if (fabs(first - second) < MIN_TOLERANCE)
        return 0;
    else if (first > second)
        return 1;
    // else if (b < a)
    return -1;
}

int minus_zero_fix(double * const variable) {
    assert(variable != NULL);
    assert(!isnan(*variable));

    if (is_zero(*variable)){
        *variable = fabs(*variable);
        return 1;
    }
    return -1;
}

double map(double value,
           double value_min, double value_max,
           double res_min, double res_max
          ) {
    assert(!isnan(value)          && "value must be not nan number");
    assert(!isnan(value_min)      && "value_min must be not nan number");
    assert(!isnan(value_max)      && "value_max must be not nan number");
    assert(!isnan(res_min)        && "res_min must be not nan number");
    assert(!isnan(res_max)        && "res_max must be not nan number");

    assert(value_min < value_max    && "value_min must be less than value_max");
    assert(res_min   < res_max      && "res_min must be less than res_max");

    value -= value_min;
    value *= (res_max - res_min);
    value /= (value_max - value_min);

    return value + res_min;
}