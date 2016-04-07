#include "Rectangle.h"
using namespace cv;

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

static cv::Point compute_p1(const cv::Point& center, const int& w, const int& h);

static cv::Point compute_p2(const cv::Point& center, const int& w, const int& h);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Rectangle::Rectangle(AppearanceShape* ptrAppearance, cv::Point p1, cv::Point p2) :
	Shape(ptrAppearance), p1(p1), p2(p2)
    {
    // Nothing
    }

Rectangle::Rectangle(AppearanceShape* ptrAppearance, cv::Point center, int w, int h) :
	Shape(ptrAppearance), p1(compute_p1(center, w, h)), p2(compute_p2(center, w, h))
    {
    // Nothing
    }

Rectangle::Rectangle(AppearanceShape* ptrAppearance, cv::Point center, int size) :
	Shape(ptrAppearance), p1(compute_p1(center, size, size)), p2(compute_p2(center, size, size))
    {
    // Nothing
    }

Rectangle::~Rectangle()
    {
    // Nothing
    }

void Rectangle::draw(cv::Mat* ptrImage)
    {
    AppearanceShape* ptrAppareance = getAppearance();
    rectangle(*ptrImage, p1, p2, ptrAppareance->color, ptrAppareance->tickness, ptrAppareance->lineType);
    }

void Rectangle::setP1(cv::Point p1)
    {
    this->p1 = p1;
    }

void Rectangle::setP2(cv::Point p2)
    {
    this->p2 = p2;
    }

void Rectangle::set(cv::Point center, int w, int h)
    {
    this->p1 = compute_p1(center, w, h);
    this->p2 = compute_p2(center, w, h);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

cv::Point compute_p1(const cv::Point& center, const int& w, const int& h)
    {
    return Point(center.x - w / 2, center.y - h / 2);
    }

cv::Point compute_p2(const cv::Point& center, const int& w, const int& h)
    {
    return Point(center.x + w / 2, center.y + h / 2);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

