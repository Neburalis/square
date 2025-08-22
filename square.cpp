#include <stdio.h>
#include <math.h>

#define min_value 0.0001

double safe_get_double(char var){
    int result;
    double a;
    for (;;){
        printf("%c = ", var);
        result = scanf("%lf", &a);
        while (getchar() != '\n');
        if (result) return a;
        printf("😢 Вы ввели число, которое я не смог распознать. Попробуйте ввести правильное число (например 12.34). Десятичный разделитель точка (.).\n");
    }
}

int main(){
    start:
    // ax^2 + bx + c = 0
    double a, b, c;

    printf("🧮 Программа для решения квадратного уравнения ax^2 + bx + c = 0\n");
    printf("📝 Введите коэффициенты a, b и c каждый в новой строке.\n");
    a = safe_get_double('a');
    b = safe_get_double('b');
    c = safe_get_double('c');

    printf("📊 %.2lfx^2 + %.2lfx + %.2lfc = 0\n", a, b, c);

    if (fabs(a) > min_value){
        double d = b * b - 4 * a * c;

        printf("🔍 d = %.2lf\n", d);

        if (d > 0){
            double x1 = (-b + sqrt(d))/(2*a);
            double x2 = (-b - sqrt(d))/(2*a);
            printf("✅ two solutions:\n"
                "x1 = %lf\n"
                "x2 = %lf\n", x1, x2);
        }
        else if (fabs(d) < min_value){
            double x = (-b)/(2*a);
            printf("🎯 one solution:\n"
                "x = %lf", x);
        }
        else if (d < 0){
            printf("❌ no solutions");
        }
    }
    else if (fabs(b) > min_value){

        double x = -(c / b);
        printf("🎯 one solution:\n"
            "x = %lf", x);
    }
    else {
        printf("❌ no solutions");
    }

    char choice;
    printf("\n🔄 Хотите решить еще одно уравнение? (Y/n)");
    scanf("%c", &choice);
    if (choice == 'Y' || choice == 'y') goto start;
}
