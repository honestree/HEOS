#pragma once

#include "../ModelGenerator/ModelGenerator.hpp"
#include <utility>

class RequestDealer{
    
    public:
    
        RequestDealer(){}
        ~RequestDealer(){}

        void ShowModel( int N, int L, int M );

        //seters
        void SetRenderRange( double r ){ renderRange = r; }
        void SetRounds( unsigned int r ){ rounds = r; }
        void SetColorScheme( std::pair<double,double> in){
            renderPMax = in.first;
            renderPMin = in.second;        
        }
        double GetRenderRange(){ return renderRange; }
        unsigned int GetRounds(){ return rounds; }
        std::pair<double,double> GetColorScheme(){
            return std::pair<double,double>( renderPMax, renderPMin );
        }

    

    private:

        unsigned int rounds = 1000000;
        double renderRange = 30;
        double renderPMax = 1e27;
        double renderPMin = 1e25;
        std::vector<struct ModelElement> modelElements;

        int generateModel( int N, int L, int M, const char* filename );
    
};
