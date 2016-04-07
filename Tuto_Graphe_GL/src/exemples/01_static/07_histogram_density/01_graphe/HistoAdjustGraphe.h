#pragma once

#include "Graph.h"
#include "HistogramToDensity.h"

#include "GaussCurve.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Objectif :
 *
 *	Cr�er l'histogram d'un set de donn�es xi distribu� selon une lois normale.
 *	Dessiner par dessus l'histogram une courbe analytique de gauss afin de valider la distribution.
 *
 * Contrainte
 *
 * 	L'echelle entre la densite et l'histo doit etre la meme
 *
 */
class HistoAdjustGraphe: public Graph
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	HistoAdjustGraphe(float mean = 5, float stdDev = 10, int nbSeparation = 20, int nbPoint = 400000 * 10);

	virtual ~HistoAdjustGraphe();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    private:

	void createGraphe();
	void createCurve();
	void addCurve();

	void createDensity();
	void createHisto();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int nbPoint;
	int nbSeparation;
	float mean;
	float stdDev;

	// Tools
	HistogramToDensity* ptrHisto;
	GaussCurve* ptrGaussCurve;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
