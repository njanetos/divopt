#include "c_rand_var_norm.h"
#include "c_util.h"
#include "c_logger.h"

c_rand_var_norm::c_rand_var_norm(size_t dim) {

    // Set the dimension of the state space.
    this->dim = dim;

    // The dimension of the optimization problem is the mean vector plus the upper triangular Cholesky factorization of the covariance matrix.
    this->dim_prob = dim + dim*(dim+1)/2;

    // Prepare the raw data
    raw_data.resize(dim_prob);

}

c_rand_var_norm::~c_rand_var_norm() {

}

double c_rand_var_norm::cdf(arma::mat *loc) {

    // Find the adjusted score.
    arma::mat adj_pos = (*loc - mean) / sqrt(cov.diag());

    // Read in the raw data for the correlation matrix
    // to pass to CDF computing library.
    double * locRaw = adj_pos.memptr();
    double raw_data_temp[dim*(dim-1)/2];

    size_t k = 0;
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < i; ++j) {
            raw_data_temp[k] = corr(i, j);
            ++k;
        }
    }

    double error;
    double ret;
    if (pmvnorm_P(dim, locRaw, raw_data_temp, &error, &ret) != 0) {
        log().warning() << "CDF may have issues. Error tolerance: " << error;
    }

    return ret;
}

arma::mat c_rand_var_norm::cdf_grad(arma::mat *loc) {
    return NULL;
}

double c_rand_var_norm::div(c_rand_var *var) {
    return 0.0;
}

void c_rand_var_norm::div_grad(c_rand_var *oth, double *res) {

}

double c_rand_var_norm::ent(double *loc, c_rand_var *var) {
    return 0.0;
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

double c_rand_var_norm::pdf(arma::mat *loc) {
    arma::mat expint = exp(-0.5*(*loc - mean).t()*inv_cov()*(*loc - mean));
    return norm_factor*expint(0);
}

arma::mat c_rand_var_norm::pdf_grad(arma::mat *loc) {
    return NULL;
}

void c_rand_var_norm::unpack() {

    // Instantiate mean (can be directly written in).
    mean = arma::mat(&raw_data[0], dim, 1, true, true);

    // Instantiate Cholesky factorization, C.
    size_t k = dim;
    ch = arma::zeros<arma::mat>(dim, dim);
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
