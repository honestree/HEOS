#pragma once
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "ModelElement.hpp"


void ModelGenerator(  const char* output_file, std::vector<ModelElement> model_element );

void AddTetrahedron( ModelElement pos, std::vector<glm::vec3> &vertexs, std::vector<glm::vec3> &colors, std::vector<glm::uvec3> &faces);