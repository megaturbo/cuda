#pragma once

#include "../VariateurData.h"
#include "ProviderGridMaillage_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ProviderGridMaillage2D: public ProviderGridMaillage_I
    {
    public:

	ProviderGridMaillage2D(const VariateurData& variateurDgX, const VariateurData& variateurDgY, const VariateurData& variateurDbX,
		const VariateurData& variateurDbY);

	virtual ~ProviderGridMaillage2D();

	/*--------------------------------------*\
 |*		Surcharge		*|
	 \*-------------------------------------*/

    public:

	virtual GridMaillage create();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private :
	// Inputs
	VariateurData variateurDgX;
	VariateurData variateurDgY;
	VariateurData variateurDbX;
	VariateurData variateurDbY;


    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
