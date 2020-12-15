#include "Polynomial.hpp"
#include <cstdio>

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

bool Polynomial::operator==( Polynomial const &other ){

    if( this->parameters.size() != other.parameters.size() ){
        printf("size missmatch: %ld vs %ld\n", this->parameters.size() , other.parameters.size() );
        return false;
    }

    for( int i = 0 ; i < this->parameters.size() ; ++i ){

        if( this->parameters[ i ] != other.parameters[ i ] ){
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



