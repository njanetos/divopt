#ifndef C_UTIL_H
#define C_UTIL_H

#include "common.h"

namespace divopt {

    class c_rand_var_norm;

    class utils {

        public:

            static real quote_current_price(c_rand_var_norm &current, arma::Mat<real>& inequalities);
            static real quote_cost(real current_price, real delta_x);
            static real quote_cost(c_rand_var_norm &current, arma::Mat<real>& inequalities, real delta_x);
            static real shares_outstanding(c_rand_var_norm &current, arma::Mat<real>& inequalities);
            static real shares_outstanding(c_rand_var_norm &current, real price);
            static c_rand_var_norm update(c_rand_var_norm& rand_var_norm, int shares);
            static c_rand_var_norm update(c_rand_var_norm& rand_var_norm, real prob);

            const static double PI;
            const static double SQRT_TWO;
            const static double WEIGHTS[];
            const static double ABS[];
            const static size_t QUADRATURE_DIM;
            const static double WEIGHT_FLOOR;

    };

}

#endif // C_UTIL_H
