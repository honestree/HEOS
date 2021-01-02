#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include <unistd.h>
#include "../ModelDemonstrator/ModelDemonstrator.hpp"
#include "../ModelGenerator/ModelGenerator.hpp"
#include "../ProbabilityFormer/WaveFunc.hpp"
#include "RequestDealer.hpp"


void RequestDealer::ShowModel( int N, int L, int M ){
   
    // Using string stream to set filename
    std::ostringstream filename_tmp;
    filename_tmp << "Models/N" << N << "L" << L << "M" << M;
    filename_tmp << "P" << rounds << "UB" << renderPMax << "LB" << renderPMin << ".ply";
    std::string filename = filename_tmp.str();

    // check if file generated
    if(( access( filename.c_str(), R_OK ) ) != -1){

        std::cout << "Old File found, reused" << std::endl;

    }
    else{

        std::cout << "Generating Model"<< filename << std::endl;
        generateModel( N, L, M, filename.c_str() );
        std::cout << "Model Generated " << std::endl;
    }
   
    try{ 
        ModelDemonstrator( filename.c_str(), renderRange * 2.5 ); 
    } 
    catch( const std::ios_base::failure& e ){
    
        std::cout << "File corrupted, " << e.what() << std::endl;
        std::cout << "Regenerate a new one\n" << e.what() << std::endl;
        generateModel( N, L, M, filename.c_str() );
        ModelDemonstrator( filename.c_str(), renderRange * 2.5 );

    }
}

int RequestDealer::generateModel( int N, int L, int M, const char* filename ){
 
    std::cout << "Calculating probability" << std::endl;
    
    WaveFunc WF1( N, L, M );

    std::default_random_engine generator;
    std::uniform_real_distribution<double> rand_dev(renderRange * -1 , renderRange);
    modelElements.resize(0);
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

    ModelGenerator modelGenerator( renderPMax , renderPMin, renderRange );
    modelGenerator.AddModelElements( modelElements );

    std::cout << "Creating Model with "<< modelGenerator.VerticesSize() << " vertices" << std::endl;

    try{
        modelGenerator.MakeModel( filename );
    }    
    catch( const std::ios_base::failure& e ){
    
        std::cout << e.what() << std::endl;
        return -1;

    }
}
