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

int selfcheck() {
    spinner("Selfchecking ", 2500, 150);

    uint32_t test_passed = 0;
    uint8_t is_failed = 0;
    {
        FILE *fp = fopen("test/solve_square_equation_test_data.txt", "r");
        is_failed |= TEST_solve_square_equation(fp, &test_passed);
        fclose(fp);
    }
    {
        FILE *fp = fopen("test/solve_linear_equation_test_data.txt", "r");
        is_failed |= TEST_solve_linear_equation(fp, &test_passed);
        fclose(fp);
    }
    {
        FILE *fp = fopen("test/is_zero_test_data.txt", "r");
        is_failed |= TEST_is_zero(fp, &test_passed);
        fclose(fp);
    }
    {
        FILE *fp = fopen("test/minus_zero_fix_test_data.txt", "r");
        is_failed |= TEST_minus_zero_fix(fp, &test_passed);
        fclose(fp);
    }
    {
        FILE *fp = fopen("test/compare_double_test_data.txt", "r");
        is_failed |= TEST_compare_double(fp, &test_passed);
        fclose(fp);
    }
    {
        FILE *fp = fopen("test/square_solver_test_data.txt", "r");
        is_failed |= TEST_square_solver(fp, &test_passed);
        fclose(fp);
    }
    if (!is_failed) {
        printf(GREEN("PASSED %u TESTS\n"), test_passed);
        return 0;
    }
    else {
        fprintf(stderr, RED("FAILED\n"));
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

int jwg(double a, double b) {
    return isfinite((a / b));
}

int main(int argc, char * argv[]) {
    int rez = 0;

    while ( (rez = getopt(argc, argv, "chq")) != -1){
		switch (rez) {
		case 'c':
            if (selfcheck()) {
                printf("SELFCHECK FAILED. See stderr to view problem.\n");
                abort();
            }
            break;
		case 'h':
            // TODO: add help param
            spinner("Думаю ", 5000, 150);
            printf(GREEN("ПРАНК: ") "хелпа не будет, разбирайся сам\n");
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
        if (status) {
            ERROR_MSG(CYAN("returned value: %d"), status);
            return status;
        }
    }

    printf(CYAN("\n"
        " _   _       _             _                                   _ _      ____ ___ _____ _   _ _   _ ____           \n"
        "| | | |   __| | ___  _ __ | |_    ___ ___  _ __ ___  _ __ ___ (_) |_   / ___|_ _|_   _| | | | | | | __ )          \n"
        "| | | |  / _` |/ _ \\| '_ \\| __|  / __/ _ \\| '_ ` _ \\| '_ ` _ \\| | __| | |  _ | |  | | | |_| | | | |  _ \\    \n"
        "| |_| | | (_| | (_) | | | | |_  | (_| (_) | | | | | | | | | | | | |_  | |_| || |  | | |  _  | |_| | |_) |         \n"
        " \\___/   \\__,_|\\___/|_| |_|\\__|  \\___\\___/|_| |_| |_|_| |_| |_|_|\\__|  \\____|___| |_| |_| |_|\\___/|____/ \n\n"
    ));
    return 0;
}
