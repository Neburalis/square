#ifndef MACRO_H
#define MACRO_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define RED(string)        ANSI_COLOR_RED     string ANSI_COLOR_RESET
#define GREEN(string)      ANSI_COLOR_GREEN   string ANSI_COLOR_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW  string ANSI_COLOR_RESET
#define BLUE(string)       ANSI_COLOR_BLUE    string ANSI_COLOR_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA string ANSI_COLOR_RESET
#define CYAN(string)       ANSI_COLOR_CYAN    string ANSI_COLOR_RESET

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

#endif // MACRO_H
