#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "c_rand_var_norm.h"
#include "c_logger.h"

TEST_CASE("Statistics and probability") {

    SECTION("PDF") {

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

        REQUIRE(std::abs(rand_var_norm.pdf(&location) - 0.061589) < 0.01);

    }

    SECTION("CDF") {

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

        REQUIRE(std::abs(rand_var_norm.cdf(&location) - 0.087040) < 0.05);

        location(0) = 0.2;
        location(1) = 0.1;

        REQUIRE(std::abs(rand_var_norm.cdf(&location) - 0.13182) < 0.05);

    }

    SECTION("Entropy and divergence") {

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

        REQUIRE(std::abs(rand_var_norm.ent(&location, &rand_var_norm2) + 0.72020) < 0.01);

        REQUIRE(std::abs(rand_var_norm.div(&rand_var_norm2) - 1.8025) < 0.01);

        REQUIRE(std::abs(rand_var_norm.div(&rand_var_norm)) < 0.01);

    }

}
