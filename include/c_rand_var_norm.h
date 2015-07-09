#ifndef C_RAND_VAR_NORM_H
#define C_RAND_VAR_NORM_H

#include <armadillo>
#include <cmath>
#include "c_rand_var.h"

class c_rand_var_norm : public c_rand_var {

    public:

        c_rand_var_norm(size_t dim);
        virtual ~c_rand_var_norm();

        size_t get_dim_prob();
        void pack();
        void unpack();

        arma::mat& inv_cov();
        arma::mat& inv_ch();
        mat mean, cov, corr, ch, var;
        double norm_factor, det_cov, gauss_factor;

    protected:

        bool inv_cov_comp = false, inv_ch_comp = false;
        mat m_inv_cov, m_inv_ch;

};

#endif // C_RAND_VAR_NORM_H
