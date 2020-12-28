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

}
