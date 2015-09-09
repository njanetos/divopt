#ifndef C_UTIL_H
#define C_UTIL_H

#include "common.h"

#include "picojson.h"
#include <nlopt.hpp>

namespace divopt {

    class c_rand_var_norm;

    struct con_data {
        c_rand_var_norm *current;
        arma::Mat<real> inequalities;
        double p;
    };

    struct obj_data {
        c_rand_var_norm *current;
    };

    class utils {

        public:

            /**
             *
             *
             *  \param json_string
             *  \return
             */
            static real quote_current_price(std::string json_string);

            /**
             *
             *
             *  \param current
             *  \param inequalities
             *  \return
             */
            static real quote_current_price(c_rand_var_norm &current, arma::Mat<real>& inequalities);

            /**
             *
             *
             *  \param current_price
             *  \param delta_x
             *  \return
             */
            static real quote_cost(real current_price, real delta_x);

            /**
             *
             *
             *  \param current
             *  \param inequalities
             *  \param delta_x
             *  \return
             */
            static real quote_cost(c_rand_var_norm &current, arma::Mat<real>& inequalities, real delta_x);

            /**
             *
             *
             *  \param current
             *  \param inequalities
             *  \return
             */
            static real shares_outstanding(c_rand_var_norm &current, arma::Mat<real>& inequalities);

            /**
             *
             *  \param current
             *  \param price
             *  \return
             */
            static real shares_outstanding(c_rand_var_norm &current, real price);

            /**
             *
             *
             *  \param rand_var_norm
             *  \param inequalities
             *  \param prob
             *  \return
             */
            static c_rand_var_norm update(c_rand_var_norm& rand_var_norm, arma::Mat<real>& inequalities, real prob);

            /**
             *
             *
             *  \param json_string
             *  \return
             */
            static c_rand_var_norm update(std::string json_string);

            /**
             *
             *
             *  \param json_string
             *  \return
             */
            static std::string update_json(std::string json_string);

            /**
             *
             *
             *  \param json_string
             *  \return
             */
            static c_rand_var_norm json_to_rand_var_norm(std::string json_string);

            /**
             *
             *
             *  \param json_string
             *  \return
             */
            static arma::Mat<real> json_to_inequalities(std::string json_string);

            /**
             *
             *
             *  \param json_string
             *  \param key
             *  \return
             */
            static double get_double_json(std::string json_string, std::string key);

            /**
             *
             *
             *  \param rand_var_norm
             *  \return
             */
            static std::string rand_var_norm_to_json(c_rand_var_norm& rand_var_norm);

            const static double PI;
            const static double SQRT_TWO;
            const static double WEIGHTS[];
            const static double ABS[];
            const static size_t QUADRATURE_DIM;
            const static double WEIGHT_FLOOR;

        private:
            static real obj_norm(unsigned n, const double *x, double *grad, void *data);
            static real con_norm(unsigned n, const double *x, double *grad, void *data);


    };

}

#endif // C_UTIL_H
