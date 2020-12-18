#include "WaveFunc.hpp"
#include <cstdio>
#include <cmath>

std::vector<Polynomial> WaveFunc::LaguerreStore{ Polynomial( std::vector<double>{ 1 } ), Polynomial(std::vector<double>{ 1,-1 }) };
std::map< std::pair<int , int>, Polynomial > WaveFunc::ExtLaguerreStore;
std::map< std::pair<int, int>, Polynomial> WaveFunc::RodriguesStore;

// compute Laguerre recursively
Polynomial WaveFunc::Laguerre( int i ){

    // prevent recalculate
    if( i < LaguerreStore.size() ){
        return LaguerreStore[ i ];
    }

    Polynomial ans = Laguerre( i-1 ) * Polynomial(std::vector<double>{ (double) 2*i - 1, -1 }) - Laguerre( i-2 )*( i-1 );
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

Polynomial WaveFunc::Rodrigues( int QL, int QM ){

    // prevent recalculate
    int QM_ABS = abs( QM );
    if( RodriguesStore.find( std::pair<int,int>( QL, QM_ABS )) != RodriguesStore.end()){
        return RodriguesStore.find( std::pair<int,int>( QL, QM_ABS ) )->second;
    }
    
    Polynomial ans;
    if( QL > 0 ){
        ans = Polynomial( std::vector<double>{ -1, 0, 1 } ) ;
        for( int i = 1; i < QL ; ++i ){
            ans = ans * Polynomial( std::vector<double>{ -1, 0, 1 } );
        }
    }
    else{
        ans = Polynomial( std::vector<double>{ 1 } ) ;
    }

    for( int i = 0; i < QL + QM_ABS ; ++i ){
        ans.differential();
    }
    ans = ans / ( pow( 2, QL ) * tgamma( QL+1 ) );
    ans = ans * sqrt( ( 2*QL + 1 ) / ( 4*M_PI ) * tgamma( QL - QM_ABS + 1 ) / tgamma( QL + QM_ABS + 1));
    RodriguesStore.insert( std::pair< std::pair<int,int>, Polynomial >( std::pair<int,int>( QL, QM_ABS ), ans ));

    return ans;
}

std::complex<double> WaveFunc::SH( double theta, double phi ){

    int QM_ABS = abs( QM );
    double real = pow( fabs(sin( theta )), QM_ABS) * Rodrigues( QL, QM ).value( cos(theta) );
    std::complex<double> ans( real, 0 );
    for( int i = 0 ; i < ( QM + QM_ABS ) % 4 ; ++i ){
        ans *= std::complex<double>( 0, 1 );
    }

    ans *= std::complex<double>( cos( QM * phi ), sin( QM * phi ));

    return ans;
}


double WaveFunc::probability( double Radial, double theta, double phi ){

    std::complex<double> PDF = SH( theta , phi ) * RBF( Radial );
    return std::norm( PDF );
}
