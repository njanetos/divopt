#include "utils.h"

#include "c_rand_var_norm.h"

real divopt::utils::quote_current_price(c_rand_var_norm& current, arma::Mat<real>& inequalities) {
    return current.cdf(inequalities);
}

real divopt::utils::quote_cost(real current_price, real delta_x) {
    return log(1-current_price) - log(exp(1-delta_x)/(exp(delta_x) - exp(1-delta_x)));
}

real divopt::utils::quote_cost(c_rand_var_norm &current, arma::Mat<real>& inequalities, real delta_x) {
    return quote_cost(quote_current_price(current, inequalities), delta_x);
}

real divopt::utils::shares_outstanding(c_rand_var_norm& current, arma::Mat<real>& inequalities) {
    return shares_outstanding(current, quote_current_price(current, inequalities));
}

real divopt::utils::shares_outstanding(c_rand_var_norm& current, real price) {
    return 1/(1 + log((1-price)/price));
}

divopt::c_rand_var_norm divopt::utils::update(c_rand_var_norm& rand_var_norm, int shares) {
    return rand_var_norm;
}

divopt::c_rand_var_norm divopt::utils::update(c_rand_var_norm& rand_var_norm, real prob) {
    return rand_var_norm;
}

const double divopt::utils::PI =         3.1415926535897932384626;
const double divopt::utils::SQRT_TWO =   1.4142135623730950488016;
const double divopt::utils::WEIGHTS[] ={ 0.0199532420590459132077,
                                         0.3936193231522411598285,
                                         0.9453087204829418812260,
                                         0.3936193231522411598285,
                                         0.0199532420590459132077};
const double divopt::utils::ABS[] = {   -2.0201828704560856329290,
                                        -0.9585724646138185071128,
                                         0.0000000000000000000000,
                                         0.9585724646138185071128,
                                         2.020182870456085632929};
const size_t divopt::utils::QUADRATURE_DIM = 5;
const double divopt::utils::WEIGHT_FLOOR = 0.000001;
