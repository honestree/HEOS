#include "ModelLoader.hpp"
#include <iostream>
#include <fstream>
#include <string>

struct Header{

    std::string name;
    unsigned int size;
    std::vector<std::string> property_array;
    bool is_property_list = false;
};


// ModelLoader would read **ascii ply file** and put vertex in out_vertex by the order of ply/face

int ModelLoader( const char* filename, std::vector<GLfloat> &out_vertex, std::vector<GLfloat> &out_color){

    //load ply object
    std::ifstream fp;
    std::string tmp;
    fp.open( filename , std::ifstream::in);
    if( !fp.is_open() ){
        std::cout << "Error opening file\n";
        return -1;
    }

    //check if it is ply w/ ascii    
    if(  fp >> tmp && tmp !=  std::string( "ply" ) ){
        std::cout << "File format unsupported\n";
        return -1;  
    }
    while( getline( fp, tmp ) && tmp == std::string( "" )){}
    if( tmp !=  std::string( "format ascii 1.0" ) ){
        std::cout << "ply not coded in ASCII is not supported yet\n";
        std::cout << "get this:" << tmp << std::endl;

        return -1;  
    }

    //Read header
    std::vector<Header> HeaderList;
    for( unsigned int index = -1; fp >> tmp && tmp != std::string( "end_header" ); ){              

        if( tmp == std::string( "comment" ) ){
            //discard comments
            getline( fp, tmp );
        }
        else if( tmp == std::string( "element" )){
            ++index;
            HeaderList.push_back( Header() );
 
            fp >> HeaderList[index].name;
            fp >> HeaderList[index].size;
        }
        else if( tmp == std::string( "property" )){
            fp >> tmp;
            if( tmp != std::string( "list" ) ){
                HeaderList[index].property_array.push_back(tmp);
                getline( fp, tmp );
            }
            else{
                HeaderList[index].is_property_list = true;
                fp >> tmp;
                HeaderList[index].property_array.push_back(tmp);
                fp >> tmp;
                HeaderList[index].property_array.push_back(tmp);
                getline( fp, tmp );
            }
        }        
    }
 
    //Read file
    std::vector<std::pair<glm::vec3,glm::vec3>> vertex_list;

    for( unsigned int i = 0 ; i < HeaderList.size(); ++i ){
        for( unsigned int j = 0 ; j < HeaderList[i].size; ++j  ){
            if( HeaderList[i].is_property_list == false ){
                if( HeaderList[i].name == std::string( "vertex" ) ){
                    if( HeaderList[i].property_array.size() != 6 ){
                        std::cout << "missing color on vertex\n";
                        return -1;
                    }
                    GLfloat tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
                    fp >> tmp1; fp >> tmp2; fp >> tmp3;
                    fp >> tmp4; fp >> tmp5; fp >> tmp6;
                    vertex_list.push_back(
                        std::pair<glm::vec3,glm::vec3>(
                            glm::vec3( tmp1, tmp2, tmp3 ),
                            glm::vec3( tmp4, tmp5, tmp6 )
                        )
                    );                      
                }
            }
            else if( HeaderList[i].name == std::string( "face" ) ){
                unsigned int trifan_size;
                fp >> trifan_size;
                std::vector<int> tri_array;
                int tmp;
                for( unsigned int i = 0 ; i < trifan_size; ++i ){
                    fp >> tmp;
                    tri_array.push_back( tmp );
                }
                for( unsigned int m = 0; m < trifan_size - 2 ; m++ ){
                    out_vertex.push_back( vertex_list[ tri_array[ 0 ]].first.x );
                    out_vertex.push_back( vertex_list[ tri_array[ 0 ]].first.y );
                    out_vertex.push_back( vertex_list[ tri_array[ 0 ]].first.z );
                    out_color.push_back( vertex_list[ tri_array[ 0 ]].second.x );
                    out_color.push_back( vertex_list[ tri_array[ 0 ]].second.y );
                    out_color.push_back( vertex_list[ tri_array[ 0 ]].second.z );                        
                    out_vertex.push_back( vertex_list[ tri_array[ m + 1 ]].first.x );
                    out_vertex.push_back( vertex_list[ tri_array[ m + 1 ]].first.y );
                    out_vertex.push_back( vertex_list[ tri_array[ m + 1 ]].first.z );
                    out_color.push_back( vertex_list[ tri_array[ m + 1 ]].second.x );
                    out_color.push_back( vertex_list[ tri_array[ m + 1 ]].second.y );
                    out_color.push_back( vertex_list[ tri_array[ m + 1 ]].second.z );
                    out_vertex.push_back( vertex_list[ tri_array[ m + 2 ]].first.x );
                    out_vertex.push_back( vertex_list[ tri_array[ m + 2 ]].first.y );
                    out_vertex.push_back( vertex_list[ tri_array[ m + 2 ]].first.z );
                    out_color.push_back( vertex_list[ tri_array[ m + 2 ]].second.x );
                    out_color.push_back( vertex_list[ tri_array[ m + 2 ]].second.y );
                    out_color.push_back( vertex_list[ tri_array[ m + 2 ]].second.z );
                }
            }
            //ignore unwanted
            else{
                for( unsigned int k = 0 ; k < HeaderList[i].property_array.size(); ++k ){
                    fp >> tmp;
                }
            }
            
        }
    }  
    return 0;
}