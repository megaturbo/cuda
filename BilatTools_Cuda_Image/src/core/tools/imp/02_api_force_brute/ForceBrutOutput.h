#pragma once

#include <string>
#include <vector>
#include <ostream>

#include "GridFps.h"
#include "GridMaillage.h"

using std::vector;
using std::string;
using std::ostream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ForceBrutOutput
    {
	/*--------------------------------------*\
 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ForceBrutOutput(GridMaillage& gridMaillage);

	ForceBrutOutput(const ForceBrutOutput& source);

	virtual ~ForceBrutOutput();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	ForceBrutOutput& operator=(const ForceBrutOutput& source);

	string toStringFps() const;

	string toStringThreadByBlock() const;

	string toStringThreadTotal() const;

	string toStringNbBlocks() const;


	void print(ostream& stream, const string& titre = "") const;
	friend ostream& operator <<(ostream& stream, const ForceBrutOutput& forceBrutOutput);

	void save(string prefixe) const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

    public:

	void setFps(int s, int fps);

	void setFps(int i, int j, int fps);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	/**
	 *  Dans le cas ou la grille est generer automatiquement par le choix des variateurs,
	 *  le tableau1D est en fait un tableau2d raw major
	 *  avec db pour les colonne, et dg pour les lignes
	 *
	 * -----> db
	 * |
	 * |
	 * dg
	 *
	 */
	inline int* getTabFps() const
	    {
	    return tabFps;
	    }

	/**
	 * sans fps
	 */
	inline const GridMaillage* getGridMaillage() const
	    {
	    return &gridMaillage;
	    }

	vector<GridFps> getMax() const;

	static string toString(vector<GridFps> vectorGridFps);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/
    private:

	// Inputs
	GridMaillage gridMaillage;

	// Outputs
	int* tabFps;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
