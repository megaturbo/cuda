#pragma once

#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class GridMaillage
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	GridMaillage(int n,int m=1);

	GridMaillage(int n,int m, Grid* tabGrid);

	GridMaillage(const GridMaillage& source);

	virtual ~GridMaillage();

	/*--------------------------------------*\
	 |*		Surcharge		*|
	 \*-------------------------------------*/

    public :

	GridMaillage& operator=(const GridMaillage& gridMaillage);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	inline Grid* getTabGrid() const
	    {
	    return tabGrid;
	    }

	inline int getN() const
	    {
	    return n;
	    }

	inline int getM() const
	    {
	    return m;
	    }

	/*
	 * @return n*m
	 */
	inline int size() const
	    {
	    return n*m;
	    }

	/**
	 * s in [0,nxm[
	 */
	int getNbThread(int s) const;

	/**
	 * i in [0,n[
	 * j in [0,m[
	 */
	int getNbThread(int i,int j) const;

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int n;
	int m;

	// Outputs
	Grid* tabGrid;

	//Tools
	bool isTabManaged;
    };

ostream& operator<<(ostream& stream, const GridMaillage& gridMaillage);



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
