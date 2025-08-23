#ifndef MATH_EQUATION_SOLVER_H
#define MATH_EQUATION_SOLVER_H

enum solutions_count {
    NO  = 0,
    ONE = 1,
    TWO = 2,
    INF = -1,
};

enum solutions_count solve_square_equation(double a, double b, double c,
                          double * const x1, double * const x2);
int TEST_solve_square_equation(int * const count_tests);

enum solutions_count solve_linear_equation(double a, double b,
                          double * const x);
int TEST_solve_linear_equation(int * const count_tests);

#endif // MATH_EQUATION_SOLVER_H
