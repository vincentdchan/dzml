// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ScannerTest.h"
#include <boost/bind.hpp>
#include <iostream>

test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	boost::shared_ptr<ScannerTest> tester(new ScannerTest);

	framework::master_test_suite().
		add(BOOST_TEST_CASE(boost::bind(&ScannerTest::TestMethod1, tester)));
	framework::master_test_suite().
		add(BOOST_TEST_CASE(boost::bind(&ScannerTest::TestMethod2, tester)));

	return 0;
}
