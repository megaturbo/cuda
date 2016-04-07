#pragma once

#include "Polygon.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Triangle : public Polygon
    {
    public:
	Triangle(AppearanceShape* ptrAppearance,cv::Point s1,cv::Point s2,cv::Point s3);

	virtual ~Triangle();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	static cv::Point* createPtrTabPoint();

	static void fillPolygon(cv::Point* ptrPoint,cv::Point& s1,cv::Point& s2,cv::Point& s3);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	static int getNbPoints();


	inline cv::Point getS1() const
	    {
	    return s1;
	    }

	inline cv::Point getS2() const
	    {
	    return s2;
	    }


	inline cv::Point getS3() const
	    {
	    return s3;
	    }

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	void set(cv::Point& s1,cv::Point& s2,cv::Point& s3);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private :

	// Inputs
	cv::Point s1;
	cv::Point s2;
	cv::Point s3;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
