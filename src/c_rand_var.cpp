#include "c_logger.h"
#include "c_rand_var.h"

void divopt::c_rand_var::dat_to_dist(const double *x) {

    partial_dat_to_dist(0, dim_prob, x);

}

void divopt::c_rand_var::partial_dat_to_dist(size_t lower, size_t upper, const double *x) {

    size_t k = 0;
    for (size_t i = lower; i < upper; ++i) {
        raw_data[i] = *(x+k);
        ++k;
    }

}

double divopt::c_rand_var::get_dim() const {

    return dim;

}

double divopt::c_rand_var::get_dim_prob() const {

    return dim_prob;

}
