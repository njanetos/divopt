#include "c_inequality.h"

divopt::c_inequality::c_inequality(size_t dim, float val, binary_relation bin) {
    this->dim = dim;
    this->val = val;
    this->bin = bin;
}

divopt::c_inequality::~c_inequality() {
    //dtor
}

size_t divopt::c_inequality::get_dim() {
    return dim;
}

float divopt::c_inequality::get_val() {
    return val;
}

divopt::binary_relation divopt::c_inequality::get_binary_relation() {
    return bin;
}
