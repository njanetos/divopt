#ifndef C_CONSTRAINT_H
#define C_CONSTRAINT_H

#include "c_inequality.h"
#include "c_rand_var.h"

/**
 * @brief Encodes information about a constraint on a random variable.
 *
 * Constraints take the form of a logical list of constraints on the CDF,
 * together with a probability. For example, one constraint we might like
 * to encode would be 'The probability that x1 < 0.3 AND x2 > 0.1 OR
 * x1 > -0.1 is 0.25'. The class encodes that information in the following
 * way: The vector inequalities would have two elements, each of which is
 * a vector of @c c_inequality. The first vector is of length two, and
 * represents 'x1 < 0.3 AND x2 > 0.1', the second vector of is of length
 * 1, and represents 'x1 > -0.1'.
 */
class c_constraint {
    public:

        /**
         *  Initializes a new, empty set of constraints.
         */
        c_constraint();

        virtual ~c_constraint();

        /**
         *  Adds an inequality onto the last set of ANDs.
         *  \param inequality The inequality to add.
         */
        void add_inequality(c_inequality inequality);

        /**
         *  Adds a vector of AND inequalities.
         *  \param inequalities A vector of inequalities.
         */
        void add_inequality(std::vector<c_inequality> inequalities);

        /**
         *  Adds an AND inequality at position @p pos.
         *  \param inequality The inequality to add.
         *  \param pos The position to add it at.
         */
        void add_inequality(c_inequality inequality, size_t pos);

        /**
         *  Tests whether the given constraint is satisfied against
         *  @p rand_var.
         *  \param rand_var The random variable to test against.
         */
        bool is_satisfied(c_rand_var rand_var);

        /**
         *  Sets the probability of the described conditions holding.
         *  \param prob The probability.
         */
        void set_prob(double prob);

    protected:

        std::vector< std::vector<c_inequality> > inequalities;
        float prob;

    private:
};

#endif // C_CONSTRAINT_H
