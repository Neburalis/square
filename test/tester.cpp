#include <stdio.h>
#include <math.h>

#include "io_utils.h"
#include "math_equation_solver_tests.h"
#include "real_number_utils_tests.h"
#include "square_tests.h"

int selfcheck() {
    spinner("Selfchecking ", 2500, 150);

    uint32_t test_passed = 0;
    uint8_t is_failed = 0;

    FILE *fp = fopen("test/solve_square_equation_test_data.txt", "r");
    is_failed |= TEST_solve_square_equation(fp, &test_passed);
    fclose(fp);

    fp = fopen("test/solve_linear_equation_test_data.txt", "r");
    is_failed |= TEST_solve_linear_equation(fp, &test_passed);
    fclose(fp);

    fp = fopen("test/is_zero_test_data.txt", "r");
    is_failed |= TEST_is_zero(fp, &test_passed);
    fclose(fp);

    fp = fopen("test/minus_zero_fix_test_data.txt", "r");
    is_failed |= TEST_minus_zero_fix(fp, &test_passed);
    fclose(fp);

    fp = fopen("test/compare_double_test_data.txt", "r");
    is_failed |= TEST_compare_double(fp, &test_passed);
    fclose(fp);

    fp = fopen("test/square_solver_test_data.txt", "r");
    is_failed |= TEST_square_solver(fp, &test_passed);
    fclose(fp);

    if (!is_failed) {
        printf(GREEN("PASSED %u TESTS\n"), test_passed);
        // system("cd cat_gifs && qlmanage -p lvl1cat1.gif > /dev/null");
        show_gif("lvl1cat1.gif");
        return 0;
    }
    else {
        fprintf(stderr, RED("FAILED\n"));
        return 1;
    }
}
