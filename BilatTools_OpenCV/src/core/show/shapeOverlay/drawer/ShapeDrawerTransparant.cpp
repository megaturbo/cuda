#include "ShapeDrawerTransparant.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

ShapeDrawerTransparant::ShapeDrawerTransparant(cv::Mat imageSource, cv::Mat imageOutput, float shapeOpacity01) :
	ShapeDrawer(imageSource.clone()), imageSource(imageSource), imageOutput(imageOutput), shapeOpacity01(shapeOpacity01)
    {
    // Nothing
    }

ShapeDrawerTransparant::ShapeDrawerTransparant(cv::Mat imageSourceDestination, float shapeOpacity01) :
	ShapeDrawer(imageSourceDestination.clone()), imageSource(imageSourceDestination), imageOutput(imageSourceDestination), shapeOpacity01(shapeOpacity01)
    {
    // Nothing
    }

ShapeDrawerTransparant::~ShapeDrawerTransparant()
    {
    // Nothing
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

// Override
void ShapeDrawerTransparant::draw(ShapeGroup* ptrShapeGroup)
    {
    ShapeDrawer::draw(ptrShapeGroup);

    combineImages();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void ShapeDrawerTransparant::combineImages()
    {
    addWeighted(overlay, shapeOpacity01, imageSource, 1 - shapeOpacity01, 0, imageOutput);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

