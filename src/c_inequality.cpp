#include "c_inequality.h"

divopt::c_inequality::c_inequality(size_t dim, float val, e_binary_relation bin) {
    this->dim = dim;
    this->val = val;
    this->bin = bin;
}

size_t divopt::c_inequality::get_dim() const {
    return dim;
}

float divopt::c_inequality::get_val() const {
    return val;
}

divopt::e_binary_relation divopt::c_inequality::get_binary_relation() const {
    return bin;
}
