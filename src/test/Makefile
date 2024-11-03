CC = gcc
CXX = g++
CXXFLAGS = -Wall -g -DGAMEBOY_TEST_DEBUG

TESTS = parser_test.o processor_test.o

SRC = ../parser.cpp ../processor.cpp ../memory.cpp

test: %: %.o ${TESTS} ${SRC}
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o test

clean:
	rm -f *.o test
