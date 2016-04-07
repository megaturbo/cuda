#pragma once

#include "ShapeDrawer.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ShapeDrawerTransparant: public ShapeDrawer
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * ImageOutput = imageSource + shapeOpacity * shapes
	 */
	ShapeDrawerTransparant(cv::Mat imageSource, cv::Mat imageOutput, float shapeOpacity01);

	ShapeDrawerTransparant(cv::Mat imageSourceDestination,  float shapeOpacity01);

	virtual ~ShapeDrawerTransparant();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/
    public:

	// Override
	void draw(ShapeGroup* ptrShapeContainer);


    private:

	void combineImages();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	cv::Mat imageSource;
	cv::Mat imageOutput;
	float shapeOpacity01;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
