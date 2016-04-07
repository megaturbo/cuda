#pragma once

#include "LaunchMode.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {

    class Settings
	{
	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/

	public:

	    Settings(LaunchMode launchMode, int deviceId, int argc, char** argv);

	    /*--------------------------------------*\
	|*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    int getDeviceId() const;

	    LaunchMode getLauchMode() const;

	    int getArgc() const;
	    char** getArgv() const;

	    /*--------------------------------------*\
	|*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    // Input / Output
	    LaunchMode launchMode;
	    int deviceId;

	    // Input console
	    int argc;
	    char** argv;
	};
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
