#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>

#include "square.h"

#include "io_utils.h"
#include "real_number_utils.h"

enum solutions_count square_solver(struct square_equation * const eq) {
    assert(eq != NULL);
    assert(eq->status == NOT_SOLVE);

    if (eq == NULL) {
        errno = EINVAL;
        return ERR;
    }
    if (eq->status != NOT_SOLVE) {
        errno = EINVAL;
        return ERR;
    }

    double a = eq->kf_a, b = eq->kf_b, c = eq->kf_c;

    if (!is_zero(a)) {
        double x1 = NAN, x2 = NAN;
        enum solutions_count n_solutions = solve_square_equation(a, b, c, &x1, &x2);
        switch (n_solutions){
            case NO:
                eq->status = SOLVED_NO;
                return NO;
            case ONE:
                eq->status = SOLVED_ONE;
                eq->ans1 = eq->ans2 = x1;
                return ONE;
            case TWO:
                eq->status = SOLVED_TWO;
                eq->ans1 = x1;
                eq->ans2 = x2;
                return TWO;
            case INF:
                eq->status = SOLUTION_ERR;
                return ERR;
            case ERR:
                eq->status = SOLUTION_ERR;
                return ERR;
            default:
                eq->status = SOLUTION_ERR;
                return ERR;
        }
    }
    else {
        double x = NAN;
        enum solutions_count n_solutions = solve_linear_equation(b, c, &x);
        switch (n_solutions) {
            case NO:
                eq->status = SOLVED_NO;
                return NO;
            case ONE:
                eq->status = SOLVED_ONE;
                eq->ans1 = eq->ans2 = x;
                return ONE;
            case INF:
                eq->status = SOLVED_INF;
                return INF;
            case TWO:
                eq->status = SOLUTION_ERR;
                return ERR;
            case ERR:
                eq->status = SOLUTION_ERR;
                return ERR;
            default:
                return ERR;
        }
    }
}

void quiet_input_square_koef(struct square_equation * const eq) {
    assert(eq != NULL);

    if (eq == NULL) {
        errno = EINVAL;
        return;
    }

    scanf("%lf%lf%lf", &eq->kf_a, &eq->kf_b, &eq->kf_c);
    eq->status = NOT_SOLVE;

    return;
}

void pretty_input_square_koef(struct square_equation * const eq) {
    assert(eq != NULL);

    if (eq == NULL) {
        errno = EINVAL;
        return;
    }

    printf(CYAN(
        " ____                                                  \n"
        "/ ___|   __ _  _   _   __ _  _ __  ___                 \n"
        "\\___ \\  / _` || | | | / _` || '__|/ _ \\             \n"
        " ___) || (_| || |_| || (_| || |  |  __/                \n"
        "|____/  \\__, | \\__,_| \\__,_||_|  _\\___|            \n"
        "  ___   __ |_|_   _   __ _ | |_ (_)  ___   _ __        \n"
        " / _ \\ / _` || | | | / _` || __|| | / _ \\ | '_ \\    \n"
        "|  __/| (_| || |_| || (_| || |_ | || (_) || | | |      \n"
        " \\___| \\__, |_\\__,_| \\__,_| \\__||_| \\___/ |_| |_|\n"
        " ___   ___|_| |__   __ ___  _ __                       \n"
        "/ __| / _ \\ | |\\ \\ / // _ \\| '__|                  \n"
        "\\__ \\| (_) || | \\ V /|  __/| |                      \n"
        "|___/ \\___/ |_|  \\_/  \\___||_|                      \n\n"
    ));
    printf("🧮 Программа для решения квадратного уравнения ax^2 + bx + c = 0\n"
            "📝 Введите коэффициенты a, b и c каждый в новой строке.\n");

    eq->kf_a = safe_get_double("a = ");
    eq->kf_b = safe_get_double("b = ");
    eq->kf_c = safe_get_double("c = ");

    eq->status = NOT_SOLVE;

    printf("📊 Буду решать уравнение: %lgx^2 + %lgx + %lgc = 0\n", eq->kf_a, eq->kf_b, eq->kf_c);

    return;
}

int quiet_output_square_solver_result(struct square_equation * const eq) {
    assert(eq != NULL);

    if (eq == NULL) {
        errno = EINVAL;
        return -1;
    }

    switch (eq->status) {
        case SOLVED_TWO:
            printf("%lg %lg\n", eq->ans1, eq->ans2);
            break;
        case SOLVED_ONE:
            printf("%lg\n", eq->ans1);
            break;
        case SOLVED_NO:
            printf("NO\n");
            break;
        case SOLVED_INF:
            printf("INF\n");
            break;
        case NOT_INPUT:
            // printf("ERROR: equation is not initialized.\n");
            return 1;
        case NOT_SOLVE:
            // printf("ERROR: equation has not been solved yet.\n");
            return 1;
        case SOLUTION_ERR:
            //
            return 1;
        default:
            // printf("ERROR: unexpected value in n_solutions, n_solutions = %d\n", eq->status);
            return 1; // TODO: return enum
    }
    return 0;
}

int pretty_output_square_solver_result(struct square_equation * const eq) {
    assert(eq != NULL);

    if (eq == NULL) {
        errno = EINVAL;
        return -1;
    }

    printf("\n");
    spinner("Ведутся раскопки ", 1000, 150);
    printf("Нашел корни квадратного уравнения:\n");

    switch (eq->status) {
        case SOLVED_TWO:
            printf(
            " _____                           _       _   _                          \n"
            "|_   _|_      _____    ___  ___ | |_   _| |_(_) ___  _ __  ___ _        \n"
            "  | | \\ \\ /\\ / / _ \\  / __|/ _ \\| | | | | __| |/ _ \\| '_ \\/ __(_)\n"
            "  | |  \\ V  V / (_) | \\__ \\ (_) | | |_| | |_| | (_) | | | \\__ \\_   \n"
            "  |_|   \\_/\\_/ \\___/  |___/\\___/|_|\\__,_|\\__|_|\\___/|_| |_|___(_)\n\n"
            "x1 = %lg\tx2 = %lg", eq->ans1, eq->ans2);
            // random cat gif
            {
                const char * cat_gifs[] = {"lvl1cat2", "lvl1cat3"};
                show_random_gif(2, (const char **) cat_gifs);
            }
            break;
        case SOLVED_ONE:
            printf(
            "  ___                         _       _   _                         \n"
            " / _ \\ _ __   ___   ___  ___ | |_   _| |_(_) ___  _ __  ___ _      \n"
            "| | | | '_ \\ / _ \\ / __|/ _ \\| | | | | __| |/ _ \\| '_ \\/ __(_) \n"
            "| |_| | | | |  __/ \\__ \\ (_) | | |_| | |_| | (_) | | | \\__ \\_   \n"
            " \\___/|_| |_|\\___| |___/\\___/|_|\\__,_|\\__|_|\\___/|_| |_|___(_)\n\n"
            "x = %lg", eq->ans1);
            // random cat gif
            {
                const char * cat_gifs[] = {"lvl2cat1", "lvl5cat1", "lvl4cat3"};
                show_random_gif(3, (const char **) cat_gifs);
            }
            break;
        case SOLVED_NO:
            printf(
            " _   _                   _       _   _                         \n"
            "| \\ | | ___    ___  ___ | |_   _| |_(_) ___  _ __  ___ _      \n"
            "|  \\| |/ _ \\  / __|/ _ \\| | | | | __| |/ _ \\| '_ \\/ __(_) \n"
            "| |\\  | (_) | \\__ \\ (_) | | |_| | |_| | (_) | | | \\__ \\_  \n"
            "|_| \\_|\\___/  |___/\\___/|_|\\__,_|\\__|_|\\___/|_| |_|___(_)\n\n");
            // random cat gif
            {
                const char * cat_gifs[] = {"lvl3cat1", "lvl6cat2"};
                show_random_gif(2, (const char **) cat_gifs);
            }
            break;
        case SOLVED_INF:
            printf(
            " ___        __             _       _   _                       \n"
            "|_ _|_ __  / _|  ___  ___ | |_   _| |_(_) ___  _ __  ___ _     \n"
            " | || '_ \\| |_  / __|/ _ \\| | | | | __| |/ _ \\| '_ \\/ __(_)\n"
            " | || | | |  _| \\__ \\ (_) | | |_| | |_| | (_) | | | \\__ \\_ \n"
            "|___|_| |_|_|   |___/\\___/|_|\\__,_|\\__|_|\\___/|_| |_|___(_)\n\n");
            // random cat gif
            {
                const char * cat_gifs[] = {"lvl4cat1", "lvl4cat2", "lvl4cat4"};
                show_random_gif(3, (const char **) cat_gifs);
            }
            break;
        case NOT_INPUT:
            printf("ERROR: equation is not initialized.\n");
            return -1;
        case NOT_SOLVE:
            printf("ERROR: equation has not been solved yet.\n");
            return -1;
        case SOLUTION_ERR:
            // ...
            return -1;
        default:
            printf("ERROR: unexpected value in n_solutions, n_solutions = %d\n", eq->status);
            return -1; // TODO: return enum
    }
    return 0;
}

int square_equation_minus_zero_fix(struct square_equation * const eq) {
    assert(eq != NULL);

    if (eq == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (eq->status == SOLVED_ONE) {
        minus_zero_fix(&eq->ans1);
        return 0;
    }
    else if (eq->status == SOLVED_TWO) {
        minus_zero_fix(&eq->ans1);
        minus_zero_fix(&eq->ans2);
        return 0;
    }
    return 1;
}
