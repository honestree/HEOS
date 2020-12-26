#include "ModelElement.hpp"

bool Model_cmp( struct ModelElement a , struct ModelElement b ){

    return a.probability < b.probability;

}