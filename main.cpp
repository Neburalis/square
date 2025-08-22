#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "square.h"
#include "io_utils.h"
#include "math_equation_solver.h"

int main(){
    int choice = 0;

    do {
        struct square_equation eq = {
            .status = NOT_INPUT,
            .kf_a   = NAN,
            .kf_b   = NAN,
            .kf_c   = NAN,
            .ans1   = NAN,
            .ans2   = NAN,
        };

        input_square_koef(&eq);
        square_solver(&eq);
        square_equation_minus_zero_fix(&eq);
        if(output_square_solver_result(&eq))
            return -1;

    }
    // repeat?
    while (is_user_want_continue("\n🔄 Хотите решить еще одно уравнение (Y/n)? "));

    return 0;
}
