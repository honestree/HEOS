.PHONY: clean all test

CXX = g++
ProbabilityFormer_O = Polynomial.o
GTEST_FLAG = -Igtest/include -Lgtest/lib -lgtest -lpthread

all: ${ProbabilityFormer_O} 

Polynomial.o: Polynomial.cpp
	${CXX} -c Polynomial.cpp

test: ProbabilityFormer_unitest.cpp ${ProbabilityFormer_O}
	${CXX} ProbabilityFormer_unitest.cpp ${ProbabilityFormer_O} -o test ${GTEST_FLAG}
	./test

clean:
	rm -rf *.o */*.gch test

