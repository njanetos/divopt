#ifndef DIVOPT_H
#define DIVOPT_H

#define PI 3.1415926535897932384626
#define SQRT_TWO 1.4142135623730950488016

#include<armadillo>
#include "c_rand_var_norm.h"

namespace divopt {
    /**
     *  Solves the optimization problem as described in the introduction
     *  and stores the result in <code>mean_new</code> and <code>cov_new</code>.
     *
     * @param mean_old Vector representing the mean of the random variable.
     * @param cov_old  Matrix representing the covariance matrix.
     * @param per      Vector representing the location at which the cdf constraint is evaluated.
     * @param p        The probability value in the constraint.
     * @param mean_new Stores the mean of the result here.
     * @param cov_new  Stores the covariance of the result here.
     */
    void solve(const arma::mat *mean_old,
               const arma::mat *cov_old,
               const arma::mat *per,
               double p,
               arma::mat *mean_new,
               arma::mat *cov_new);

    /**
     *  Uses Gauss-Hermite integration to find the expected value of a function.
     *
     * @param mean Vector representing the mean of the random variable.
     * @param cov  Matrix representing the covariance matrix.
     * @param func Function to evaluate.
     */
    double gauss_hermite(const arma::mat *mean,
                         const arma::mat *cov,
                         double (*func)(const arma::mat *loc));

    /**
     *  Uses Gauss-Hermite integration to find the expected value of a function.
     *
     * @param mean Vector representing the mean of the random variable.
     * @param cov  Matrix representing the covariance matrix.
     * @param func Function to evaluate.
     * @param grid Number of evaluation points to use.
     */
    double gauss_hermite(const arma::mat *mean,
                         const arma::mat *cov,
                         double (*func)(const arma::mat *loc),
                         size_t grid);
}

#endif // DIVOPT_H
