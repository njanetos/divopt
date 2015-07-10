#include <cxxtest/TestSuite.h>
#include "../include/divopt.h"
#include "../include/c_rand_var_norm.h"

class c_tests : public CxxTest::TestSuite {
  public:
    void testAddition( void ) {
      TS_ASSERT( 1 + 1 > 1 );
      TS_ASSERT_EQUALS( 1 + 1, 2 );
    }

    void test_rand_var_norm(void) {
      c_rand_var_norm rand_var_norm(5);
      TS_ASSERT(1+1 > 1);
    }
};
