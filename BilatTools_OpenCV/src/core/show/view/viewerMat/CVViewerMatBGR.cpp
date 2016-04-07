#include "CVViewerMatBGR.h"

#include <OpencvTools.h>


using namespace cv;

using std::cout;
using std::endl;

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

CVViewerMatBGR::CVViewerMatBGR(CaptureMat_I* ptrCapture, const string& idWindow): fps("shower")
    {
    this->ptrCapture = ptrCapture;
    this->idWindow = idWindow;
    this->isFini = false;
    }

CVViewerMatBGR::~CVViewerMatBGR(void)
    {
    OpencvTools::destroyFrame(idWindow);
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 */
void CVViewerMatBGR::start()
    {
    isFini = false;

    fps.activate();
    while (!isFini)
	{
	Mat matBGR = ptrCapture->provideBGR();

	//fps.suspend();
	isFini = OpencvTools::showBGR(matBGR, idWindow);
	//fps.activate();
	fps.acquire();
	}

    fps.suspend();
    OpencvTools::destroyFrame(idWindow);
    }


/**
 * Override
 */
void CVViewerMatBGR::stop(void)
    {
    isFini=true;
    }


/**
 * Override
 */
int CVViewerMatBGR::getFps(void)
    {
    return fps.fps();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

