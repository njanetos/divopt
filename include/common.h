#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <armadillo>

#define PRECISION   0.000001

typedef double real;

class c_rand_var_norm;

struct con_data {
    c_rand_var_norm *current;
    arma::Mat<double> inequalities;
    double p;
};

struct obj_data {
    c_rand_var_norm *current;
};

const double pi = 3.1415926535897932384626;
const double sqrt_two = 1.4142135623730950488016;

const double WEIGHTS[] ={ 0.0199532420590459132077,
                                         0.3936193231522411598285,
                                         0.9453087204829418812260,
                                         0.3936193231522411598285,
                                         0.0199532420590459132077};
const double ABS[] = {   -2.0201828704560856329290,
                                        -0.9585724646138185071128,
                                         0.0000000000000000000000,
                                         0.9585724646138185071128,
                                         2.020182870456085632929};
const size_t QUADRATURE_DIM = 5;
const double WEIGHT_FLOOR = 0.000001;

#endif // COMMON_H
