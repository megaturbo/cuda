#pragma once

#include <string>

#include "Capture_I.h"
#include "ImageViewer_I.h"

#include "Fps.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CVViewerUcharBGR: public ImageViewer_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	CVViewerUcharBGR(Capture_I* ptrCapture, const string& idWindow);
	virtual ~CVViewerUcharBGR(void);

	/*--------------------------------------*\
	|*		Override		*|
	 \*-------------------------------------*/

    public:

	virtual void start();
	virtual void stop();

	virtual int getFps(void);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:
	//Inputs
	string idWindow;
	Capture_I* ptrCapture;

	// Tools
	Fps fps;
	bool isFini;
	unsigned char* ptrPixels;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
