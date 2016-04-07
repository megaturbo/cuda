#pragma once

#include "../VariateurData.h"
#include "ProviderGridMaillage_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ProviderGridMaillage1D: public ProviderGridMaillage_I
    {
    public:

	ProviderGridMaillage1D(const VariateurData& variateurDg,const VariateurData& variateurDb);

	virtual ~ProviderGridMaillage1D();

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
	VariateurData variateurDg;
	VariateurData variateurDb;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
