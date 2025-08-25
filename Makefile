UNAME_S := $(shell uname -s)

CXX = g++

# ----- Windows -----
ifneq (,$(findstring NT,$(UNAME_S)))
    CXXFLAGS_OS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
        -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
        -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
        -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op \
        -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo \
        -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla \
        -D_DEBUG -D_EJUDGE_CLIENT_SIDE

    CXXFLAGS_ARCH =
endif

# ----- Linux -----
ifeq ($(UNAME_S), Linux)
    CXXFLAGS_OS = -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
        -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported \
        -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
        -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual \
        -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
        -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods \
        -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef \
        -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers \
        -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation \
        -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 \
        -Wstack-usage=8192 -pie -fPIE -Werror=vla \
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,\
        integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,\
        shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

    CXXFLAGS_ARCH = -pthread
endif

# --- macOS (Darwin) ---
ifeq ($(UNAME_S), Darwin)
    CXXFLAGS_OS = -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations \
        -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
        -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor \
        -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion \
        -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef \
        -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing \
        -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector \
        -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -Werror=vla \
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

    CXXFLAGS_ARCH = -pthread
endif

CXXFLAGS = $(CXXFLAGS_OS) $(CXXFLAGS_ARCH) \
	-Iio_utils -Imath_equation_solver -Ireal_number_utils -Isquare

TARGET = a.out
SOURCES = main.cpp \
	io_utils/io_utils.cpp \
	math_equation_solver/math_equation_solver.cpp \
	math_equation_solver/math_equation_solver_tests.cpp \
	real_number_utils/real_number_utils.cpp \
	real_number_utils/real_number_utils_tests.cpp \
	square/square.cpp \
	square/square_tests.cpp

OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = io_utils/io_utils.h \
	macro.h \
	math_equation_solver/math_equation_solver.h \
	math_equation_solver/math_equation_solver_tests.h \
	real_number_utils/real_number_utils.h \
	real_number_utils/real_number_utils_tests.h \
	square/square.h \
	square/square_tests.h

# --- Цель сборки ---
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(TARGET)

# --- Компиляция: .cpp → .o ---
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Очистка ---
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(TARGET).dSYM
