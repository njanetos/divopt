#ifndef C_INEQUALITY_H
#define C_INEQUALITY_H

#include <stdlib.h>

namespace divopt {

    enum class e_binary_relation { GEQ, LEQ };

    /**
     * @brief Encodes information about an inequality in one dimension.
     */
    class c_inequality {

        public:

            /**
             *  Define a new inequality, e.g., x_5 > 0.3.
             *  \param dim The dimension of the state space on which this inequality acts, e.g., 5.
             *  \param The value on the left side, e.g., 0.3.
             *  \param The direction of the inequality, e.g., GEQ.
             */
            c_inequality(size_t dim, float val, e_binary_relation bin);

            /**
             *  Returns the dimension of the state space on which this inequality acts.
             *  \return The dimension.
             */
            size_t get_dim() const;

            /**
             *  Returns the value on the left hand side of the inequality.
             *  \return The value.
             */
            float get_val() const;

            /**
             *  Returns the direction of the binary relationship.
             *  \return The direction of the binary relation.
             */
            e_binary_relation get_binary_relation() const;

        protected:

            size_t dim;
            float val;
            e_binary_relation bin;

    };

}

#endif // C_INEQUALITY_H
