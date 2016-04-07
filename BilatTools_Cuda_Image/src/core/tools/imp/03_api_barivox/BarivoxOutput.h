#pragma once

#include <iostream>
#include <ostream>
#include <string>

#include "cuda_runtime.h"

using std::ostream;
using std::string;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class BarivoxOutput
    {

	/*--------------------------------------*\
 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	BarivoxOutput(int nDg, int nDb);

	BarivoxOutput(const BarivoxOutput& source);

	virtual ~BarivoxOutput();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	BarivoxOutput& operator=(const BarivoxOutput& source);

	string toStringFpsDb() const;

	string toStringFpsDg() const;

	string toStringDb() const;

	string toStringDg() const;

	void save(string prefix) const;

	void print(ostream& stream, const string& titre = "") const;

	friend ostream& operator <<(ostream& stream, const BarivoxOutput& barivoxOutput);

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

    public:

	void setFpsDb(int s, int fps);

	void setFpsDg(int s, int fps);

	/**
	 * (dgInit,dbMaxForDgInit)
	 */
	void setCroix(int2 croix);

	void setCroix(int dgInit, int dbMaxForDgInit);

	void setGrid(dim3* tabDg, dim3* tabDb);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	/**
	 * Fps when dg is fixed and db was varying
	 */
	inline int* getTabFpsDb() const
	    {
	    return tabFpsDb;
	    }

	/**
	 * Fps when db is fixed and dg was varying
	 */
	inline int* getTabFpsDg() const
	    {
	    return tabFpsDg;
	    }

	/**
	 * dgFixe: db variable
	 */
	inline dim3* getTabDb() const
	    {
	    return tabDb;
	    }

	/**
	 * dbFixe: dg variable
	 */
	inline dim3* getTabDg() const
	    {
	    return tabDg;
	    }

	inline int getNbDg() const
	    {
	    return nDb;
	    }

	inline int getNbDb() const
	    {
	    return nDb;
	    }

	/**
	 * (dgInit,dbMaxForDgInit)
	 */
	inline int2 getCroix() const
	    {
	    return croix;
	    }

    private:

	void max(ostream& stream) const;

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int nDb; 	// nbDg
	int nDg; 	// nbDb
	int2 croix; 	// (dgInit,dbMaxForDgInit)

	//Outputs
	int* tabFpsDb;
	int* tabFpsDg;

	dim3* tabDg;
	dim3* tabDb;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
