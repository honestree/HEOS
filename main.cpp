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
    std::uniform_real_distribution<double> rand_dev(-15,15);
    std::vector<struct ModelElement> modelElements;
    char const *filename = "model69.ply";

    unsigned int rounds = 300000;
    
    std::cout << "Creating Model..." << std::endl;

    std::cout << "Calculating probability" << std::endl;

    for( unsigned int i = 0 ; i < rounds ; ++i ){
        double x = rand_dev( generator );
        double y = rand_dev( generator );
        double z = rand_dev( generator );
        double r = sqrt( x * x + y * y + z * z  );
        
        if( x * y * z != 0 ){    
            struct ModelElement tmp{
                (float) r,
                (float) acos( z/r ),
                (float) atan2( y, x ),
                WF1.probability( r * 1e-10, acos( z / r ) , atan2( y,x ) )
            };    
            if( tmp.probability > 10 ){
                modelElements.push_back( tmp );
            }
        }
    }

    std::cout << "Sorting element" << std::endl;
    std::sort( modelElements.begin(), modelElements.end(), ModelCmp);
    
    std::cout << "Creating Model with "<< modelElements.size() << " vertices"  << std::endl;
    ModelGenerator modelGenerator;
    modelGenerator.AddModelElements( modelElements );
    modelGenerator.MakeModel( filename );
    
    ModelDemonstrator( filename );
}
