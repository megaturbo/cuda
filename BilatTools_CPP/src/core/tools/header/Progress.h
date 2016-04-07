#pragma once

#include <iostream>
#include "Chrono.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Progress
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Progress(int n,string title,bool isVerbosityEnable=true);
	virtual ~Progress(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void incrementer();
	int get();
	int getIteration();
	Chrono getChrono();

    private:

	int nbStarToAdd();
	void printProgress();
	void printIntro();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int n;
	bool isVerbosityEnable;
	string title;

	// Tools
	int i;
	int avancement100;
	int nbStar;
	Chrono* ptrChrono;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
