#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "real_number_utils.c"

const int SS_INF_SOLUTIONS = -1;

enum ss_status {
    INF = -1,
    NO = 0,
    ONE = 1,
    TWO = 2,
    NOT_SOLVE = -2,
    NOT_INPUT = -3
};

struct square_equation {
    enum ss_status status;
    double kf_a;
    double kf_b;
    double kf_c;
    double ans1;
    double ans2;
};

int square_solver(struct square_equation *eq) {
    assert(eq != NULL);

    double a = eq->kf_a, b = eq->kf_b, c = eq->kf_c;

    if (!is_zero(a)) {
        double d = b * b - 4 * a * c;

        if (d > 0) {
            double sqrt_d = sqrt(d);
            eq->ans1 = ( -b + sqrt_d) / (2*a);
            eq->ans2 = ( -b - sqrt_d) / (2*a);
            eq->status = TWO;
            return 2;
        }
        else if (is_zero(d)) {
            eq->ans1 = eq->ans2 = -b / (2*a);
            eq->status = ONE;
            return 1;
        }
        else { //if (d < 0)
            eq->status = NO;
            return 0;
        }
    }
    else if (!is_zero(b)) {
        eq->ans1 = eq->ans2 = -c / b;
        eq->status = ONE;
        return 1;
    }
    else if (!is_zero(c)) {
        eq->status = NO;
        return 0;
    }
    else { // a = 0  b = 0  c = 0
        eq->status = INF;
        return SS_INF_SOLUTIONS;
    }
}

void input_square_koef(struct square_equation *eq) {
    assert(eq != NULL);
    printf("🧮 Программа для решения квадратного уравнения ax^2 + bx + c = 0\n"
           "📝 Введите коэффициенты a, b и c каждый в новой строке.\n");
    eq->kf_a = safe_get_double('a');
    eq->kf_b = safe_get_double('b');
    eq->kf_c = safe_get_double('c');

    eq->status = NOT_SOLVE;

    printf("📊 Буду решать уравнение: %lgx^2 + %lgx + %lgc = 0\n", eq->kf_a, eq->kf_b, eq->kf_c);
    return;
}

int output_square_solver_result(struct square_equation *eq) {
    switch (eq->status) {
        case TWO:
            printf("Two solutions:\n"
                   "x1 = %lg\tx2 = %lg", eq->ans1, eq->ans2);
            break;
        case ONE:
            printf("One solution:\n"
                   "x = %lg", eq->ans1);
            break;
        case NO:
            printf("No solutions");
            break;
        case INF:
            printf("INF solutions");
            break;
        default:
            printf("ERROR: unexpected value in n_solutions, n_solutions = %d", eq->status);
            return 0;
    }
    return 1;
}

int main(){
    int choice = '\0';

    do {
        struct square_equation eq = {.status=NOT_INPUT, .kf_a=NAN, .kf_b=NAN, .kf_c=NAN, .ans1=NAN, .ans2=NAN};

        input_square_koef(&eq);
        square_solver(&eq);
        minus_zero_check(&eq.ans1);
        minus_zero_check(&eq.ans2);
        if(!output_square_solver_result(&eq)) //TODO: stuct input/output
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
