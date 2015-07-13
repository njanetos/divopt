#ifndef C_RAND_VAR_NORM_H
#define C_RAND_VAR_NORM_H

#include <armadillo>
#include <cmath>
#include "c_rand_var.h"
#include "mvtnorm.h"

namespace divopt {

    /**
     * @brief Represents an n-dimensional normal random variable.
     */
    class c_rand_var_norm : public c_rand_var {

        public:

            c_rand_var_norm(size_t dim);
            virtual ~c_rand_var_norm();

            double cdf(arma::mat *loc);
            double cdf(std::vector<c_inequality> *inequalities);
            arma::mat cdf_grad(arma::mat *loc);
            double div(c_rand_var *var);
            arma::mat div_grad(c_rand_var *oth);
            double ent(arma::mat *loc, c_rand_var *var);

            /**
             *  Returns the inverse of the covariance matrix. Since this
             *  is an expensive operation, it is only inverted when called.
             *  \return The inverse of the covariance matrix.
             */
            arma::mat& inv_cov();

            /**
             *  Returns the inverse of the Cholesky matrix. Since this
             *  is an expensive operation, it is only inverted when called.
             *  \return The inverse of the Cholesky matrix.
             */
            arma::mat& inv_ch();

            double pdf(arma::mat *loc);
            arma::mat pdf_grad(arma::mat *loc);
            void pack();
            void pdf_grad(double *loc, double *res);
            void unpack();

            arma::mat mean, cov, corr, ch, var;
            double norm_factor, det_cov, gauss_factor;

        protected:

            bool inv_ch_is_computed, inv_cov_is_computed;
            arma::mat m_inv_cov, m_inv_ch;

    };

}

#endif // C_RAND_VAR_NORM_H
