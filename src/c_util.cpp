#include "c_util.h"

using namespace divopt;

const double divopt::c_util::PI =         3.1415926535897932384626;
const double divopt::c_util::SQRT_TWO =   1.4142135623730950488016;
const double divopt::c_util::WEIGHTS[] ={ 0.0199532420590459132077,
                                          0.3936193231522411598285,
                                          0.9453087204829418812260,
                                          0.3936193231522411598285,
                                          0.0199532420590459132077};
const double divopt::c_util::ABS[] = {   -2.0201828704560856329290,
                                         -0.9585724646138185071128,
                                          0.0000000000000000000000,
                                          0.9585724646138185071128,
                                          2.020182870456085632929};
const size_t divopt::c_util::QUADRATURE_DIM = 5;
const double divopt::c_util::WEIGHT_FLOOR = 0.000001;
