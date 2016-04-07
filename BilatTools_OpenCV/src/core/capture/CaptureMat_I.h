#pragma once

#include "Capture_I.h"

#include <opencv2/opencv.hpp>
using cv::Mat;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Capture_I contient pas de trace opencv! Peut etre utilise dans implementation v4l sans opencv
 * CaptureMat_I contient l'objet cv::Mat
 */
class CaptureMat_I: public Capture_I
    {

	/*--------------------------------------*\
	|*		Destructor		*|
	 \*-------------------------------------*/

    public:

	virtual ~CaptureMat_I()
	    {
	    }

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * opencv natural
	 */
	virtual Mat provideBGR()=0;

	virtual Mat BGRToRGBA(Mat& matBGR)=0;

    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
