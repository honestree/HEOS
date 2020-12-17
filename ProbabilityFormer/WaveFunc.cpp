#include "WaveFunc.hpp"
#include <cstdio>
#include <cmath>

std::vector<Polynomial> WaveFunc::LaguerreStore{ Polynomial( std::vector<double>{ 1 } ), Polynomial(std::vector<double>{ 1,-1 }) };
std::map< std::pair<int , int>, Polynomial > WaveFunc::ExtLaguerreStore;

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

Polynomial WaveFunc::ExtLaguerre( int QN, int QL ){

    // prevent recalculate
    if( ExtLaguerreStore.find( std::pair<int,int>( QN, QL )) != ExtLaguerreStore.end()){
        return ExtLaguerreStore.find( std::pair<int,int>( QN, QL ) )->second;
    }
    
    Polynomial ans = Laguerre( QN + QL );
    for( int i = 0 ; i < 2 * QL + 1 ; i++  ){
        ans.differential();
    }

    double od = pow( (double) 2 / ( QN * BohrRad ) , 3 );
    double oe = tgamma( QN - QL ) /(2 * QN * tgamma( QN + QL + 1 ) );
   
    ans = ans * ( - 1 ) * sqrt( od * oe );
    ExtLaguerreStore.insert( std::pair< std::pair<int,int>, Polynomial >( std::pair<int,int>( QN, QL ), ans ));

    return ans;
}

double WaveFunc::RBF( double Radial ){
    double m_exp = exp( -1 * Radial / ( QN * BohrRad ));
    double tar = 2 * Radial / ( QN * BohrRad );
    return ExtLaguerre( QN, QL ).value( tar ) * pow( tar, QL ) * m_exp;
}

