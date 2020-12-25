#include "ModelGenerator.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>

void ModelGenerator( char* output_file, std::vector<Model_element> model_element ){
    std::ofstream fp;
    fp.open( output_file );

    std::vector<glm::vec3> vertexs;
    std::vector<glm::vec3> colors;
    std::vector<glm::uvec3> faces;
    for( unsigned int i = 0 ; i < model_element.size(); i++ ){
        AddTetrahedron( model_element[ i ], vertexs, colors, faces );
    }

    fp << "ply\nformat ascii 1.0\n";
    fp << "element vertex "<< vertexs.size() << "\n";
    fp << "property float x\nproperty float y\nproperty float z\n";
    fp << "property float r\nproperty float g\nproperty float b\n";
    fp << "element face " << faces.size() << "\n";
    fp << "property list uchar int vertex_index\nend_header\n";
    for( unsigned int i = 0 ; i < vertexs.size(); i++ ){
        fp << vertexs[i].x << " " << vertexs[i].y << " " << vertexs[i].z << " ";
        fp << colors[i].x << " " << colors[i].y << " " << colors[i].z << "\n";
    }
    for( unsigned int i = 0 ; i < faces.size(); i++ ){
        
        fp << "3 " << faces[i].x << " " << faces[i].y << " " << faces[i].z << "\n";
    }

    fp.close();
    return;
}

void AddTetrahedron( Model_element pos,
                     std::vector<glm::vec3> &vertexs,
                     std::vector<glm::vec3> &colors, 
                     std::vector<glm::uvec3> &faces
                    ){

    glm::vec3 reg_tetra1( 0.5 , 0 , -0.5 / sqrt(2) );
    glm::vec3 reg_tetra2( -0.5 , 0 , -0.5 / sqrt(2) );
    glm::vec3 reg_tetra3( 0 , -0.5 , 0.5 / sqrt(2) );
    glm::vec3 reg_tetra4( 0 , 0.5 , 0.5 / sqrt(2) );
    glm::vec3 ver_color( 1 , 1 , 0 );
    glm::vec3 central_p ( 
        pos.r * sin( pos.theta ) * cos( pos.phi ),
        pos.r * sin( pos.theta ) * sin( pos.phi ),
        pos.r * cos( pos.theta )
    );
    unsigned vector_size = vertexs.size();

    reg_tetra1 = central_p + reg_tetra1 * pos.size;
    reg_tetra2 = central_p + reg_tetra2 * pos.size;
    reg_tetra3 = central_p + reg_tetra3 * pos.size;
    reg_tetra4 = central_p + reg_tetra4 * pos.size;
    ver_color *= std::min( (float) 1 , pos.size/10 );
    
    vertexs.push_back( reg_tetra1 );
    vertexs.push_back( reg_tetra2 );
    vertexs.push_back( reg_tetra3 );
    vertexs.push_back( reg_tetra4 );
    colors.push_back( ver_color );
    colors.push_back( ver_color );
    colors.push_back( ver_color );
    colors.push_back( ver_color );
    
    faces.push_back( glm::uvec3( vector_size, vector_size+1, vector_size+2 ));
    faces.push_back( glm::uvec3( vector_size+3, vector_size+1, vector_size+2 ));
    faces.push_back( glm::uvec3( vector_size+3, vector_size, vector_size+2 ));
    faces.push_back( glm::uvec3( vector_size+3, vector_size, vector_size+1 ));

    return;
}