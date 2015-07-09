#include "c_rand_var.h"

void c_rand_var::dat_to_dist(size_t dim_prob, const double *x) {
    raw_data.resize(dim_prob);
    partial_dat_to_dist(0, dim_prob, x);
}

void c_rand_var::partial_dat_to_dist(size_t lower, size_t upper, const double *x) {
    size_t k = 0;
    for (size_t i = lower; i < upper; ++i) {
        raw_data[i] = *(x+k);
        ++k;
    }
}
