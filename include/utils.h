#ifndef C_UTIL_H
#define C_UTIL_H

#include "common.h"

#include "picojson.h"

namespace divopt {

    class c_rand_var_norm;

    class utils {

        public:

            static real quote_current_price(std::string json_string);
            static real quote_current_price(c_rand_var_norm &current, arma::Mat<real>& inequalities);
            static real quote_cost(real current_price, real delta_x);
            static real quote_cost(c_rand_var_norm &current, arma::Mat<real>& inequalities, real delta_x);
            static real shares_outstanding(c_rand_var_norm &current, arma::Mat<real>& inequalities);
            static real shares_outstanding(c_rand_var_norm &current, real price);
            static c_rand_var_norm update(c_rand_var_norm& rand_var_norm, arma::Mat<real>& inequalities, real prob);
            static c_rand_var_norm update(std::string json_string);
            static std::string update_json(std::string json_string);
            static c_rand_var_norm json_to_rand_var_norm(std::string json_string);
            static arma::Mat<real> json_to_inequalities(std::string json_string);
            static double get_double_json(std::string json_string, std::string key);
            static std::string rand_var_norm_to_json(c_rand_var_norm& rand_var_norm);

            const static double PI;
            const static double SQRT_TWO;
            const static double WEIGHTS[];
            const static double ABS[];
            const static size_t QUADRATURE_DIM;
            const static double WEIGHT_FLOOR;

    };

}

#endif // C_UTIL_H
