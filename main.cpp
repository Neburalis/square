#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include "square.h"
#include "io_utils.h"
#include "math_equation_solver.h"
#include "real_number_utils.h"
#include "tester.h"

int default_work();
int quiet_work();

// TODO: perror errno

int main(int argc, char * argv[]) {
    int rez = 0;

    while ( (rez = getopt(argc, argv, "chq")) != -1){
		switch (rez) {
		case 'c':
            if (selfcheck()) {
                printf(BOLD(RED("SELFCHECK FAILED. See stderr to view problem.\n")));
                return -1;
            }
            break;
		case 'h':
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

    printf(BOLD(CYAN("\n"
        " _   _       _             _                                   _ _      ____ ___ _____ _   _ _   _ ____           \n"
        "| | | |   __| | ___  _ __ | |_    ___ ___  _ __ ___  _ __ ___ (_) |_   / ___|_ _|_   _| | | | | | | __ )          \n"
        "| | | |  / _` |/ _ \\| '_ \\| __|  / __/ _ \\| '_ ` _ \\| '_ ` _ \\| | __| | |  _ | |  | | | |_| | | | |  _ \\    \n"
        "| |_| | | (_| | (_) | | | | |_  | (_| (_) | | | | | | | | | | | | |_  | |_| || |  | | |  _  | |_| | |_) |         \n"
        " \\___/   \\__,_|\\___/|_| |_|\\__|  \\___\\___/|_| |_| |_|_| |_| |_|_|\\__|  \\____|___| |_| |_| |_|\\___/|____/ \n\n"
    )));
    return 0;
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
        if(pretty_output_square_solver_result(&eq)){
            ERROR_MSG("Error message:%s\n", CYAN("pretty_output_square_solver_result is return not zero value"));
            return -1;
        }

    }
    // repeat?
    while (is_user_want_continue("\n🔄 Хотите решить еще одно уравнение (Y/n)? ") == 1);

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