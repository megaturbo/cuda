#pragma once

#include "cpptest.h"
#include "integer.h"

class TestIntegerJunit: public Test::Suite
    {
public:

    TestIntegerJunit(void)
	{
	TEST_ADD(TestIntegerJunit::testAdd);
	TEST_ADD(TestIntegerJunit::testFois);
	}

private:

    void testAdd(void)
	{
	int a = 2;
	int b = 3;

	TEST_ASSERT(plus(a, b) == 5);
	TEST_ASSERT(plus(-a, b) == 1);
	}

    void testFois(void)
	{
	int a = 2;
	int b = 3;

	TEST_ASSERT(fois(a, b) == 6);
	TEST_ASSERT(fois(-a, b) == -6);
	}
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


