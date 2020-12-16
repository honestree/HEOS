#include "WaveFunc.hpp"
#include <cstdio>

std::vector<Polynomial> WaveFunc::LaguerreStore{ Polynomial( std::vector<double>{ 1 } ), Polynomial(std::vector<double>{ 1,-1 }) };


// compute Laguerre recursively
Polynomial WaveFunc::Laguerre( int i ){

    // prevent recalculate
    if( i < LaguerreStore.size() ){
        return LaguerreStore[ i ];
    }

    Polynomial ans = Laguerre( i-1 ) * Polynomial(std::vector<double>{ 2 * i - 1, -1 }) - Laguerre( i-2 )*( i-1 );
    ans = ans / (double) i;

    LaguerreStore.push_back( ans );
    return LaguerreStore[ i ];
}
