#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <unistd.h>
#include "ModelDemonstrator/ModelDemonstrator.hpp"
#include "ModelGenerator/ModelGenerator.hpp"
#include "ProbabilityFormer/WaveFunc.hpp"

int main( int argc , char* argv[] ){
    
    unsigned int rounds = 1000000;
    double renderRange = 30;
    double renderPMax = 1e27;
    double renderPMin = 1e25;
    int QN, QL, QM;
    std::vector<struct ModelElement> modelElements;
    std::string filename;
  
    if( argc != 4 ){
        std::cout<< "./HEOS N L M " << std::endl;
        return -1;
    }
    else{
        QN = atoi( argv[1] );
        QL = atoi( argv[2] );
        QM = atoi( argv[3] );
    }

    filename += "Models/N";
    filename += std::to_string( QN );
    filename += "L";
    filename += std::to_string( QL );
    filename += "M";
    filename += std::to_string( QM );
    filename += ".ply";

    // check if file generated
    if(( access( filename.c_str(), R_OK ) ) != -1){

        std::cout << "Old File found, reused" << std::endl;

    }
    else{

        std::cout << "Generating "<< filename << std::endl;
        std::cout << "Calculating probability" << std::endl;
        
        WaveFunc WF1( QN, QL, QM );
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

        ModelGenerator modelGenerator( renderPMax , renderPMin, renderRange );
        modelGenerator.AddModelElements( modelElements );

        std::cout << "Creating Model with "<< modelGenerator.VerticesSize() << " vertices" << std::endl;
        modelGenerator.MakeModel( filename.c_str() );
    }
   
    try{ 
        ModelDemonstrator( filename.c_str(), renderRange * 2.5 ); 
    } 
    catch( const std::ios_base::failure& e ){
        std::cout << "File corrupted, " << e.what() << std::endl;
    }
}
