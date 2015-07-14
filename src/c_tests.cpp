#define CATCH_CONFIG_MAIN
#include <armadillo>
#include "catch.hpp"
#include "c_rand_var_norm.h"
#include "c_constraint.h"
#include "c_inequality.h"
#include "c_logger.h"
#include "c_util.h"

using namespace divopt;

TEST_CASE("Nuts and bolts") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[5];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 2;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    REQUIRE(rand_var_norm.get_dim() == 2);

    REQUIRE(rand_var_norm.get_dim_prob() == 5);

    REQUIRE(rand_var_norm.inv_cov()(0, 0) == 1.06250);

    arma::Mat<double> new_mean(2, 1);
    new_mean(0, 0) = 0.2;
    new_mean(1, 0) = 0.3;

    rand_var_norm.mean = new_mean;
    rand_var_norm.pack();
    rand_var_norm.unpack();

    REQUIRE( (rand_var_norm.mean(0, 0) == 0.2) );

    REQUIRE( (rand_var_norm.inv_ch()(0, 0) == 1) );

}

TEST_CASE("PDF") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[5];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 2;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    arma::Mat<double> location(2, 1);
    location(0) = 0.2;
    location(1) = 0.4;

    REQUIRE( (std::abs(rand_var_norm.pdf(&location) - 0.061589) < 0.01) );

}

TEST_CASE("CDF") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[5];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 2;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    arma::Mat<double> location(2, 1);
    location(0) = -0.2;
    location(1) = 0.1;

    REQUIRE( (std::abs(rand_var_norm.cdf(&location) - 0.087040) < 0.05) );

    location(0) = 0.2;
    location(1) = 0.1;

    REQUIRE( (std::abs(rand_var_norm.cdf(&location) - 0.13182) < 0.05) );

}

TEST_CASE("Divergence and entropy") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[5];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 2;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    c_rand_var_norm rand_var_norm2(2);

    double raw_data2[5];
    raw_data2[0] = 0;
    raw_data2[1] = 0;
    raw_data2[2] = 2;
    raw_data2[3] = 0.1;
    raw_data2[4] = 1;

    rand_var_norm2.dat_to_dist(raw_data2);
    rand_var_norm2.unpack();

    arma::Mat<double> location(2, 1);
    location(0) = -0.2;
    location(1) = 0.1;

    REQUIRE( (std::abs(rand_var_norm.ent(&location, &rand_var_norm2) + 0.72020) < 0.01) );

    REQUIRE( (std::abs(rand_var_norm.div(&rand_var_norm2) - 1.8025) < 0.01) );

    REQUIRE( (std::abs(rand_var_norm.div(&rand_var_norm)) < 0.01) );

}

TEST_CASE("Nuts and bolts of events") {

    c_inequality inequality1(0, 0.2, e_binary_relation::GEQ);
    c_inequality inequality2(1, -0.1, e_binary_relation::LEQ);
    c_inequality inequality3(0, 0.3, e_binary_relation::GEQ);
    c_inequality inequality4(0, 0.4, e_binary_relation::GEQ);

    c_constraint constraint;

    constraint.add_inequality(inequality1, 0);
    constraint.add_inequality(inequality2, 0);
    constraint.add_inequality(inequality3, 1);
    constraint.add_inequality(inequality4, 0);

    std::vector<c_inequality> comb;

    comb = divopt::c_util::reduce(&constraint, 0, 1);

    REQUIRE( comb.size() == 2 );

    REQUIRE( comb[0].get_val() == 0.2f );

}
