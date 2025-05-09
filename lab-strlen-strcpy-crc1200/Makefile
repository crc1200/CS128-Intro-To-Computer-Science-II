CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec

bin/exec: ./src/driver.cc ./src/solution.cc
	$(CXX) $(CXXFLAGS) $^ -o $@



.DEFAULT_GOAL := exec


