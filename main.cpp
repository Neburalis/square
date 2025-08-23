#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "square/square.h"
#include "io_utils/io_utils.h"
#include "math_equation_solver/math_equation_solver.h"
#include "real_number_utils/real_number_utils.h"
#include "real_number_utils/real_number_utils_tests.h"

//TODO: option selfcheck help (getopt)

int main() {
    int test_passed = 0;
    printf("Selfcheck ...\n");
    uint8_t is_failed = 0;
    is_failed |= TEST_solve_square_equation(&test_passed);
    is_failed |= TEST_solve_linear_equation(&test_passed);
    is_failed |= TEST_is_zero(&test_passed);
    is_failed |= TEST_compare_double(&test_passed);

    printf(!is_failed ? "PASSED %d TESTS\n" : "FAILED\n", test_passed);

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
