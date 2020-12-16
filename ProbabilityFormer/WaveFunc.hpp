#pragma once
#include <vector>
#include "Polynomial.hpp"

class WaveFunc{

    public:
        Polynomial Laguerre( int i );
    private:
        static std::vector<Polynomial> LaguerreStore;
};

