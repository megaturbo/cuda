#include "Circle.h"

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

Circle::Circle(AppearanceShape* ptrAppearance, cv::Point center, int radius) :
	Shape(ptrAppearance), center(center), radius(radius)
    {
    // Nothing
    }

Circle::~Circle()
    {
    // Nothing
    }

void Circle::draw(cv::Mat* ptrImage)
    {
    AppearanceShape* ptrAppareance = getAppearance();
    circle(*ptrImage,center,radius, ptrAppareance->color, ptrAppareance->tickness, ptrAppareance->lineType);
    }

void Circle::setPoint(cv::Point center)
    {
    this->center = center;
    }

void Circle::setRadius(int radius)
    {
    this->radius = radius;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

