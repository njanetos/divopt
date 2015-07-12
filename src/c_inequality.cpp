#include "c_inequality.h"

c_inequality::c_inequality(size_t dim, float val, binary_relation bin) {
    this->dim = dim;
    this->val = val;
    this->bin = bin;
}

c_inequality::~c_inequality() {
    //dtor
}

size_t c_inequality::get_dim() {
    return dim;
}

float c_inequality::get_val() {
    return val;
}

binary_relation c_inequality::get_binary_relation() {
    return bin;
}
