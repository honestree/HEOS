.PHONY: clean all

CXX = g++
GL_FLAG = -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lGLEW
ModelDemonstrator_O = MatrixControl.o loadShader.o ModelDemonstrator.o ModelLoader.o
ModelGenerator_O = ModelGenerator.o
ProbabilityFormer_O = Polynomial.o WaveFunc.o

LIBARY_O = ${ModelDemonstrator_O} ${ModelGenerator_O} ${ProbabilityFormer_O}

all: ${LIBARY_O} HEOS

Polynomial.o: ProbabilityFormer/Polynomial.cpp ProbabilityFormer/Polynomial.hpp
	${CXX} -c ProbabilityFormer/Polynomial.cpp

WaveFunc.o: ProbabilityFormer/WaveFunc.cpp ProbabilityFormer/WaveFunc.hpp
	${CXX} -c ProbabilityFormer/WaveFunc.cpp

MatrixControl.o: ModelDemonstrator/MatrixControl.hpp ModelDemonstrator/MatrixControl.cpp
	${CXX} -c ModelDemonstrator/MatrixControl.cpp

loadShader.o: ModelDemonstrator/loadShader.cpp ModelDemonstrator/loadShader.hpp
	${CXX} -c ModelDemonstrator/loadShader.cpp

ModelDemonstrator.o: ModelDemonstrator/ModelDemonstrator.cpp ModelDemonstrator/ModelDemonstrator.hpp
	${CXX} -c ModelDemonstrator/ModelDemonstrator.cpp

ModelLoader.o: ModelDemonstrator/ModelLoader.cpp ModelDemonstrator/ModelLoader.hpp
	${CXX} -c ModelDemonstrator/ModelLoader.cpp

ModelGenerator.o: ModelGenerator/ModelGenerator.cpp ModelGenerator/ModelGenerator.hpp
	${CXX} -c ModelGenerator/ModelGenerator.cpp

HEOS: main.cpp ${LIBARY_O}
	${CXX} main.cpp ${LIBARY_O} -o HEOS ${GL_FLAG}

clean:
	rm -rf *.o */*.gch HEOS model.ply

