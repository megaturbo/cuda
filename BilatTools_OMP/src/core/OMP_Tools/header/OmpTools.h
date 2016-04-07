#pragma once

#include <omp.h>
#include <iostream>

#include "ParallelPatern.h"

using std::string;



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class OmpTools
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	OmpTools();

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~OmpTools();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	/**
	 * autant de thread que de core
	 */
	static int setAndGetNaturalGranularity();

	static void setNbThread(int nbThread);


	static string toString(ParallelPatern parallelPatern);

	/**
	 * Warning : A utiliser uniquement dans une section parallel!!!! sionon return 1!
	 */
	static int getNbThread();
	static int getNbCore();
	static int getTid();

	/**
	 * Thread safe
	 * [0,1[
	 */
	static double uniform01(void);

	/**
	 * Thread safe
	 * [a,b[
	 */
	static double uniform(double a, double b);

    private:

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
