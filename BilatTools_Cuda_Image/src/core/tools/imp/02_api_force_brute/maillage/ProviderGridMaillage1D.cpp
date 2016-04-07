#include "ProviderGridMaillage1D.h"
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

ProviderGridMaillage1D::ProviderGridMaillage1D(const VariateurData& variateurDg, const VariateurData& variateurDb) :
	variateurDg(variateurDg), variateurDb(variateurDb)
    {
    // rien
    }

ProviderGridMaillage1D::~ProviderGridMaillage1D()
    {
    // Rien
    }

GridMaillage ProviderGridMaillage1D::create()
    {
    int n=variateurDg.getN();
    int m=variateurDb.getN();
    GridMaillage gridMaillage(n, m);
    Grid* tabGrid = gridMaillage.getTabGrid();

    dim3 dg(variateurDg.min,1,1);
    for(int i=0;i<n;i++)
	{
	dim3 db(variateurDb.min,1,1);
	for(int j=0;j<m;j++)
	    {
	    int s=i*m+j;
	    Grid grid(dg,db);
	    tabGrid[s]=grid;

	    db.x+=variateurDb.step;
	    }

	dg.x+=variateurDg.step;
	}

    return gridMaillage;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

