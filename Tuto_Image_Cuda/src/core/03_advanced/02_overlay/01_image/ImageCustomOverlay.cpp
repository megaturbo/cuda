#include "ImageCustomOverlay.h"

#include <iostream>

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

ImageCustomOverlay::ImageCustomOverlay(Animable_I<uchar4>* ptrAnimable,ColorRGB_01 colorTexte)
    :ImageAnimable_RGBA_uchar4(ptrAnimable,colorTexte)
    {
    // Tools
    this->ptrDrawer2D = new Drawer2D(ptrAnimable->getW(), ptrAnimable->getH());
    }

ImageCustomOverlay::~ImageCustomOverlay(void)
    {
    delete ptrKeyListener;
    delete ptrMouseListener;
    delete ptrDrawer2D;
    }

/*--------------------------------------*\
 |*		Methode 		*|
 \*-------------------------------------*/

/**
 * Override
 * call periodicly by the api
 */
void ImageCustomOverlay::paintPrimitives(Graphic2D& graphic2D)
    {
    ImageAnimable_RGBA_uchar4::paintPrimitives( graphic2D);

    float r = 1;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);
    graphic2D.setFont(TIMES_ROMAN_24);

    // Top
	{
	float t = getAnimable()->getAnimationPara();

	string title =getAnimable()->getTitle();

	graphic2D.drawTitleBottom(title);

	// Bottom
	    {
	    graphic2D.drawTitleTop("Advanced : Click on the windows, and look message in the console");
	    }
	}

    // Drawer2D
	{
	ptrDrawer2D->drawObjet(graphic2D);
	ptrDrawer2D->drawNonObjet(graphic2D);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

