#include <stdio.h>
#include <math.h>

#define MIN_VALUE 0.0001

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

bool is_zero(double a){
    if (fabs(a) < MIN_VALUE) return true;
    else return false;
}

int main(){
    start:
    // ax^2 + bx + c = 0
    double a = 0, b = 0, c = 0;

    printf("🧮 Программа для решения квадратного уравнения ax^2 + bx + c = 0\n");
    printf("📝 Введите коэффициенты a, b и c каждый в новой строке.\n");
    a = safe_get_double('a');
    b = safe_get_double('b');
    c = safe_get_double('c');

    printf("📊 %lgx^2 + %lgx + %lgc = 0\n", a, b, c);

    if (!is_zero(a)){
        double d = b * b - 4 * a * c;

        printf("🔍 d = %lg\n", d);

        if (d > 0){
            double x1 = (-b + sqrt(d))/(2*a);
            double x2 = (-b - sqrt(d))/(2*a);
            printf("✅ two solutions:\n"
                "x1 = %lg\n"
                "x2 = %lg\n", x1, x2);
        }
        else if (is_zero(d)){
            double x = (-b)/(2*a);
            printf("🎯 one solution:\n"
                "x = %lg", x);
        }
        else if (d < 0){
            printf("❌ no solutions");
        }
    }
    else if (!is_zero(b)){

        double x = -(c / b);
        printf("🎯 one solution:\n"
            "x = %lg", x);
    }
    else {
        printf("❌ no solutions");
    }

    int choice;
    printf("\n🔄 Хотите решить еще одно уравнение? (Y/n)");
    choice = getchar();
    if (choice == 'Y' || choice == 'y') goto start;

    return 0;
}
