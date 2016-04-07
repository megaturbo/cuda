#include "LineDrawer.h"
#include <algorithm>
#include <assert.h>

#define CV_EPAISSEUR_MAX 255

#include <iostream>

using cv::Point2f;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * L'épaisseur maximal d'une line avec OpenCV égal 255
 * Nous on peut dessiner des line d'une épaisseur supérieur, jusqu'à max 765 car on dessine plusieur lignes côte à côte.
 */
void LineDrawer::drawLine(ShapeGroup* ptrShapeContainer, Point2i& p1, Point2i& p2, Scalar color, int epaisseur)
    {
    assert(epaisseur >= 1 && epaisseur <= 3 * CV_EPAISSEUR_MAX);

    if (epaisseur > CV_EPAISSEUR_MAX)
	{
	Point2f d = p2 - p1; // veteur directeur de la droite a dessiner (ie p1p2)

	// d orthogonal à P2P1 et normaliser (sur place)
	    {
	    float x = d.x;
	    d.x = -d.y;
	    d.y = x;
	    d *= 1.0 / norm(d);
	    }

	int largeurTraitAdditionel = -1;
	// allonger d à la bonne longuer (sur place)
	    {
	    largeurTraitAdditionel = computeLargeurTraitAdditionnel(epaisseur);
	    int lamda = CV_EPAISSEUR_MAX / 2 + largeurTraitAdditionel / 2; //pour s'eloigner du trait central (CV_EPAISSEUR_MAX/2)  pour être au milieu du trait additionnel ( largeurTraitAdditionel / 2)
	    d *= lamda;
	    }

	// On dessiner les 2 nouvelle lignes (une à droite et une à gauche)
	    {
	    AppearanceShape appearanceLineAdditionel(color, largeurTraitAdditionel);
	    Point2f p1f(p1.x, p1.y);
	    Point2f p2f(p2.x, p2.y);

	    Point2f p11 = p1f + d;
	    Point2f p21 = p2f + d;
	    Line* ptrLineAdditionel1 = new Line(&appearanceLineAdditionel, p11, p21);

	    Point2f p12 = p1f - d;
	    Point2f p22 = p2f - d;
	    Line* ptrLineAdditionel2 = new Line(&appearanceLineAdditionel, p12, p22);

	    ptrShapeContainer->add(ptrLineAdditionel1);
	    ptrShapeContainer->add(ptrLineAdditionel2);
	    }

	epaisseur = CV_EPAISSEUR_MAX;
	}

    // Ligne du centre ( ou unique si rayon > CV_R_MAX)
	{
	AppearanceShape appearanceLineCentre(color, epaisseur);
	Line* ptrLineCentre = new Line(&appearanceLineCentre, p1, p2);
	ptrShapeContainer->add(ptrLineCentre);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * hyp: epaisseur>CV_R_MAX
 */
int LineDrawer::computeLargeurTraitAdditionnel(int epaisseur)
    {
    assert(epaisseur > CV_EPAISSEUR_MAX);

    return (epaisseur - CV_EPAISSEUR_MAX) / 2;
    // return std::max(127 + (epaisseur - CV_R_MAX) / 2, 1);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

