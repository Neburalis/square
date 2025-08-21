#include <stdio.h>
#include <math.h>

int main(){
    // ax^2 + bx + c = 0
    float a, b, c;

    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);

    printf("%fx^2 + %fx + %fc = 0\n", a, b, c);

    float d = b * b - 4 * a * c;

    printf("d = %f\n", d);

    if (d > 0){
        float x1 = (-b + sqrt(d))/(2*a);
        float x2 = (-b - sqrt(d))/(2*a);
        printf("two solutions:\nx1 = %f\nx2 = %f\n", x1, x2);
    }
    else if (d == 0){
        float x = (-b)/(2*a);
        printf("one solution:\nx = %f", x);
    }
    else if (d < 0){
        printf("no solutions");
    }

}
