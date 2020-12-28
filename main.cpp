#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include "ModelDemonstrator/ModelDemonstrator.hpp"
#include "ModelGenerator/ModelGenerator.hpp"
#include "ProbabilityFormer/WaveFunc.hpp"

int main( int argc , char* argv[] ){
    
    unsigned int rounds = 1000000;
    double renderRange = 30;
    double renderPMax = 1e27;
    double renderPMin = 1e25;
    std::vector<struct ModelElement> modelElements;
    char const *filename = "model.ply";
  
    if( argc != 4 ){
        std::cout<< "./HEOS N L M " << std::endl;
        return -1;
    }    

    std::cout << "Calculating probability" << std::endl;
    
    WaveFunc WF1( atoi( argv[1] ), atoi( argv[2] ), atoi( argv[3] ) );
    std::default_random_engine generator;
    std::uniform_real_distribution<double> rand_dev(renderRange * -1 , renderRange);
    for( unsigned int i = 0 ; i < rounds ; ++i ){
        double x = rand_dev( generator );
        double y = rand_dev( generator );
        double z = rand_dev( generator );
        double r = sqrt( x * x + y * y + z * z );
        
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
    ModelGenerator modelGenerator( renderPMax , renderPMin, renderRange );
    modelGenerator.AddModelElements( modelElements );

    std::cout << "Loading Model with "<< modelGenerator.VerticesSize() << " vertices" << std::endl;
    modelGenerator.MakeModel( filename );
    
    ModelDemonstrator( filename, renderRange * 2.5 );
}
