#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MIN_VALUE 0.0001
#define NDEBUG
#define INF_SOLUTIONS -1

double safe_get_double(char var) {
    int result = 0;
    double a = NAN;
    for (;;) {
        printf("%c = ", var);
        result = scanf("%lg", &a);
        while (getchar() != '\n')
            continue;
        if (result)
            return a;
        printf("😢 Вы ввели число, которое я не смог распознать. Попробуйте ввести правильное число (например 12.34). Десятичный разделитель точка (.).\n");
    }
}
//TODO: compare_double(a, b)
bool is_zero(double a){
    if (fabs(a) < MIN_VALUE)
        return true;
    else
        return false;
}

// 0.1 + 0.2 != 0.3

int square_solver(double a, double b, double c,
                    double *x1, double *x2){

    assert(x1 != NULL); //TODO: assert(!isnan(a) && ...)
    assert(x2 != NULL);
    assert(x1 != x2);

    if (!is_zero(a)) {
        double d = b * b - 4 * a * c;

        if (d > 0) {
            *x1 = (-b + sqrt(d))/(2*a);
            *x2 = (-b - sqrt(d))/(2*a);
            return 2;
        }
        else if (is_zero(d)) {
            *x1 = *x2 = (-b)/(2*a);
            return 1;
        }
        else{ //if (d < 0)
            return 0;
        }
    }
    else if (!is_zero(b)){ //TODO: -0
        *x1 = *x2 = -(c / b);
        return 1;
    }
    else if (!is_zero(c)){
        return 0;
    }
    else{ // a = 0  b = 0  c = 0
        return INF_SOLUTIONS;
    }
}

int main(){
    start:
    // ax^2 + bx + c = 0
    double a = 0, b = 0, c = 0; //TODO:
    double x1 = 0, x2 = 0;
    int n_solutions = 0;

    printf("🧮 Программа для решения квадратного уравнения ax^2 + bx + c = 0\n");
    printf("📝 Введите коэффициенты a, b и c каждый в новой строке.\n");
    a = safe_get_double('a');
    b = safe_get_double('b');
    c = safe_get_double('c');

    printf("📊 %lgx^2 + %lgx + %lgc = 0\n", a, b, c);

    n_solutions = square_solver(a, b, c, &x1, &x2);

    switch (n_solutions) {
        case 2:
            printf("Two solutions:\n"
                   "x1 = %lg\tx2 = %lg", x1, x2);
            break;
        case 1:
            printf("One solution:\n"
                   "x1 = %lg", x1);
            break;
        case 0:
            printf("No solutions");
            break;
        case INF_SOLUTIONS:
            printf("INF solutions");
            break;
        default:
            printf("ERROR: unexpected value in n_solutions, n_solutions = %d", n_solutions);
            return -1;
    }

    int choice;
    printf("\n🔄 Хотите решить еще одно уравнение? (Y/n)");
    choice = getchar();
    if (choice == 'Y' || choice == 'y') goto start;

    return 0;
}


/* TODO:
int main() {
    do {
        //input
        //solve
        //output
    } while();
}
*/
