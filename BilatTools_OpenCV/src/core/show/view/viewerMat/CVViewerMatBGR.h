#pragma once

#include <string>

#include "CaptureMat_I.h"
#include "ImageViewer_I.h"

#include "Fps.h"

using std::string;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CVViewerMatBGR: public ImageViewer_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	CVViewerMatBGR(CaptureMat_I* ptrCapture,const string& idWindow);
	virtual ~CVViewerMatBGR(void);

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
	CaptureMat_I* ptrCapture;

	// Tools
	Fps fps;
	bool isFini;


    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
