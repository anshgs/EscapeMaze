CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec


bin/exec: src/main.cc includes/my_functions.hpp src/my_functions.cc
	${CXX} ${CXX_FLAGS} src/main.cc src/my_functions.cc -o bin/exec



.DEFAULT_GOAL := exec


clean:
	rm -rf bin/*
