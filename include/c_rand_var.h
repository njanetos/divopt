#ifndef C_RAND_VAR_H
#define C_RAND_VAR_H

#include <stdlib.h>
#include <vector>
#include <armadillo>
#include "c_inequality.h"

namespace divopt {

    /**
     * @brief Represents a random variable.
     *
     * Abstract class that represents a random variable. Contains
     * functions for finding the cdf, the pdf, the entropy, the
     * divergence, and the gradients of all these things. Every
     * random variable is represented by a vector of raw data,
     * implementing classes are responsible for packing and
     * unpacking that raw data to form the elements of the random
     * variable itself. The gradients are always with respect to the
     * vector of raw data.
     */
    class c_rand_var {

        public:

            /**
             *  Returns the cumulative density at a location.
             *
             *  \param loc The location to compute the cumulative density at.
             *  \return The cumulative density.
             */
            virtual double cdf(arma::mat *loc) =0;

            /**
             *  Returns the probability of some event.
             *
             *  \param inequalities The inequalities that define the event.
             *  \return The cumulative density.
             */
            virtual double cdf(std::vector<c_inequality> *inequalities) =0;

            /**
             *  Computes the gradient of my cdf at some location.
             *
             *  \param loc Where to evaluate the cdf.
             *  \return Vector containing the gradient.
             */
            virtual arma::mat cdf_grad(arma::mat *loc) =0;

            /**
             *  Copies in data to the raw data. You have to run unpack() for the
             *  changes to be reflected.
             *
             *  \param dim_prob The dimension of the raw data vector.
             *  \param x Points to the data to copy.
             */
            void dat_to_dist(const double *x);

            /**
             *  Computes the divergence.
             *
             *  \param var The distribution to find the divergence against.
             *  \return The Kullback-Leibler divergence.
             */
            virtual double div(c_rand_var *var) =0;

            /**
             *  Computes the gradient of the divergence between this random variable and
             *  another.
             *
             *  \param oth The other random variable to compute against.
             *  \return A vector containing the gradient.
             */
            virtual arma::mat div_grad(c_rand_var *oth) =0;

            /**
             *  Computes the entropy.
             *
             *  \param loc The location to compute the entropy at.
             *  \param var The distribution to measure the entropy against.
             *  \return The relative entropy at some location.
             */
            virtual double ent(arma::mat *loc, c_rand_var *var) =0;

            /**
             *  Returns the dimension of the state space. (Not the optimization problem!)
             *  \return The dimension of the state space.
             */
            double get_dim();

            /**
             *  Returns the dimension of the optimization problem. (Not the state space!)
             *  \return The dimension of the optimization problem.
             */
            double get_dim_prob();

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
             *  Returns the density at a location.
             *
             *  \param loc The location to compute the density at.
             *  \return The density.
             */
            virtual double pdf(arma::mat *loc) =0;

            /**
             *  Returns the gradient of the density at some location.
             *
             *  \param loc The location to compute the gradient at.
             *  \return A vector with the gradient.
             *
             */
            virtual arma::mat pdf_grad(arma::mat *loc) =0;

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
            std::vector<double> raw_data;

    };

}

#endif // C_RAND_VAR_H
