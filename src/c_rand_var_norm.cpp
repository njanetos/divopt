#include "c_rand_var_norm.h"

c_rand_var_norm::c_rand_var_norm(size_t dim) {

    // Set the dimension of the state space.
    this->dim = dim;

    // The dimension of the optimization problem is the mean vector plus the upper triangular Cholesky factorization of the covariance matrix.
    this->dim_prob = dim*(dim+1)/2;

}

c_rand_var_norm::~c_rand_var_norm() {

}

size_t c_rand_var_norm::get_dim_prob() {

    return dim_prob;

}

void c_rand_var_norm::unpack() {

    // Instantiate mean (can be directly written in).
    mean = arma::mat(&raw_data[0], dim, 1, true, true);

    // Instantiate Cholesky factorization, C.
    size_t k = dim;
    ch = zeros<mat>(dim, dim);
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            ch(i, j) = raw_data[k];
            ++k;
        }
    }

    // Compute covariance matrix, S = C*C'.
    cov = ch*ch.t();

    // Get the correlation matrix.
    corr = arma::diagmat(1/arma::sqrt(arma::diagmat(cov)))*cov*arma::diagmat(1/arma::sqrt(arma::diagmat(cov)));

    // Find the remaining scalar values
    det_cov = det(cov);
    norm_factor = 1/(sqrt(pow(2*c_util::PI, dim)*det_cov));
    gauss_factor = arma::det(ch)/sqrt(pow(c_util::PI, dim)*det_cov);

    // Flag inverse matrices as in need of computation
    inv_cov_is_computed = false;
    inv_ch_is_computed = false;

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

arma::mat& c_rand_var_norm::inv_cov() {

    // Check if the inverse covariance matrix has already been computed.
    if (!inv_cov_is_computed) {

        // Compute the inverse.
        m_inv_cov = arma::inv(cov);

        // Flag it as completed.
        inv_cov_is_computed = true;

    }

    return m_inv_cov;

}

arma::mat& c_rand_var_norm::inv_ch() {

    // Check if the inverse of the Cholesky factorization has been computed.
    if (!inv_ch_is_computed) {

        // Compute it.
        m_inv_ch = inv(ch);

        // Compute the inverse of the covariance matrix while we're at it.
        m_inv_cov = m_inv_ch*m_inv_ch.t();

        // Flag both as computed.
        inv_ch_is_computed = true;
        inv_cov_is_computed = true;

    }

    return m_inv_ch;

}
