.PHONY: clean all

CXX = g++
GL_FLAG = -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lGLEW
RequestDealer_O = RequestDealer.o

LIBARY_O = ${RequestDealer_O}

all: ${LIBARY_O}

RequestDealer.o: RequestDealer.cpp RequestDealer.hpp
	${CXX} -c RequestDealer.cpp

clean:
	rm -rf *.o */*.gch

