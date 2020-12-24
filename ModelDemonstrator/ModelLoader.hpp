#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

int ModelLoader( char* filename, std::vector<GLfloat> &out_vertex, std::vector<GLfloat> &out_color);
