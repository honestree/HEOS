.PHONY: clean all
all: MatrixControl.o HEOS

MatrixControl.o: MatrixControl.hpp MatrixControl.cpp
	g++ -c MatrixControl.hpp MatrixControl.cpp -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lGLEW

HEOS: main.cpp loadShader.cpp MatrixControl.o
	g++ main.cpp loadShader.cpp MatrixControl.o -o HEOS -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lGLEW

clean:
	rm -rf *.o *.gch HEOS

