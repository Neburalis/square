#ifndef SQUARE_H
#define SQUARE_H

#include "../math_equation_solver/math_equation_solver.h"

enum ss_status {
    NOT_INPUT  = -3,
    NOT_SOLVE  = -2,
    SOLVED_INF = -1,
    SOLVED_NO  = 0,
    SOLVED_ONE = 1,
    SOLVED_TWO = 2,
};

struct square_equation {
    enum ss_status status;
    double kf_a;
    double kf_b;
    double kf_c;
    double ans1;
    double ans2;
};

enum solutions_count square_solver(struct square_equation * const eq);

void input_square_koef(struct square_equation * const eq);

int output_square_solver_result(struct square_equation * const eq);

int square_equation_minus_zero_fix(struct square_equation * const eq);

#endif // SQUARE_H
