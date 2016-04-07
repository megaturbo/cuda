#include <iostream>

#include "FactoryImageViewer.h"
#include "CVCaptureVideo.h"
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

void useVideo(string nameFile);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void work(CVCaptureVideo& video);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useVideo(string nameFile)
    {
    CVCaptureVideo video(nameFile);

    bool isOk = video.start();

    if (isOk)
	{
	work(video);

	video.stop();
	}
    else
	{
	exit (EXIT_FAILURE);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void work(CVCaptureVideo& video)
    {
    const bool IS_V1 = true;

    // common
    CaptureMat_I* ptrCapture = (CaptureMat_I*) &video;
    const string ID_WINDOW = "tuto video";

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

