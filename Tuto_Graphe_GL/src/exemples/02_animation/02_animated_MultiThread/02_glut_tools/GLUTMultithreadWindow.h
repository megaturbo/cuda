#pragma once

#include "GLUTGraphWindow.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class GLUTMultithreadWindow: public GLUTGraphWindow
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	GLUTMultithreadWindow(Graph* ptrGraph, string title, int width, int height, int pxFrame = 0, int pyFrame = 0);
	virtual ~GLUTMultithreadWindow();

	/*--------------------------------------*\
	|*		Methode		*|
	 \*-------------------------------------*/

	/**
	 * Override
	 */
	virtual void idleFunc();

	/**
	 * Override
	 */
	virtual void postRendu();
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
