#include "ShapeGroup.h"

#include <algorithm>
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

ShapeGroup::ShapeGroup()
    {

    }

ShapeGroup::~ShapeGroup()
    {
    deleteAll();
    }

void ShapeGroup::draw(cv::Mat* ptrImage)
    {
    Shape_I* ptrShape;
    for (vectorShape::iterator it = vectorShapes.begin(); it != vectorShapes.end(); ++it)
	{
	ptrShape = *it;
	ptrShape->draw(ptrImage);
	}
    }

void ShapeGroup::add(Shape_I* ptrShape)
    {
    vectorShapes.push_back(ptrShape);
    }

void ShapeGroup::remove(Shape_I* ptrShape)
    {
    std::remove(vectorShapes.begin(), vectorShapes.end(), ptrShape);
    }

void ShapeGroup::deleteAll()
    {
    Shape_I* ptrShape;
    for (vectorShape::iterator it = vectorShapes.begin(); it != vectorShapes.end(); ++it)
	{
	ptrShape = *it;
	if (ptrShape != NULL)
	    {
	    delete ptrShape;
	    }
	}
    vectorShapes.clear();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

