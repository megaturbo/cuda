#include "CVViewerUcharBGR.h"

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

CVViewerUcharBGR::CVViewerUcharBGR(Capture_I* ptrCapture, const string& idWindow) :
	fps("shower")
    {
    this->ptrCapture = ptrCapture;
    this->idWindow = idWindow;
    this->isFini = false;

    const int w = ptrCapture->getW();
    const int h = ptrCapture->getH();
    this->ptrPixels = new unsigned char[w * h * 4];
    }

CVViewerUcharBGR::~CVViewerUcharBGR(void)
    {
    OpencvTools::destroyFrame(idWindow);
    delete[] ptrPixels;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 */
void CVViewerUcharBGR::start()
    {
    const int w = ptrCapture->getW();
    const int h = ptrCapture->getH();
    Mat matRGBA(h, w, CV_8UC4, ptrPixels);
    Mat matBGRA(h, w, CV_8UC4);
    isFini = false;

    fps.activate();
    while (!isFini)
	{
	ptrCapture->captureRGBA(ptrPixels);
	OpencvTools::switchRB(matBGRA,matRGBA );// src, dest

	//fps.suspend();
	isFini = OpencvTools::showBGR(matBGRA, idWindow);
	//fps.activate();
	fps.acquire();
	//cout<<fps.fpsFloat()<<endl;
	}

    fps.suspend();
    OpencvTools::destroyFrame(idWindow);
    }

/**
 * Override
 */
void CVViewerUcharBGR::stop(void)
    {
    isFini = true;
    }

/**
 * Override
 */
int CVViewerUcharBGR::getFps(void)
    {
    return fps.fps();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

