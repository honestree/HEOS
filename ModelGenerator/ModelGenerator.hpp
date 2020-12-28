#pragma once
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "ModelElement.hpp"

class ModelGenerator{

    public:

        ModelGenerator(){}
        ModelGenerator( double max, double min, double distance ):max(max),min(min){
            pFocus = ( log10(max) + log10(min))/2;
            pVar = (log10(max) - log10(min))/2;
            size = (float) distance * 0.005;
        }
        ~ModelGenerator(){}
        int AddModelElements( std::vector<struct ModelElement> modelElements );
        int MakeModel(const char* output_file);

    private:
    
        int addTetrahedron( struct ModelElement model );
        
        // decide probability rander range
        double max = 1e+27;
        double min = 1e+25;
        double pFocus = 26.0;
        double pVar = 1.0;
        float size = 0.1; 
        
        glm::vec3 visualColor( float index );
        std::vector<glm::vec3> vertexs;
        std::vector<glm::vec3> colors;
        std::vector<glm::uvec3> faces;
};