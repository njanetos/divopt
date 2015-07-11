#include <cxxtest/TestSuite.h>
#include "../include/divopt.h"
#include "../include/c_rand_var_norm.h"
#include <math.h>

class c_tests : public CxxTest::TestSuite {
  public:
    void test_pdf(void) {
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

      TS_ASSERT( std::abs(rand_var_norm.pdf(&location) - 0.061589) < 0.01 );
    }
};
