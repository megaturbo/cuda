#include <iostream>

#include "FactoryImageViewer.h"
#include "CVCaptureWebcam.h"
#include "OpencvTools.h"

using std::cout;
using std::endl;
using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useWebcam(int w, int h, int deviceID);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void work(CVCaptureWebcam& webcam);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useWebcam(int w, int h, int deviceID)
    {
    CVCaptureWebcam webcam(w, h, deviceID);

    bool isOk = webcam.start();

    if (isOk)
	{
	work(webcam);

	webcam.stop();
	}
    else
	{
	exit (EXIT_FAILURE);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void work(CVCaptureWebcam& webcam)
    {
    const bool IS_V1 = true;

    // common
    CaptureMat_I* ptrCapture = (CaptureMat_I*) &webcam;
    const string ID_WINDOW = "tuto webcam";

    if (IS_V1)
	{
	ImageViewer_I* ptrViewer = FactoryImageViewer::create(ptrCapture, ID_WINDOW);
	ptrViewer->start();
	delete ptrViewer;
	}
    else
	{
	Mat matRGBA;
	bool isFini = false;

	while (!isFini)
	    {
	    Mat matBGR = ptrCapture->provideBGR();

	    isFini = OpencvTools::showBGR(matBGR, ID_WINDOW);
	    }

	OpencvTools::destroyFrame(ID_WINDOW);
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

