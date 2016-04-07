#pragma once

#include <algorithm>

#include "BarivoxOutput.h"
#include "VariateurData.h"
#include "Grid.h"
#include "Progress.h"
#include "Device.h"

#include "Animable_I_GPU.h"
#include "Provider_I_GPU.h"
#include "Animateur_GPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    /**
     * Fixe dg a dg init
     * On bruteforce sur DB, on chercher le fps max
     * On bruteforce DG ave le DB fps max trouvé
     *
     * Grid 1d Only
     */
    template<typename T>
    class Barivox
	{
	    /*--------------------------------------*\
	     |*		Constructor		*|
	     \*-------------------------------------*/

	public:

	    Barivox(Provider_I<T>* ptrProvider, dim3 dgInit, VariateurData variateurDg, VariateurData variateurDb, int nbIteration = 1000, bool verboseEnable =
		    true, bool verboseAnimatorEnable = true, bool isGridHeuristic = false) :
		    animateur(ptrProvider->createAnimable(), nbIteration, verboseAnimatorEnable), verboseEnable(verboseEnable), dgInit(dgInit), variateurDg(
			    variateurDg), variateurDb(variateurDb)
		{
		// Tools
		this->nDb = variateurDb.getN();
		this->nDg = variateurDg.getN();
		this->ptrAnimable = animateur.getAnimable();

		// Config
		this->ptrAnimable->setGridHeuristic(isGridHeuristic);
		}

	    virtual ~Barivox()
		{
		delete[] tabDb;
		delete[] tabDg;
		}

	    /*--------------------------------------*\
	     |*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    const BarivoxOutput run();

	private:

	    const dim3 parcoursDB(BarivoxOutput* ptrOutput);

	    const void parcoursDG(BarivoxOutput* ptrOutput, dim3 dbMax);

	    /*--------------------------------------*\
	     |*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    // Inputs
	    dim3 dgInit;
	    VariateurData variateurDg;
	    VariateurData variateurDb;
	    Animateur<T> animateur;
	    bool verboseEnable;

	    // Tools
	    dim3* tabDb;
	    dim3* tabDg;

	    int nDb;
	    int nDg;

	    Animable_I<T>* ptrAnimable;
	};

    /*----------------------------------------------------------------------*\
 |*			Implementation 					*|
     \*---------------------------------------------------------------------*/

    template<typename T>
    const BarivoxOutput Barivox<T>::run()
	{
	if (verboseEnable)
	    {
	    cout << endl << "[" << ptrAnimable->getTitle() << "] : Barivox processing ..." << endl;
	    }

	// Preparin grid
	    {
	    // tabDg create
		{
		tabDg = new dim3[variateurDg.getN()];

		dim3 dg(variateurDg.min, 1, 1);
		for (int i = 0; i < variateurDg.getN(); i++)
		    {
		    tabDg[i] = dg;
		    dg.x += variateurDg.step;
		    }
		}

	    // tabDb create
		{
		tabDb = new dim3[variateurDb.getN()];

		dim3 db(variateurDb.min, 1, 1);
		for (int i = 0; i < variateurDb.getN(); i++)
		    {
		    tabDb[i] = db;
		    db.x += variateurDb.step;
		    }
		}
	    }

	BarivoxOutput output(nDg, nDb);
	output.setGrid(tabDg, tabDb);

	dim3 dbMax = parcoursDB(&output);
	parcoursDG(&output, dbMax);

	return output;
	}

    template<typename T>
    const dim3 Barivox<T>::parcoursDB(BarivoxOutput* ptrOutput)
	{
	if (verboseEnable)
	    {
	    cout << "Step1 :" << endl;
	    cout << "Fixe  : dg = " << dgInit.x << endl;
	    cout << "Processing along db ..." << endl;
	    }

	Progress progressDB(nDb, "Grid", verboseEnable);

	dim3 dbMax(Device::getMaxThreadPerBlock(), 1, 1); // quelque chose
	// BruteForce DB
	    {
	    Grid grid(dgInit, tabDb[0]);
	    int fpsMax = 0;
	    for (int i = 0; i < nDb; i++)
		{
		grid.db = tabDb[i];
		ptrAnimable->setGrid(grid);

		int fps = animateur.run();
		ptrOutput->setFpsDb(i, fps);

		// max
		    {
		    if (fps > fpsMax)
			{
			fpsMax = fps;
			dbMax = tabDb[i];
			}
		    else if (fps == fpsMax)	// TODO JST c'est quoi
			{
			dbMax.x = std::min(dbMax.x, tabDb[i].x);
			}
		    else
			{
			//Plus petit rien!
			}
		    }

		progressDB.incrementer();
		}
	    }

	return dbMax;
	}

    template<typename T>
    const void Barivox<T>::parcoursDG(BarivoxOutput* ptrOutput, dim3 dbMax)
	{
	if (verboseEnable)
	    {
	    cout << endl;
	    cout << "Step 2 :" << endl;
	    cout << "Fixe   : db = " << dbMax.x << endl;
	    cout << "Processing along dg ..." << endl;
	    }

	Progress progressDG(nDg, "Grid", verboseEnable);

	dim3 dgTemp;
	Grid grid(dgTemp, dbMax);

	// BruteForce DG
	    {
	    for (int i = 0; i < nDg; i++)
		{
		grid.dg = tabDg[i];
		ptrAnimable->setGrid(grid);

		int fps = animateur.run();
		ptrOutput->setFpsDg(i, fps);

		progressDG.incrementer();
		}
	    }

	ptrOutput->setCroix(dgInit.x, dbMax.x);
	}

    } // end namespace

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
