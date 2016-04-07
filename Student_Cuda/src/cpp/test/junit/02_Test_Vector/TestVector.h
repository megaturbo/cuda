#pragma once

#include "cpptest.h"

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestVector: public Suite
    {
    public:

	TestVector(int deviceId);

    private:

	void testAdd(void);

    private:

	int deviceId;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

