.PHONY: clean all test

CXX = g++
ModelGenerator_O = ModelGenerator.o

all: ${ModelGenerator_O}

ModelGenerator.o: ModelGenerator.cpp ModelGenerator.hpp
	${CXX} -c ModelGenerator.cpp

test: ProbabilityFormer_unitest.cpp ${ProbabilityFormer_O}
	${CXX} ProbabilityFormer_unitest.cpp ${ProbabilityFormer_O} -o test ${GTEST_FLAG}
	./test

clean:
	rm -rf *.o */*.gch test

