#include "../include/divopt.h"

namespace divopt {
  void solve(const arma::mat *mean_old,
             const arma::mat *cov_old,
             const arma::mat *per,
             double p,
             arma::mat *mean_new,
             arma::mat *cov_new) {

  }

  double pdf(const arma::mat *mean,
             const arma::mat *cov,
             const arma::mat *loc) {
    mat locMat = arma::mat(loc, mean->dim, 1, false, true);
    mat expint = exp(-0.5*(locMat - mean).t()*inv_cov()*(locMat - mean));
    return norm_factor*expint(0);`
  }

  double cdf(const arma::mat *mean,
             const arma::mat *cov,
             const arma::mat *per) {
    return 0.0;
  }

  double div(const arma::mat *mean_old,
             const arma::mat *cov_old,
             const arma::mat *mean_new,
             const arma::mat *cov_new) {
    return 0.0;
  }

  double ent(const arma::mat *mean_old,
             const arma::mat *cov_old,
             const arma::mat *mean_new,
             const arma::mat *cov_new,
             const arma::mat *loc) {
    return 0.0;
  }

  double gauss_hermite(const arma::mat *mean,
                       const arma::mat *cov,
                       double (*func)(const arma::mat *loc)) {
    return 0.0;
  }

  double gauss_hermite(const arma::mat *mean, const arma::mat *cov, double (*func)(const arma::mat *loc), size_t grid) {
    return 0.0;
  }
}
