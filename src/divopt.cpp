#define GAUSS_FACTOR
#define

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

    mat expint = exp(-0.5*(locMat - mean).t()*inv_cov()*(locMat - mean));
    return norm_factor*expint(0);

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
