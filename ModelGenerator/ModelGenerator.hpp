#pragma once
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Model_element{
    
    float r;
    float theta;
    float phi;
    float size;
    
};


void ModelGenerator( char* output_file, std::vector<Model_element> model_element );

void AddTetrahedron( Model_element pos, std::vector<glm::vec3> &vertexs, std::vector<glm::vec3> &colors, std::vector<glm::uvec3> &faces);