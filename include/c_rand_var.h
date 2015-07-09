#ifndef C_RAND_VAR_H
#define C_RAND_VAR_H

#include <stdlib.h>

class c_rand_var {

    public:

        /**
         *  Copies in data to the raw data. You have to run unpack() for the
         *  changes to be reflected.
         *
         *  \param dim_prob The dimension of the raw data vector.
         *  \param x Points to the data to copy.
         */
        void dat_to_dist(const double *x);

        /**
         *  Returns the dimension of the optimization problem.
         *
         *  \return The dimension of the optimization problem, not the dimension of the space.
         */
        virtual size_t get_dim_prob() =0;

        /**
         *  Takes the non-raw-data aspects and reads them into the raw data.
         */
        virtual void pack() =0;

        /**
         *  Partially copies in data to the raw data. You have to run unpack() for
         *  the changes to be reflected.
         *
         *  \param lower Starting index to copy into.
         *  \param upper Ending index to copy into.
         *  \param x The data to copy.
         */
        void partial_dat_to_dist(size_t lower, size_t upper, const double *x);

        /**
         *  Instantiates `non-raw-data' aspects of the distribution.
         */
        virtual void unpack() =0;

    protected:

        /**
         *  The dimension of the state space. (Not the optimization problem!)
         */
        size_t dim;

        /**
         *  The dimension of the problem. (Not the state space!)
         */
        size_t dim_prob;

        /**
        *  The raw data of the problem. Should be of length dim_prob.
        */
        double* raw_data;

};

#endif // C_RAND_VAR_H
