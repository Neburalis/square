#ifndef IO_UTILS_H
#define IO_UTILS_H

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
