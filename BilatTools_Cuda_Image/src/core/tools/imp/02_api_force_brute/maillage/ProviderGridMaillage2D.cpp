#include <iostream>

#include "ProviderGridMaillage2D.h"
#include "Device.h"

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

ProviderGridMaillage2D::ProviderGridMaillage2D(const VariateurData& variateurDgX, const VariateurData& variateurDgY, const VariateurData& variateurDbX,
	const VariateurData& variateurDbY) :
	variateurDgX(variateurDgX), variateurDgY(variateurDgY), variateurDbX(variateurDbX), variateurDbY(variateurDbY)
    {
    // rien
    }

ProviderGridMaillage2D::~ProviderGridMaillage2D()
    {
    // Rien
    }

GridMaillage ProviderGridMaillage2D::create()
    {
    int n = variateurDgX.getN() * variateurDgY.getN();
    int m = variateurDbX.getN() * variateurDbY.getN();
    GridMaillage gridMaillage(n, m);
    Grid* tabGrid = gridMaillage.getTabGrid();
    //std::cout << "ProviderGridMaillage2D::create(" << n << "x" << m << ")" << std::endl;
    int s = 0;
    for (int dgx = variateurDgX.min; dgx <= variateurDgX.max; dgx += variateurDgX.step)
	{
	for (int dgy = variateurDgY.min; dgy <= variateurDgY.max; dgy += variateurDgY.step)
	    {
	    dim3 dg(dgx, dgy, 1);
	    for (int dbx = variateurDbX.min; dbx <= variateurDbX.max; dbx += variateurDbX.step)
		{
		for (int dby = variateurDbY.min; dby <= variateurDbY.max; dby += variateurDbY.step)
		    {
		    dim3 db(dbx, dby, 1);
		    Grid grid(dg, db);
		    //std::cout<<"--- ["<<s<<"] ---"<<std::endl;
		    //Device::print(dg,db);
		    tabGrid[s] = grid;
		    s++;
		    }
		}
	    }
	}

    return gridMaillage;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

