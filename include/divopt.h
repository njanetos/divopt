#ifndef DIVOPT_H
#define DIVOPT_H

#include<armadillo>

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
     *  Computes the pdf of a normal random variable.
     *
     * @param mean Vector representing the mean of the random variable.
     * @param cov  Matrix representing the covariance matrix.
     * @param loc  Vector representing the location at which the pdf is evaluated.
     */
    double pdf(const arma::mat *mean,
               const arma::mat *cov,
               const arma::mat *loc);

    /**
     *  Computes the cdf of a normal random variable.
     *
     * @param mean Vector representing the mean of the random variable.
     * @param cov  Matrix representing the covariance matrix.
     * @param loc  Vector representing the location at which the cdf is evaluated.
     */
    double cdf(const arma::mat *mean,
               const arma::mat *cov,
               const arma::mat *per);

    /**
     *  Computes the divergence of two random variables.
     *
     * @param mean_old Vector representing the mean of the random variable in the denominator.
     * @param cov_old  Matrix representing the covariance matrix in the denominator.
     * @param mean_new Vector representing the mean of the random variable in the numerator.
     * @param cov_new  Matrix representing the covariance matrix in the numerator.
     */
    double div(const arma::mat *mean_old,
               const arma::mat *cov_old,
               const arma::mat *mean_new,
               const arma::mat *cov_new);

    /**
     *  Computes the entropy of two random variables at one realization.
     *
     * @param mean_old Vector representing the mean of the random variable in the denominator.
     * @param cov_old  Matrix representing the covariance matrix in the denominator.
     * @param mean_new Vector representing the mean of the random variable in the numerator.
     * @param cov_new  Matrix representing the covariance matrix in the numerator.
     * @param looc     Vector representing the location to evaluate at.
     */
    double ent(const arma::mat *mean_old,
               const arma::mat *cov_old,
               const arma::mat *mean_new,
               const arma::mat *cov_new,
               const arma::mat *loc);

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


    const double c_util::PI =         3.1415926535897932384626;
    const double c_util::SQRT_TWO =   1.4142135623730950488016;
    const double c_util::WEIGHTS[] ={ 0.0199532420590459132077,
                                      0.3936193231522411598285,
                                      0.9453087204829418812260,
                                      0.3936193231522411598285,
                                      0.0199532420590459132077};
    const double c_util::ABS[] = {   -2.0201828704560856329290,
                                     -0.9585724646138185071128,
                                      0.0000000000000000000000,
                                      0.9585724646138185071128,
                                      2.020182870456085632929};
    const int c_util::QUADRATURE_DIM = 5;
    const double c_util::WEIGHT_FLOOR = 0.000001;
}

#endif // DIVOPT_H
