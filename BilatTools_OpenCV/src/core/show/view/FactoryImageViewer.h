#pragma once

#include "ImageViewer_I.h"
#include "Capture_I.h"
#include "CaptureMat_I.h"

#include <string.h>

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FactoryImageViewer
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/



    public:

	/*--------------------------------------*\
	|*		Override		*|
	 \*-------------------------------------*/

    public:

	/**
	 * use delete on ImageViewer_I* when you have finish to deal with it.
	 */
	static ImageViewer_I* create(Capture_I* ptrCapture, string ID_WINDOW);

	/**
	 * use delete on ImageViewer_I* when you have finish to deal with it.
	 */
	static ImageViewer_I* create(CaptureMat_I* ptrCapture, string ID_WINDOW);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
