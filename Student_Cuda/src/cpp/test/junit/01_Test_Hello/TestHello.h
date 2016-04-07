#pragma once

#include "cpptest.h"

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestHello: public Suite
    {
    public:

	TestHello(int deviceId);

    private:

	void testHelloCuda(void);
	void testAdd(void);

    private:

	int deviceId;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

