#pragma once

#include "Shape.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Polygon: public Shape
    {
    public:

	Polygon(AppearanceShape* ptrAppearance, cv::Point* ptrTabPoint, int nbPoints);

	virtual ~Polygon();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	void draw(cv::Mat* ptrImage);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	inline cv::Point* getTabPoints() const
	    {
	    return ptrTabPoint;
	    }

	inline int getNbPoints() const
	    {
	    return nbPoints;
	    }

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	void setTabPoints(cv::Point* ptrTabPoints,int nbPoints);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	cv::Point* ptrTabPoint;
	int nbPoints;

    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
