#ifndef REAL_NUMBER_UTILS_H
#define REAL_NUMBER_UTILS_H

int is_zero (double var);
int TEST_is_zero(int * const count_tests);

// -------
//!
//! Func to compare real numbers.
//! if compare_double < 0 => a < b
//! if compare_double == 0 => a == b (Taking into account tolerance MIN_TOLERANCE)
//! if compare_double > 0 => a > b
//!
// ----
int compare_double(double a, double b);
int TEST_compare_double(int * const count_tests);

int minus_zero_fix(double * const variable);

#endif // REAL_NUMBER_UTILS_H
