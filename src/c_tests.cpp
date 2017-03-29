#define CATCH_CONFIG_MAIN
#include <armadillo>
#include "catch.hpp"
#include "c_rand_var_norm.h"
#include "c_logger.h"
#include "libtiresias.h"

TEST_CASE("Nuts and bolts") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[10];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 4.25;
    raw_data[5] = 1;
    raw_data[6] = 1;
    raw_data[7] = 1;
    raw_data[8] = 1;
    raw_data[9] = 1;

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

}

TEST_CASE("PDF") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[10];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 4.25;
    raw_data[5] = 1;
    raw_data[6] = 1;
    raw_data[7] = 1;
    raw_data[8] = 1;
    raw_data[9] = 1;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    arma::Mat<double> location(2, 1);
    location(0) = 0.2;
    location(1) = 0.4;

    REQUIRE( (std::abs(rand_var_norm.pdf(location) - 0.061589) < 0.01) );

}

TEST_CASE("CDF") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[10];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 4.25;
    raw_data[5] = 1;
    raw_data[6] = 1;
    raw_data[7] = 1;
    raw_data[8] = 1;
    raw_data[9] = 1;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    arma::Mat<real> inequalities(2, 2);
    inequalities(0, 0) = -1*std::numeric_limits<real>::infinity();
    inequalities(1, 0) = -1*std::numeric_limits<real>::infinity();
    inequalities(0, 1) = -0.2;
    inequalities(1, 1) = 0.1;

    REQUIRE( (std::abs(rand_var_norm.cdf(inequalities) - 0.087040) < 0.05) );

    inequalities(0, 1) = 0.2;
    inequalities(1, 1) = 0.1;

    REQUIRE( (std::abs(rand_var_norm.cdf(inequalities) - 0.13182) < 0.05) );

    inequalities(0, 0) = -0.2;
    inequalities(1, 0) = -0.1;

    REQUIRE( (std::abs(rand_var_norm.cdf(inequalities) - 0.00373) < 0.05) );

    inequalities(0, 0) = -0.2;
    inequalities(1, 0) = -0.1;

    REQUIRE( (std::abs(rand_var_norm.cdf(inequalities) - 0.00373) < 0.05) );
}

TEST_CASE("Divergence and entropy") {

    c_rand_var_norm rand_var_norm(2);

    double raw_data[10];
    raw_data[0] = 1;
    raw_data[1] = 1;
    raw_data[2] = 1;
    raw_data[3] = 0.5;
    raw_data[4] = 4.25;
    raw_data[5] = 1;
    raw_data[6] = 1;
    raw_data[7] = 1;
    raw_data[8] = 1;
    raw_data[9] = 1;

    rand_var_norm.dat_to_dist(raw_data);
    rand_var_norm.unpack();

    c_rand_var_norm rand_var_norm2(2);

    double raw_data2[10];
    raw_data2[0] = 0;
    raw_data2[1] = 0;
    raw_data2[2] = 4;
    raw_data2[3] = 0.2;
    raw_data2[4] = 1;
    raw_data[5] = 1;
    raw_data[6] = 1;
    raw_data[7] = 1;
    raw_data[8] = 1;
    raw_data[9] = 1;

    rand_var_norm2.dat_to_dist(raw_data2);
    rand_var_norm2.unpack();

    arma::Mat<double> location(2, 1);
    location(0) = -0.2;
    location(1) = 0.1;

    REQUIRE( (std::abs(rand_var_norm.ent(location, rand_var_norm2) + 0.72020) < 0.01) );

    REQUIRE( (std::abs(rand_var_norm.div(rand_var_norm2) - 1.82326) < 0.01) );

    REQUIRE( (std::abs(rand_var_norm.div(rand_var_norm)) < 0.01) );

}

TEST_CASE("Update and quote") {
  //c_rand_var_norm rand_var_norm(5);

  std::string json;

  json = "{ \"dim\": 5, \"raw\": [0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],  \"low\": [\"-INF\", \"-INF\", \"-INF\", \"-INF\", \"-INF\"], \"high\": [\"INF\", \"INF\", \"INF\", \"INF\", \"INF\"]}";
  REQUIRE( (std::abs(tiresias::quote(json) - 100) < 0.01) );

  json = "{ \"dim\": 5, \"raw\": [0.1, 0.2, 0.15, 0.1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],  \"low\": [0, 0, 0, 0, 0], \"high\": [\"INF\", \"INF\", \"INF\", \"INF\", \"INF\"]}";
  REQUIRE( (std::abs(tiresias::quote(json) - 4.7233) < 0.01) );

  json = "{ \"dim\": 2, \"raw\": [0, 0, 1, 0, 1, 1, 1, 1, 1, 1],  \"low\": [\"-INF\", \"-INF\"], \"high\": [0, 0], \"prob\": 0.4}";
  c_rand_var_norm rand_var_norm_upd = tiresias::json_to_rand_var_norm(tiresias::update(json));
  std::cout << rand_var_norm_upd.mean << rand_var_norm_upd.cov;
  REQUIRE( (std::abs(rand_var_norm_upd.mean[0] + 0.2745) < 0.01) );

  json = "{ \"dim\": 2, \"raw\": [0, 0, 1, 0, 1, 1, 1, 0, 0, 0],  \"low\": [\"-INF\", \"-INF\"], \"high\": [0, 0], \"prob\": 0.4}";
  rand_var_norm_upd = tiresias::json_to_rand_var_norm(tiresias::update(json));
  REQUIRE( (std::abs(rand_var_norm_upd.mean[0] + 0.3385) < 0.01) );
}

TEST_CASE("Nuts and bolts of events") {


}
