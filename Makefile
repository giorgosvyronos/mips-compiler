CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

SRCS = $(wildcard src/ast/*.cpp)
OBJS = $(SRCS:.cpp=.o)



$(OBJS): %.o : %.cpp
	  g++ $(CPPFLAGS) -c $< -o $*.o



src/c_lexer.yy.cpp : src/c_lexer.flex src/c_parser.tab.hpp
		flex -w -o src/c_lexer.yy.cpp src/c_lexer.flex

src/c_parser.tab.cpp : src/c_parser.y
		bison -v -d src/c_parser.y -o src/c_parser.tab.cpp

bin/c_compiler : src/c_lexer.yy.cpp src/c_parser.tab.cpp $(OBJS)
		find src -type f -exec touch {} +
		mkdir -p bin
		g++ $(CPPFLAGS) -o bin/c_compiler $^ src/compiler.cpp

test : bin/c_compiler
		./test_compiler.sh

clean :

		rm -f src/*.o
		rm -f src/ast/*.o
		rm -f src/*.tab.cpp
		rm -f src/*.yy.cpp

		rm -f bin/*
		rm -rf working
