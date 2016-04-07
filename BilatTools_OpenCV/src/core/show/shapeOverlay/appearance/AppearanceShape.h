#pragma once

#include <opencv2/opencv.hpp>
#include <highgui.hpp>

using cv::Scalar;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class AppearanceShape
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * For filled shape set tickness to CV_FILLED
	 *
	 * default tickness = CV_FILLED
	 *
	 * lineType :
	 *
	 * 	8 	: 8 connected line
	 * 	4 	: 4 connected line
	 * 	CV_AA 	: antialiased line
	 *
	 */
	AppearanceShape(const Scalar& color=Scalar(255,255,255),const int tickness=CV_FILLED,const int lineType=8);


	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    public:

	// Inputs
	const Scalar color;
	const int tickness;
	const int lineType;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
