#include <iostream>
#include <unistd.h>
#include "RequestDealer/RequestDealer.hpp"
       
// Show a model;
// RD.ShowModel( n , l , m );

//Dicide the Render Range(Angstrom, 10^-10 meters)
// RD.SetRenderRange( 30.0 );

//Dicide to Shuffle how many points inside a cube ranged in ( range, -range )
//The more, the result is more detailed and slowed.
//RD.SetRounds( 100000 );

//Since The Overall model would strongly depend on how you take probability into account
//Type in pair( MAX probability, Min probability) to decide the model coloring
//For showing N >= 4, its recommented to go with default;
//For Larger N, using smaller probability to show more detailed shape
//RD.SetColorScheme( std::pair<double,double>( 1e27, 1e25 ) );

int main( int argc , char* argv[] ){

    RequestDealer RD;
    std::string tmp_str;
    unsigned int n, l, m, tmp_i;
    double tmp_d,tmp_d2;

    while( true ){

        system("clear");

        std::cout << "HEOS - Hydrogen Electron Orbital Simulator" << std::endl;
        std::cout << "(1) Show a model" << std::endl;
        std::cout << "(2) Change the number of points: Now " << RD.GetRounds() << " points"  << std::endl;
        std::cout << "(3) Change the size of Rendering Distance: Now " << RD.GetRenderRange() << " * 10^-10 m"  << std::endl;
        std::cout << "(4) Change the range of Rendering Probability: Now " << RD.GetColorScheme().first << " to "  << RD.GetColorScheme().second << std::endl; 
        std::cout << "(5) Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> tmp_str;

        if( tmp_str == "1" ){
            std::cout << "Insert in the Principal quantum number, azimuthal quantum and magnetic quantum number." << std::endl;
            std::cin >> n;
            std::cin >> l;
            std::cin >> m;
            RD.ShowModel( n , l , m );
        }
        else if( tmp_str == "2" ){
            std::cout << "Insert the number of points: Now " << RD.GetRounds() << " points"  << std::endl;
            std::cin >> tmp_i;
            RD.SetRounds( tmp_i );
        }
        else if( tmp_str == "3" ){
            std::cout << "Insert the Rendering Distance: Now " << RD.GetRenderRange() << " * 10^-10 m" << std::endl;
            std::cin >> tmp_d;
            RD.SetRenderRange( tmp_d );
        }
        else if( tmp_str == "4" ){
            std::cout << "Insert the range of Rendering Probability: Now " << RD.GetColorScheme().first << " to "  << RD.GetColorScheme().second << std::endl; 
            std::cout << "Render Maxima: ";
            std::cin >> tmp_d;
            std::cout << "Render Minima: ";
            std::cin >> tmp_d2;
            RD.SetColorScheme( std::pair<double,double>( tmp_d, tmp_d2 ) );
        }
        else if( tmp_str == "5" ){
            std::cout << "Exit" << std::endl;            
            return 0;
        }
        else{
            std::cout << "Invaild Input! Retry" << std::endl;
            system("wait 1");
        }               
    }
}
