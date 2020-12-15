#pragma once
#include <vector>

class Polynomial{

    public:

        //default constructor
        Polynomial(){}

        // construct with vector
        // polynomial( vector<double>{ 1 , 2 , 3 } )
        Polynomial( std::vector<double> in ):parameters( in ){
            removeZero();
        }

        //copy assignment operator
        Polynomial& operator=( const Polynomial &other ){
            parameters = other.parameters;
        }

        //operators
        double operator()( int pos ) const { return parameters[ pos ]; }
        double &operator()( int pos ){ return parameters[ pos ]; }
        Polynomial operator+( Polynomial const &other );
        Polynomial operator-( Polynomial const &other );
        Polynomial operator*( double scalar );
        Polynomial operator*( Polynomial const &other );
        bool operator==( Polynomial const &other );

        //others
        double value( double x );
        void differential();

    private:
        // value store as parameter, postion stands for the index of x
        // vector<double> parameters { 1 , 2 , 3 } stands for 3 x^2 + 2x + 1
        // which means negative index not implemented
        std::vector< double > parameters{ 0 };

        //clear Leading Zero and made parameters.size()-1 really the highest index
        void removeZero();
};

