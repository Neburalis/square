#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "ansi.h"

#define RUNTIME_ERROR_BIG_STRING "\n" \
" .+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+. \n" \
"(      ____  _   _ _   _ _____ ___ __  __ _____   _____ ____  ____   ___  ____        )                     \n" \
" )    |  _ \\| | | | \\ | |_   _|_ _|  \\/  | ____| | ____|  _ \\|  _ \\ / _ \\|  _ \\      (               \n" \
"(     | |_) | | | |  \\| | | |  | || |\\/| |  _|   |  _| | |_) | |_) | | | | |_) |      )                   \n" \
" )    |  _ <| |_| | |\\  | | |  | || |  | | |___  | |___|  _ <|  _ <| |_| |  _ <      (                     \n" \
"(     |_| \\_\\\\___/|_| \\_| |_| |___|_|  |_|_____| |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\      )          \n" \
" )                                                                                   (                      \n" \
"(                                                                                     )                     \n" \
" \"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"+.+\"\n\n"

#define ERROR_MSG(format, ...) \
    fprintf(stderr, RED(RUNTIME_ERROR_BIG_STRING) \
            "In " GREEN("%s:%d") ", " YELLOW("%s") ".\n" format, \
            __FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__);


#define string_t const char * const

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec);

void spinner(string_t str, uint32_t time, uint32_t period);

long long lines_in_file(FILE *fp);
/**
  @brief Функция отчистки буфера ввода
  Считывает данные из потока ввода до \\n (\n также будет считан)

  \code{cpp}
    int a = 0;
    a = getchar();

    clear_stdin_buffer();
    // Теперь буфер чист
  \endcode

  @return int 1 если буфер отчищен
 */
int clear_stdin_buffer();

/**
  @brief Функция проверки чист ли буфер ввода (очищает буфер если он чист)
  Считывает данные из потока ввода до \\n (\n также будет считан)
  Если считывается ' ' или '\t' - то считается что буфер чист
  Если считывается любое другое, считается что буфер не чист


  \code{cpp}
    int a = 0, status = 0;
    a = getchar();

    if (is_stdin_buffer_clean())
        // В буфере были только ' ' и '\t' теперь чист
    else
        // В буфере есть что-то еще, он остался не чист
  \endcode

  @return int 1 если буфер содержал только ' ' или '\t' или уже был чист
  @return int 0 если буфер содержит что-то помимо пустоты
 */
int is_stdin_buffer_clean();
double safe_get_double(const char * const var_name);
int is_user_want_continue(const char * const ask_message);

#endif // IO_UTILS_H
