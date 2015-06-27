#ifndef C_UTIL_H
#define C_UTIL_H

#include <armadillo>
#include <cmath>
#include <nlopt.hpp>

/**
 *
 */
namespace divopt {
    class c_util {
        public:

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
            static void solve(const arma::mat *mean_old,
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
            static double pdf(const arma::mat *mean,
                              const arma::mat *cov,
                              const arma::mat *loc);

            /**
             *  Computes the cdf of a normal random variable.
             *
             * @param mean Vector representing the mean of the random variable.
             * @param cov  Matrix representing the covariance matrix.
             * @param loc  Vector representing the location at which the cdf is evaluated.
             */
            static double cdf(const arma::mat *mean,
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
            static double div(const arma::mat *mean_old,
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
            static double ent(const arma::mat *mean_old,
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
            static double gauss_hermite(const arma::mat *mean,
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
            static double gauss_hermite(const arma::mat *mean,
                                        const arma::mat *cov,
                                        double (*func)(const arma::mat *loc),
                                        size_t grid);
        protected:
        private:
    };
}


#endif // C_UTIL_H
