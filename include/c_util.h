#ifndef C_UTIL_H
#define C_UTIL_H

#include "common.h"

#include <stdlib.h>
#include <vector>

namespace divopt {

    class c_util
    {

        public:

            const static double PI;
            const static double SQRT_TWO;
            const static double WEIGHTS[];
            const static double ABS[];
            const static size_t QUADRATURE_DIM;
            const static double WEIGHT_FLOOR;

    };

}

#endif // C_UTIL_H
