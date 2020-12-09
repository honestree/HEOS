.PHONY: clean all

CXX = g++
GL_FLAG = -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lGLEW
ModelDemonstrator_O = MatrixControl.o loadShader.o

LIBARY_O = ${ModelDemonstrator_O}


all: ${LIBARY_O} HEOS

MatrixControl.o: ModelDemonstrator/MatrixControl.hpp ModelDemonstrator/MatrixControl.cpp
	${CXX} -c ModelDemonstrator/MatrixControl.cpp ${GL_FLAG}

loadShader.o: ModelDemonstrator/loadShader.cpp ModelDemonstrator/loadShader.hpp
	${CXX} -c ModelDemonstrator/loadShader.cpp ${GL_FLAG}

HEOS: main.cpp ${LIBARY_O}
	${CXX} main.cpp ${LIBARY_O} -o HEOS ${GL_FLAG}

clean:
	rm -rf *.o */*.gch HEOS 

