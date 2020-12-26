#pragma once

struct ModelElement{
    
    float r;
    float theta;
    float phi;
    double probability;    
};


bool ModelCmp( struct ModelElement a ,struct ModelElement b );