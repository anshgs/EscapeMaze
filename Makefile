CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec


bin/exec: src/main.cc src/ai.cc src/item.cc src/user.cc src/game.cc includes/ai.hpp includes/item.hpp includes/user.hpp includes/game.hpp
	${CXX} ${CXX_FLAGS} src/main.cc src/ai.cc  -o bin/exec


.DEFAULT_GOAL := exec


clean:
	rm -rf bin/*
