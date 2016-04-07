#include "Triangle.h"

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

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Triangle::Triangle(AppearanceShape* ptrAppearance, Point s1, Point s2, Point s3) :
	Polygon(ptrAppearance, Triangle::createPtrTabPoint(), Triangle::getNbPoints()), s1(s1),s2(s2),s3(s3)
    {
    fillPolygon(getTabPoints(), s1, s2, s3);
    }

Triangle::~Triangle()
    {
    // Triangle create ne TabPoint
    delete getTabPoints();
    }

void Triangle::set(cv::Point& s1,cv::Point& s2,cv::Point& s3)
    {
    this->s1=s1;
    this->s2=s2;
    this->s3=s3;
    fillPolygon(getTabPoints(), s1, s2, s3);
    }

/*----------------------------------------------------------------------*\
 |*			Static 						*|
 \*---------------------------------------------------------------------*/

/**
 * return 6 car 3 segment de 2 points!
 */
int Triangle::getNbPoints()
    {
    return 3 * 2;
    }

/**
 *
 */
void Triangle::fillPolygon(cv::Point* ptrPoint, cv::Point& s1, cv::Point& s2, cv::Point& s3)
    {
    ptrPoint[0] = s1;
    ptrPoint[1] = s2;

    ptrPoint[2] = s2;
    ptrPoint[3] = s3;

    ptrPoint[4] = s3;
    ptrPoint[5] = s1;
    }

cv::Point* Triangle::createPtrTabPoint()
    {
    return new Point[6];
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

