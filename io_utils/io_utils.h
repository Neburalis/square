#ifndef IO_UTILS_H
#define IO_UTILS_H

int clear_stdin_buffer();
int is_stdin_buffer_clean();
double safe_get_double(const char * const var_name);
int is_user_want_continue(const char * const ask_message);

#endif // IO_UTILS_H
