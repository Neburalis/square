#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "real_number_utils.c"

const int SS_INF_SOLUTIONS = -1;

int square_solver(double a, double b, double c,
                    double *x1, double *x2);

void input_square_koef(double *a, double *b, double *c) {
    assert(a != NULL && b != NULL && c != NULL && a != b && a != c && b != c);
    printf("🧮 Программа для решения квадратного уравнения ax^2 + bx + c = 0\n"
           "📝 Введите коэффициенты a, b и c каждый в новой строке.\n");
    *a = safe_get_double('a');
    *b = safe_get_double('b');
    *c = safe_get_double('c');

    printf("📊 Буду решать уравнение: %lgx^2 + %lgx + %lgc = 0\n", *a, *b, *c);
    return;
}

int output_square_solver_result(int n_solutions, double x1, double x2) {
    switch (n_solutions) {
        case 2:
            printf("Two solutions:\n"
                   "x1 = %lg\tx2 = %lg", x1, x2);
            break;
        case 1:
            printf("One solution:\n"
                   "x = %lg", x1);
            break;
        case 0:
            printf("No solutions");
            break;
        case SS_INF_SOLUTIONS:
            printf("INF solutions");
            break;
        default:
            printf("ERROR: unexpected value in n_solutions, n_solutions = %d", n_solutions);
            return 0;
    }
    return 1;
}

int main(){
    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;
    int n_solutions = -1;
    int choice = '\0';

    do {
        input_square_koef(&a, &b, &c);
        n_solutions = square_solver(a, b, c, &x1, &x2);
        minus_zero_check(&x1);
        minus_zero_check(&x2);
        if(!output_square_solver_result(n_solutions, x1, x2)) //TODO: stuct input/output
            return -1;

        // repeat?
        printf("\n🔄 Хотите решить еще одно уравнение (Y/n)? ");
        do {
            choice = getchar();
        }
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '\n');
    }
    while (choice == 'Y' || choice == 'y')
        ;

    return 0;
}

int square_solver(double a, double b, double c,
                    double *x1, double *x2) {

    assert(!isnan(a) && !isinf(a));
    assert(!isnan(b) && !isinf(b));
    assert(!isnan(c) && !isinf(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (!is_zero(a)) {
        double d = b * b - 4 * a * c;

        if (d > 0) {
            double sqrt_d = sqrt(d);
            *x1 = ( -b + sqrt_d) / (2*a);
            *x2 = ( -b - sqrt_d) / (2*a);
            return 2;
        }
        else if (is_zero(d)) {
            *x1 = *x2 = -b / (2*a);
            return 1;
        }
        else { //if (d < 0)
            return 0;
        }
    }
    else if (!is_zero(b)) {
        *x1 = *x2 = -c / b;
        return 1;
    }
    else if (!is_zero(c)) {
        return 0;
    }
    else { // a = 0  b = 0  c = 0
        return SS_INF_SOLUTIONS;
    }
}
