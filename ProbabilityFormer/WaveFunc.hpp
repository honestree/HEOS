#pragma once
#include <vector>
#include <cstdlib>
#include <map>
#include "Polynomial.hpp"

#define BohrRad 5.29177210903e-11

class WaveFunc{

    public:

        WaveFunc( int in_N, int in_L, int in_M ):QN( in_N ),QL( in_L ),QM( in_M ){

            if( QN < 0  || QL >= QN || abs( QM ) > QL ){
                throw std::invalid_argument("Invaild Quantum Number detected while creating WaveFunc");
            }
        }

        Polynomial Laguerre( int i );
        Polynomial ExtLaguerre( int QN, int QL );

        // Radial Basis Function
        double RBF( double Radial );

    private:
        // Quantum Numbers
        int QN = 1;
        int QL = 0;
        int QM = 0;

        //Storing value for speedup

        //Defined recursively, therefore stored in vector
        static std::vector<Polynomial> LaguerreStore;

        //Calculated By <QN, QL>, therefore stored in map
        static std::map< std::pair<int, int>, Polynomial> ExtLaguerreStore;
};

