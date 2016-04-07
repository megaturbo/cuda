#pragma once

#include "shapes.h"
#include "ShapeOverlay.h"

#include <opencv2/opencv.hpp>

using cv::Point2i;
using cv::Scalar;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class LineDrawer
    {

	/*--------------------------------------*\
	 |*	 Methodes static		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Problem:
	 * 	L'épaisseur maximal d'une line avec OpenCV égal 255 (thinkness assert in opencv code)
	 *
	 * Goal:
	 * 	Permetter de dessiner des lignes avec une épaisseur plus grande jusquant 3*255
	 *
	 * Technique:
	 * 	On dessine 3 lignes cote à cote pour arriver à la largeur voulue
	 */
	static void drawLine(ShapeGroup* ptrShapeContainer, Point2i& p1, Point2i& p2, Scalar color, int epaisseur);

    private:

	static int computeLargeurTraitAdditionnel(int epaisseur);

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
