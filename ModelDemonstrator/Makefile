.PHONY: clean all

CXX = g++
GL_FLAG = -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lGLEW
ModelDemonstrator_O = MatrixControl.o loadShader.o ModelDemonstrator.o ModelLoader.o

LIBARY_O = ${ModelDemonstrator_O}


all: ${LIBARY_O}

MatrixControl.o: MatrixControl.hpp MatrixControl.cpp
	${CXX} -c MatrixControl.cpp

loadShader.o: loadShader.cpp loadShader.hpp
	${CXX} -c loadShader.cpp

ModelDemontrator.o: ModelDemonstrator.cpp ModelDemonstrator.hpp
	${CXX} -c ModelDemonstrator.cpp

ModelLoader.o: ModelLoader.cpp ModelLoader.hpp
	${CXX} -c ModelLoader.cpp

clean:
	rm -rf *.o */*.gch 

