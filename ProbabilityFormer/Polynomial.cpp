#include "Polynomial.hpp"
#include <cstdio>
#include <cstdlib>

Polynomial Polynomial::operator+( Polynomial const &other ){

    Polynomial ans;
    ans.parameters.resize( std::max( this->parameters.size(), other.parameters.size()));

    for( int i = 0 ; i < this->parameters.size() ; ++i ){
        ans.parameters[ i ] += this->parameters[ i ];
    }

    for( int i = 0 ; i < other.parameters.size() ; ++i ){
        ans.parameters[ i ] += other.parameters[ i ];
    }

    ans.removeZero();
    return ans;
}

Polynomial Polynomial::operator-( Polynomial const &other ){

    Polynomial ans;
    ans.parameters.resize( std::max( this->parameters.size(), other.parameters.size()));

    for( int i = 0 ; i < this->parameters.size() ; ++i ){
        ans.parameters[ i ] += this->parameters[ i ];
    }

    for( int i = 0 ; i < other.parameters.size() ; ++i ){
        ans.parameters[ i ] -= other.parameters[ i ];
    }

    ans.removeZero();
    return ans;
}

Polynomial Polynomial::operator*( double scalar ){

    Polynomial ans;
    ans.parameters.resize( this->parameters.size());

    for( int i = 0 ; i < this->parameters.size() ; ++i ){
        ans.parameters[ i ] = this->parameters[ i ] * scalar ;
    }

    ans.removeZero();
    return ans;
}

Polynomial Polynomial::operator*( Polynomial const &other ){

    Polynomial ans;
    ans.parameters.resize( this->parameters.size() + other.parameters.size());

    for( int i = 0 ; i < this->parameters.size() ; ++i ){
        for( int j = 0 ; j < other.parameters.size() ; ++j )

            ans.parameters[ i + j ] += this->parameters[ i ] * other.parameters[ j ];
    }

    ans.removeZero();
    return ans;
}

Polynomial Polynomial::operator/( double scalar ){
    return *this * ( 1 / scalar );
}


bool Polynomial::operator==( Polynomial const &other ){

    if( this->parameters.size() != other.parameters.size() ){
        printf("size missmatch: %ld vs %ld\n", this->parameters.size() , other.parameters.size() );
        return false;
    }

    for( int i = 0 ; i < this->parameters.size() ; ++i ){

        if( abs( this->parameters[ i ] - other.parameters[ i ] ) > 0.00000000000000000000000000001 ){
            printf( " position different at %d: %lf vs %lf  \n", i , this->parameters[i] , other.parameters[ i ] );
            return false;
        }
    }
    return true;
}

void Polynomial::removeZero(){

    while( this->parameters.back() == 0 && this->parameters.size() > 1 ){
        this->parameters.pop_back();
    }

    return;
}


double Polynomial::value( double x ){

    double ans = 0;

    for( int index = this->parameters.size() - 1; index > 0; index-- ){
        ans += this->parameters[ index ];
        ans *= x;
    }
    ans += this->parameters[ 0 ];

    return ans;
}

void Polynomial::differential(){

    for( int i = 1 ; i < this->parameters.size(); ++i ){

        this->parameters[ i - 1 ] = this->parameters[ i ] * i;
    }

    if( this->parameters.size() > 1 ){

        this->parameters.pop_back();
    }
    else{

        this->parameters[0] = 0;
    }

    return;
}

