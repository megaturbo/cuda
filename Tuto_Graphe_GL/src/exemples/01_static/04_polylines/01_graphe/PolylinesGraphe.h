#pragma once

#include "Graph.h"
#include "Polylines.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Objectif :
 *
 *	 Affiche une polyligne suivant un ensemble de point (xi,yi)
 *
 * Exemple:
 *
 * 	Un cercle
 */
class PolylinesGraphe : public Graph
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	PolylinesGraphe(int nbPoint=20);

	virtual ~PolylinesGraphe();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    private:

	void createGraphe();

	void createCurve();

	void addCurve();

	void fillTabPointXY(shared_array<Point> ptrTabPointXY);

	/*--------------------------------------*\
	 |*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Input
	int nbPoint;

	// Tools
	Polylines* ptrPolyline;

	double x0;
	double y0;
	double r;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
