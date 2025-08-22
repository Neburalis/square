const double MIN_TOLERANCE = 0.0001; // 1E-6

int clear_stdin_buffer(){
    while (getchar() != '\n')
        continue;
    return 1;
}

double safe_get_double(char var_name) {
    int scanf_status = -1;
    double var = NAN;
    for (;;) {
        printf("%c = ", var_name);
        scanf_status = scanf("%lg", &var);
        clear_stdin_buffer();
        if (scanf_status && !isinf(var))
            return var;
        printf("😢 Вы ввели число, которое я не смог распознать. "
               "Попробуйте ввести правильное число (например 12.34). "
               "Десятичный разделитель точка (.).\n");
    }
}

int is_zero(double a) {
    if (fabs(a) < MIN_TOLERANCE)
        return 1;
    return 0;
}

// -------
//!
//! Func to compare real numbers.
//! if compare_double < 0 => a < b
//! if compare_double == 0 => a == b (Taking into account tolerance MIN_TOLERANCE)
//! if compare_double > 0 => a > b
//!
// ----
int compare_double(double a, double b) {
    assert(!isnan(a) && !isnan(b));

    if (fabs(a - b) < MIN_TOLERANCE)
        return 0;
    else if (a > b)
        return 1;
    // else if (b < a)
    return -1;
}

int minus_zero_check(double *variable) {
    if (is_zero(*variable)){
        *variable = 0;
        return 1;
    }
    return -1;
}
