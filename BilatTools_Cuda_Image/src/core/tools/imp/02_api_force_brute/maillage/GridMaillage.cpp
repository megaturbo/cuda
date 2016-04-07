#include <stdlib.h>

#include "GridMaillage.h"



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

GridMaillage::GridMaillage(int n, int m) :
	tabGrid(new Grid[n * m])
    {
    this->n = n;
    this->m = m;
    this->isTabManaged = true;
    }

GridMaillage::GridMaillage(int n, int m, Grid* tabGrid) :
	tabGrid(tabGrid)
    {
    this->n = n;
    this->m = m;
    this->isTabManaged = false;
    }

GridMaillage::GridMaillage(const GridMaillage& source) :
	tabGrid(new Grid[source.size()])
    {
    this->n = source.n;
    this->m = source.m;
    this->isTabManaged = true;

    for (int i = 0; i < size(); i++)
	{
	tabGrid[i] = source.tabGrid[i];
	}
    }

GridMaillage::~GridMaillage()
    {
    if (isTabManaged && tabGrid != NULL)
	{
	delete[] tabGrid;
	tabGrid = NULL;
	}
    }

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

GridMaillage& GridMaillage::operator=(const GridMaillage& source)
    {
    n = source.n;
    m = source.m;

    for (int i = 0; i < size(); i++)
	{
	tabGrid[i] = source.tabGrid[i];
	}

    return *this;
    }

int GridMaillage::getNbThread(int s) const
    {
    return tabGrid[s].threadCounts();
    }

int GridMaillage::getNbThread(int i, int j) const
    {
    int s = i * m + j;
    return getNbThread(s);
    }

ostream& operator<<(ostream& stream, const GridMaillage& gridMaillage)
    {
    Grid* ptrTabGrid = gridMaillage.getTabGrid();
    const int size = gridMaillage.getN() * gridMaillage.getM();

    stream << "dg x db :" << std::endl;
    for (int i = 1; i <= size; i++)
	{
	stream << "(" << ptrTabGrid[i - 1].dg.x << "," << ptrTabGrid[i - 1].dg.y << "," << ptrTabGrid[i - 1].dg.z << ")";
	stream << "x";
	stream << "(" << ptrTabGrid[i - 1].db.x << "," << ptrTabGrid[i - 1].db.y << "," << ptrTabGrid[i - 1].db.z << ")";
	stream << "\t";

	if (i % gridMaillage.getM() == 0)
	    {
	    stream << std::endl;
	    }
	}
    return stream;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

