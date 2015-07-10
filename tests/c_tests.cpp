/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_c_tests_init = false;
#include "/home/njanetos/Google Drive/Programming/divopt/tests/c_tests.h"

static c_tests suite_c_tests;

static CxxTest::List Tests_c_tests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_c_tests( "c_tests.h", 5, "c_tests", suite_c_tests, Tests_c_tests );

static class TestDescription_suite_c_tests_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_c_tests_testAddition() : CxxTest::RealTestDescription( Tests_c_tests, suiteDescription_c_tests, 7, "testAddition" ) {}
 void runTest() { suite_c_tests.testAddition(); }
} testDescription_suite_c_tests_testAddition;

static class TestDescription_suite_c_tests_test_rand_var_norm : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_c_tests_test_rand_var_norm() : CxxTest::RealTestDescription( Tests_c_tests, suiteDescription_c_tests, 12, "test_rand_var_norm" ) {}
 void runTest() { suite_c_tests.test_rand_var_norm(); }
} testDescription_suite_c_tests_test_rand_var_norm;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
