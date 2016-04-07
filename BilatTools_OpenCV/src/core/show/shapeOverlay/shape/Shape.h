#pragma once

#include "Shape_I.h"
#include "AppearanceShape.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Shape: public Shape_I
    {
    public:
	Shape(AppearanceShape* ptrAppearance);

	virtual ~Shape();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	virtual void draw(cv::Mat* ptrImage)=0;

	inline AppearanceShape* getAppearance() const
	    {
	    return ptrAppearance;
	    }

	void setAppearance(AppearanceShape* ptrAppearance);

	/*-------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    protected:
	// Inputs
	AppearanceShape* ptrAppearance;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
