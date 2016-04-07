#pragma once

#include <vector>

#include "Shape_I.h"

typedef std::vector<Shape_I*> vectorShape;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Warning : destructor delete shape!
 */
class ShapeGroup : public Shape_I
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ShapeGroup();

	virtual ~ShapeGroup();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	virtual void draw(cv::Mat* ptrImage);

	/**
	 * Warning : destructor delete shape!
	 */
	void add(Shape_I* ptrShape);

	void remove(Shape_I* ptrShape);

    private:

	void deleteAll();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	inline vectorShape getShapes() const
	    {
	    return vectorShapes;
	    }

	inline int size() const
	    {
	    return vectorShapes.size();
	    }

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:
	// Inputs
	vectorShape vectorShapes;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
