#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "io_utils.h"

int clear_stdin_buffer() {
    while (getchar() != '\n')
        continue;
    return 1;
}

int is_stdin_buffer_clean() {
    int c = 0;
    while ((c = getchar()) != '\n') {
        if (c == ' ' || c == '\t')
            continue;
        return 0;
    }
    return 1;
}

double safe_get_double(const char * const var_name) {
    assert(var_name != NULL);

    int scanf_status = 0;
    double var = NAN;
    for (;;) {
        printf("%s", var_name);
        scanf_status = scanf("%lg", &var);
        if (scanf_status && !isinf(var) && isfinite(var) && is_stdin_buffer_clean())
            return var;
        clear_stdin_buffer();
        printf("😢 Вы ввели число, которое я не смог распознать.     "
               "Попробуйте ввести правильное число (например 12.34). "
               "Десятичный разделитель точка (.).\n                  ");
    }
}

int is_user_want_continue(const char * const ask_message) {
    int choice = 0;

    printf("%s", ask_message);

    do {
        choice = getchar();
    }
    while (choice != 'y' &&
           choice != 'Y' &&
           choice != 'n' &&
           choice != 'N' &&
           choice != '\n');

    if (choice == 'Y' || choice == 'y')
        return 1;
    return 0;
}
