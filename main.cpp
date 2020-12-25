#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include "ModelDemonstrator/ModelDemonstrator.hpp"
#include "ModelGenerator/ModelGenerator.hpp"
#include "ProbabilityFormer/WaveFunc.hpp"

int main( int argc , char* argv[] ){
    
    if( argc != 4 ){
        std::cout<< "./HEOS N L M " << std::endl;
        return -1;
    }
    WaveFunc WF1( atoi( argv[1] ), atoi( argv[2] ), atoi( argv[3] ) );
    std::default_random_engine generator;
    std::uniform_real_distribution<double> rand_dev(-0.08,0.08);
    std::vector<Model_element> model_element;
    char const *filename = "model.ply";
    
    std::cout << "start model" << std::endl;

    for( float r = 0 ; r < 200 ; r+= ( 0.1 + rand_dev( generator ) )){
        for( float theta = 0; theta < 2 * M_PI; theta += (0.1 + rand_dev( generator )) ){
            for( float phi = 0; phi < 2 * M_PI; phi += (0.1+ rand_dev( generator )) ){
                model_element.push_back( 
                    Model_element{
                        r,
                        theta,
                        phi,
                        WF1.probability( r * 4e-10, theta , phi )
                    }
                );
            }
        }
    }
    
    std::cout << "vector finished" << std::endl;
    
    ModelGenerator( filename , model_element );

    ModelDemonstrator();
}
