#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include "square.h"
#include "square_tests.h"
#include "io_utils.h"
#include "math_equation_solver.h"
#include "math_equation_solver_tests.h"
#include "real_number_utils.h"
#include "real_number_utils_tests.h"

//TODO: colored output

int selfcheck() {
    int test_passed = 0;
    printf("Selfcheck ...\n");
    uint8_t is_failed = 0;
    is_failed |= TEST_solve_square_equation(&test_passed);
    is_failed |= TEST_solve_linear_equation(&test_passed);
    is_failed |= TEST_is_zero(&test_passed);
    is_failed |= TEST_compare_double(&test_passed);
    is_failed |= TEST_minus_zero_fix(&test_passed);
    is_failed |= TEST_square_solver(&test_passed);
    if (!is_failed) {
        printf("PASSED %d TESTS\n", test_passed);
        return 0;
    }
    else {
        fprintf(stderr, "FAILED\n");
        return 1;
    }
}

int default_work() {
    do {
        struct square_equation eq = {
            .status = NOT_INPUT,
            .kf_a   = NAN,
            .kf_b   = NAN,
            .kf_c   = NAN,
            .ans1   = NAN,
            .ans2   = NAN,
        };

        pretty_input_square_koef(&eq);
        square_solver(&eq);
        square_equation_minus_zero_fix(&eq);
        if(pretty_output_square_solver_result(&eq))
            return -1;

    }
    // repeat?
    while (is_user_want_continue("\n🔄 Хотите решить еще одно уравнение (Y/n)? "));

    return 0;
}

int quiet_work() {
    struct square_equation eq = {
        .status = NOT_INPUT,
        .kf_a   = NAN,
        .kf_b   = NAN,
        .kf_c   = NAN,
        .ans1   = NAN,
        .ans2   = NAN,
    };

    quiet_input_square_koef(&eq);
    square_solver(&eq);
    square_equation_minus_zero_fix(&eq);
    if(quiet_output_square_solver_result(&eq))
        return -1;

    return 0;
}

int main(int argc, char * argv[]) {
    int rez = 0;

    while ( (rez = getopt(argc, argv, "chq")) != -1){
		switch (rez) {
		case 'c':
            printf("Starting selfcheck\n");
            if (selfcheck()) {
                printf("SELFCHECK FAILED. See stderr to view problem.\n");
                abort();
            }
            break;
		case 'h':
            // TODO: add help param
            printf("found argument \"h\".\n");
            break;
		case 'q': {
            int status = quiet_work();
            if (!status)
                return status;
            break;
        }
		case '?':
        default:
            printf("Error found !\n");
            break;
		}
	}

    if (argc == 1) {
        int status = default_work();
        if (!status)
            return status;
    }
    return 0;
}
