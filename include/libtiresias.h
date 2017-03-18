#ifndef C_UTIL_H
#define C_UTIL_H

class c_rand_var_norm;

class tiresias {

    public:

        /**
         *  Quotes a price for a market and asset encoded in the JSON string.
         *
         *  \param json_string
         *  \return
         */
        static double quote_current_price(std::string json_string);

        /**
         *
         *
         *  \param json_string
         *  \return
         */
        static std::string update(std::string json_string);

    protected:

        /**
         *
         *
         *  \param json_string
         *  \return
         */
        static c_rand_var_norm json_to_rand_var_norm(std::string json_string);

        /**
         *  Quotes a price for a market encoded in current and an asset defined by the inequalities.
         *
         *  \param current
         *  \param inequalities
         *  \return
         */
        static double quote_current_price(c_rand_var_norm &current, arma::Mat<double>& inequalities);

        /**
         *
         *
         *  \param rand_var_norm
         *  \param inequalities
         *  \param prob
         *  \return
         */
        static c_rand_var_norm update(c_rand_var_norm& rand_var_norm, arma::Mat<double>& inequalities, double prob);

        /**
         *
         *
         *  \param json_string
         *  \return
         */
        static arma::Mat<double> json_to_inequalities(std::string json_string);

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

        static double quote_cost(double current_price, double delta_x);

        static double quote_cost(c_rand_var_norm &current, arma::Mat<double>& inequalities, double delta_x);

        static double shares_outstanding(c_rand_var_norm& current, arma::Mat<double>& inequalities);

        static double shares_outstanding(c_rand_var_norm& current, double price);


    private:
        static double obj_norm(unsigned n, const double *x, double *grad, void *data);
        static double con_norm(unsigned n, const double *x, double *grad, void *data);

        const static double PI;
        const static double SQRT_TWO;
        const static double WEIGHTS[];
        const static double ABS[];
        const static size_t QUADRATURE_DIM;
        const static double WEIGHT_FLOOR;

};

#endif // C_UTIL_H
