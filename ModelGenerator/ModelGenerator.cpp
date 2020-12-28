#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "ModelGenerator.hpp"

int ModelGenerator::MakeModel(const char* output_file){

    std::ofstream fp;
    fp.open( output_file );

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
    return 0;
}


int ModelGenerator::AddModelElements( std::vector<struct ModelElement> modelElements ){

    for( unsigned int i = 0 ; i < modelElements.size(); i++ ){
        if( modelElements[ i ].probability > min ){
            addTetrahedron( modelElements[ i ] );
        }
    }
    return 0;
   
}
int ModelGenerator::addTetrahedron( struct ModelElement model ){
   
    glm::vec3 reg_tetra1( 1, 0, -1 / sqrt(2.0) );
    glm::vec3 reg_tetra2( -1, 0, -1 / sqrt(2.0) );
    glm::vec3 reg_tetra3( 0, -1, 1 / sqrt(2.0) );
    glm::vec3 reg_tetra4( 0, 1, 1 / sqrt(2.0) );
    glm::vec3 ver_color = visualColor( ( log10( model.probability ) - ( pFocus - pVar ) )/ ( 2 * pVar ));
    glm::vec3 central_p ( 
        model.r * sin( model.theta ) * cos( model.phi ),
        model.r * sin( model.theta ) * sin( model.phi ),
        model.r * cos( model.theta )
    );
    unsigned vector_size = vertexs.size();

    reg_tetra1 = central_p + reg_tetra1 * size;
    reg_tetra2 = central_p + reg_tetra2 * size;
    reg_tetra3 = central_p + reg_tetra3 * size;
    reg_tetra4 = central_p + reg_tetra4 * size;
    
    vertexs.push_back( reg_tetra1 );
    vertexs.push_back( reg_tetra2 );
    vertexs.push_back( reg_tetra3 );
    vertexs.push_back( reg_tetra4 );
    
    colors.push_back( ver_color );
    colors.push_back( ver_color );
    colors.push_back( ver_color );
    colors.push_back( ver_color );

    faces.push_back( glm::uvec3( vector_size, vector_size+2, vector_size+1 ));
    faces.push_back( glm::uvec3( vector_size+1, vector_size+2, vector_size+3 ));
    faces.push_back( glm::uvec3( vector_size+3, vector_size+2, vector_size ));
    faces.push_back( glm::uvec3( vector_size+3, vector_size, vector_size+1 ));

    return 0;
}

glm::vec3 ModelGenerator::visualColor( float index ){

    if( index > 1 ){
        return glm::vec3( 1, 1, 1);
    }
    else if( index < 0 ){
        return glm::vec3( 0, 0, 0);
    }
    glm::vec3 purple(  89.0/255.0,  32.0/255.0, 122.0/255.0 );    //15%
    glm::vec3 red   ( 198.0/255.0,  64.0/255.0,  70.0/255.0 );    //30%
    glm::vec3 orange( 251.0/255.0, 120.0/255.0,  14.0/255.0 );    //50%
    glm::vec3 yellow( 255.0/255.0, 193.0/255.0,  67.0/255.0 );    //72.5%
    glm::vec3 white (           1,           1,           1 );    //100%

    if( index < 0.15 ){
        return purple * ( index / 0.15f );
    }
    else if( index < 0.3){
        return red * (( index - 0.15f )/0.15f) + purple * (( 0.3f - index )/0.15f);
    }
    else if( index < 0.5){
        return orange * (( index - 0.3f )/0.20f) + red * (( 0.5f - index )/0.20f);
    }
    else if( index < 0.725){
        return yellow * (( index - 0.5f )/0.225f) + orange * (( 0.725f - index )/0.225f);
    }
    else{
        return white * (( index - 0.725f )/0.275f) + yellow * (( 1.0f - index )/0.275f);
    }

}
