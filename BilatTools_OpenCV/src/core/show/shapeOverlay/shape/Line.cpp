#include "Line.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Line::Line(AppearanceShape* ptrAppearance, cv::Point p1, cv::Point p2) :
	Shape(ptrAppearance), p1(p1), p2(p2)
    {
    // Nothing
    }

Line::~Line()
    {
    // Nothing
    }

void Line::draw(cv::Mat* ptrImage)
    {
    AppearanceShape* ptrAppareance = getAppearance();
    line(*ptrImage,p1, p2, ptrAppareance->color, ptrAppareance->tickness, ptrAppareance->lineType);
    }

void Line::setP1(cv::Point p1)
    {
    this->p1 = p1;
    }

void Line::setP2(cv::Point p2)
    {
    this->p2 = p2;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

