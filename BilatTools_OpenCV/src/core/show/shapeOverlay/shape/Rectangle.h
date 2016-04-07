#pragma once

#include "Shape.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Rectangle: public Shape
    {

	    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	Rectangle(AppearanceShape* ptrAppearance, cv::Point p1, cv::Point p2);

	Rectangle(AppearanceShape* ptrAppearance, cv::Point center, int w, int h);

	Rectangle(AppearanceShape* ptrAppearance, cv::Point center, int size);

	virtual ~Rectangle();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	// Override
	void draw(cv::Mat* ptrImage);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	inline cv::Point getP1() const
	    {
	    return p1;
	    }

	inline cv::Point getP2() const
	    {
	    return p2;
	    }

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	void setP1(cv::Point p1);

	void setP2(cv::Point p2);

	void set(cv::Point center, int w, int h);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	cv::Point p1;
	cv::Point p2;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
