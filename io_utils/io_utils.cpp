#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "io_utils.h"

int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void spinner(string_t str, uint32_t time, uint32_t period) {
    const char pp[] = {'-', '\\', '|', '/'};
    for (uint32_t i = 0; i < (uint32_t) time/period; ++i) {
        printf("%s", str);
        fflush(stdout);
        printf("%c", pp[i%4]); // - \ | /
        msleep(period);
        printf("\r");
    }
}

size_t lines_in_file(FILE *fp) {
    if (!fp){
        errno = EBADF;
        return 0;
    }

    long long lines = 1;
    int ch = 0;

    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            ++lines;
        }
    }

    if (fseek(fp, 0, SEEK_SET)) {
        errno = EBADF;
        return 0;
    }
    return lines;
}

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
    fflush(stdout);

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
