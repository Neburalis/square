#include <stdio.h>
#include <math.h>

#define min_value 0.001

int main(){
    // ax^2 + bx + c = 0
    double a, b, c;

    printf("Программа для решения квадратного уравнения ax^2 + bx + c = 0\n");
    printf("Введите коэффициенты a, b и c каждый в новой строке.\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);

    printf("%lfx^2 + %lfx + %lfc = 0\n", a, b, c);

    if (fabs(a) > min_value){
        double d = b * b - 4 * a * c;

        printf("d = %lf\n", d);

        if (d > 0){
            double x1 = (-b + sqrt(d))/(2*a);
            double x2 = (-b - sqrt(d))/(2*a);
            printf("two solutions:\n"
                "x1 = %lf\n"
                "x2 = %lf\n", x1, x2);
        }
        else if (fabs(d) < min_value){
            double x = (-b)/(2*a);
            printf("one solution:\n"
                "x = %lf", x);
        }
        else if (d < 0){
            printf("no solutions");
        }
    }
    else {
        double x = -(c / b);
        printf("one solution:\n"
            "x = %lf", x);
    }
}
