#ifndef C_UTIL_H
#define C_UTIL_H

#include <stdlib.h>
#include <vector>
#include "c_inequality.h"
#include "c_constraint.h"

namespace divopt {

    class c_util
    {

        public:

            /**
             *  Combines two ORs into an AND, eliminating redundant inequality constraints,
             *  and returning an empty vector if the probability is zero.
             *  \param ineq1 Points to the first vector to combine.
             *  \param ineq2 Points to the second vector to combine.
             *  \return The result.
             */
            static std::vector<c_inequality> reduce(const std::vector<c_inequality> *ineq1,
                                                    const std::vector<c_inequality> *ineq2);

            /**
             *  Combines two ORs into an AND, eliminating redundant inequality constraints,
             *  and returning an empty vector if the probability is zero.
             *  \param constraint The constraint to draw the data from.
             *  \param dim1 The first set of ANDs to pull from.
             *  \param dim2 The second set of ANDs to pull from.
             *  \return The result.
             */
            static std::vector<c_inequality> reduce(c_constraint *constraint,
                                                    size_t dim1,
                                                    size_t dim2);

            /**
             *  Checks whether these two inequalities describe an empty event.
             *  \param ineq1 The first inequality.
             *  \param ineq2 The second inequality.
             *  \return True if, e.g., x1 > 0.2 AND x1 < 0.1.
             */
            static bool null_event(const c_inequality *ineq1,
                                   const c_inequality *ineq2);

            /**
             *  Returns true if the inequalities are well-defined.
             *  \param inequalities The inequalities to check
             *  \return True if they're well-defined, i.e., not a null event, and no nested inequalities.
             */
            static bool is_clean(const std::vector<c_inequality> *inequalities);

            /**
             *  Returns whether one inequality nests another inequality.
             *  \param ineq1 The first inequality.
             *  \param ineq2 The second inequality.
             *  \return -1 if neither nests the other, 0 if the first nests the second, etc.
             */
            static int is_nested(const c_inequality *ineq1,
                                 const c_inequality *ineq2);

            const static double PI;
            const static double SQRT_TWO;
            const static double WEIGHTS[];
            const static double ABS[];
            const static size_t QUADRATURE_DIM;
            const static double WEIGHT_FLOOR;

    };

}

#endif // C_UTIL_H
