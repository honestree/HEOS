#include <iostream>
#include <unistd.h>
#include "RequestDealer/RequestDealer.hpp"

int main( int argc , char* argv[] ){
 
    if( argc != 4 ){
        std::cout<< "./HEOS N L M " << std::endl;
        return -1;
    }

    RequestDealer RD;
    RD.ShowModel( atoi( argv[1] ) , atoi( argv[2] ) , atoi( argv[3] ) );

    //Dicide the Render Range(Angstrom, 10^-10 meters)
    RD.SetRenderRange( 30.0 );
    
    //Dicide to Shuffle how many points inside a cube ranged in ( range, -range )
    //The more, the result is more detailed and slowed.
    RD.SetRounds( 100000 );

    //Since The Overall model would strongly depend on how you take probability into account
    //Type in pair( MAX probability, Min probability) to decide the model coloring
    //For showing N >= 4, its recommented to go with default;
    //For Larger N, using smaller probability to show more detailed shape
    RD.SetColorScheme( std::pair<double,double>( 1e27, 1e25 ) );

}
