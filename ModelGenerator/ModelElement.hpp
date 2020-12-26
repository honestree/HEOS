#pragma once

struct ModelElement{
    
    float r;
    float theta;
    float phi;
    double probability;    
};


bool Model_cmp( ModelElement a , ModelElement b );