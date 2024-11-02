CC = gcc
CXX = g++
CXXFLAGS = -Wall -g -DGAMEBOY_TEST_DEBUG

TESTS = parser_test.o processor_test.o

SRC = ../parser.cpp ../processor.cpp  ../fetcher.cpp

test: %: %.o ${TESTS} ${SRC}
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o test
	./test

clean:
	rm -f *.o test
