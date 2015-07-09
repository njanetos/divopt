#include "c_rand_var_norm.h"

c_rand_var_norm::c_rand_var_norm(size_t dim) {
    this->dim = dim;
}

c_rand_var_norm::~c_rand_var_norm() {

}

size_t c_rand_var_norm::get_dim_prob() {
    return dim_prob;
}

void c_rand_var_norm::unpack() {

    // Instantiate mean (can be directly written in).
    mean = mat(&raw_data[0], dim, 1, true, true);

    // Instantiate Cholesky factorization
    size_t k = dim;
    ch = zeros<mat>(dim, dim);
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            ch(i, j) = raw_data[k];
            ++k;
        }
    }

    // Compute covariance matrix
    cov = ch*ch.t();

    // Get the correlations
    corr = diagmat(1/sqrt(diagmat(cov)))*cov*diagmat(1/sqrt(diagmat(cov)));

    // Find the remaining scalar values
    det_cov = det(cov);
    norm_factor = 1/(sqrt(pow(2*c_util::PI, dim)*det_cov));
    gauss_factor = arma::det(ch)/sqrt(pow(c_util::PI, dim)*det_cov);

    // Flag inverse matrices as in need of computation
    inv_cov_comp = false;
    inv_ch_comp = false;
}

void c_rand_var_norm::pack() {
    for (size_t i = 0; i < dim; ++i) {
        raw_data[i] = mean(i);
    }

    size_t k = dim;
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            raw_data[k] = ch(i, j);
            ++k;
        }
    }
}

std::vector<double> c_rand_var_norm::estimate(con_data *pred) {
    // TODO: Implement a better algorithm here!
    return raw_data;
}

mat& c_rand_var_norm::inv_cov() {

    if (!inv_cov_comp) {
        m_inv_cov = inv(cov);
        inv_cov_comp = true;
    }
    return m_inv_cov;
}

mat& c_rand_var_norm::inv_ch() {

    if (!inv_ch_comp) {
        m_inv_ch = inv(ch);
        inv_ch_comp = true;
    }
    return m_inv_ch;
}
