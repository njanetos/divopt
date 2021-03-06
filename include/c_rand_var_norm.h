#ifndef C_RAND_VAR_NORM_H
#define C_RAND_VAR_NORM_H

#include "common.h"

#include <armadillo>
#include <cmath>
#include "mvtnorm.h"

/**
 * @brief Represents an n-dimensional normal random variable.
 */
class c_rand_var_norm {

    public:

        c_rand_var_norm(size_t dim);

        void clone(c_rand_var_norm* parent);

        real cdf(arma::mat& inequalities);
        arma::mat cdf_grad(arma::mat& inequalities);
        real div(c_rand_var_norm& var);
        real div_alternate(c_rand_var_norm& var);
        arma::mat div_grad(c_rand_var_norm& oth);
        real ent(arma::mat& loc, c_rand_var_norm& var);

        /**
         *  Returns the inverse of the covariance matrix. Since this
         *  is an expensive operation, it is only inverted when called.
         *  \return The inverse of the covariance matrix.
         */
        arma::mat& inv_cov();

        double pdf(arma::mat& loc);
        arma::mat pdf_grad(arma::mat& loc);
        void pack();
        void unpack();

        void dat_to_dist(const double *x);
        void partial_dat_to_dist(size_t lower, size_t upper, const double *x);
        size_t get_dim() const;
        size_t get_dim_prob() const;

        size_t get_opt_dim() const;

        std::vector<real> get_lower_bounds() const;
        std::vector<real> get_upper_bounds() const;

        arma::mat mean, cov, corr, var, ch;
        real norm_factor, det_cov, gauss_factor;
        std::vector<bool> opt_flags;

        /**
        *  The raw data of the problem. Should be of length dim_prob.
        */
        std::vector<double> raw_data;

        bool inv_cov_is_computed;
        arma::mat m_inv_cov;

    protected:


        /**
         *  The dimension of the state space. (Not the optimization problem!)
         */
        size_t dim;

        /**
         *  The dimension of the problem. (Not the state space!)
         */
        size_t dim_prob;


};

#endif // C_RAND_VAR_NORM_H
