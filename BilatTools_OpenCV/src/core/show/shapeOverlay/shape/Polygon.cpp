#include "Polygon.h"
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
 |*		Public			*|
 \*-------------------------------------*/

Polygon::Polygon(AppearanceShape* ptrAppearance, cv::Point* ptrTabPoint, int nbPoints) :
	Shape(ptrAppearance), ptrTabPoint(ptrTabPoint), nbPoints(nbPoints)
    {
    // Nothing
    }

Polygon::~Polygon()
    {
    // Nothing
    }

void Polygon::draw(cv::Mat* ptrImage)
    {
    AppearanceShape* ptrAppareance = getAppearance();
    const cv::Point* ppt[1] =
	{
	ptrTabPoint
	};
    int tabSize[1] =
	{
	nbPoints
	};

    fillPoly(*ptrImage, ppt, tabSize, 1, ptrAppareance->color, ptrAppareance->lineType);
    }

void Polygon::setTabPoints(cv::Point* ptrTabPoints, int nbPoints)
    {
    this->ptrTabPoint = ptrTabPoint;
    this->nbPoints = nbPoints;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

