CXX = g++
CXXFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr\
			-Iio_utils -Imath_equation_solver -Ireal_number_utils -Isquare

TARGET = a.out
SOURCES = main.cpp real_number_utils/real_number_utils.cpp real_number_utils/real_number_utils_tests.cpp io_utils/io_utils.cpp square/square.cpp square/square_tests.cpp math_equation_solver/math_equation_solver.cpp math_equation_solver/math_equation_solver_tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = real_number_utils/real_number_utils.h real_number_utils/real_number_utils_tests.h io_utils/io_utils.h square/square.h square/square_tests.h math_equation_solver/math_equation_solver.h math_equation_solver/math_equation_solver_tests.h

# Основная цель
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(TARGET)

# Объектные файлы
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

real_number_utils.o: real_number_utils.cpp real_number_utils.h
	$(CXX) $(CXXFLAGS) -c real_number_utils.cpp -o real_number_utils.o

io_utils.o: io_utils.cpp io_utils.h
	$(CXX) $(CXXFLAGS) -c io_utils.cpp -o io_utils.o

square.o: square.cpp square.h
	$(CXX) $(CXXFLAGS) -c square.cpp -o square.o

math_equation_solver.o: math_equation_solver.cpp math_equation_solver.h
	$(CXX) $(CXXFLAGS) -c math_equation_solver.cpp -o math_equation_solver.o


.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(TARGET).dSYM
