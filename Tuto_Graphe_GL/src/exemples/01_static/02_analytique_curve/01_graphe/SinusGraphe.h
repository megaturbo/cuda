#pragma once

#include "Graph.h"
#include "SinusCurve.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Objectif :
 *
 *	 Affiche la fonction a*sin entre 0 et 2 PI, grace � une formule analytique
 *
 */
class SinusGraphe: public Graph
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	SinusGraphe(float a = 1.0f);

	virtual ~SinusGraphe();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    private:

	void createGraphe();
	void createCurve();
	void addCurve();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	SinusCurve* getSinusCurve();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Input
	float a;

	// Tools
	SinusCurve* ptrSinusCurve;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
