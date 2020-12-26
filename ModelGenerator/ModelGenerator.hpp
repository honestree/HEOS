#pragma once
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "ModelElement.hpp"

class ModelGenerator{

    public:

        ModelGenerator(){}
        ~ModelGenerator(){}
        int AddModelElements( std::vector<struct ModelElement> modelElements );
        int MakeModel(const char* output_file);

    private:
    
        int addTetrahedron( struct ModelElement model );
        glm::vec3 visualColor( float index );
        std::vector<glm::vec3> vertexs;
        std::vector<glm::vec3> colors;
        std::vector<glm::uvec3> faces;
};