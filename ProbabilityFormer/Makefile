.PHONY: clean all test

CXX = g++
ProbabilityFormer_O = Polynomial.o WaveFunc.o
GTEST_FLAG = -Igtest/include -Lgtest/lib -lgtest -lpthread

all: ${ProbabilityFormer_O}

Polynomial.o: Polynomial.cpp Polynomial.hpp
	${CXX} -c Polynomial.cpp

WaveFunc.o: WaveFunc.cpp WaveFunc.hpp
	${CXX} -c WaveFunc.cpp

test: ProbabilityFormer_unitest.cpp ${ProbabilityFormer_O}
	${CXX} ProbabilityFormer_unitest.cpp ${ProbabilityFormer_O} -o test ${GTEST_FLAG}
	./test

clean:
	rm -rf *.o */*.gch test

