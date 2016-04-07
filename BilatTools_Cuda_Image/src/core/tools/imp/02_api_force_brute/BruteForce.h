#pragma once

#include "ForceBrutOutput.h"
#include "ProviderGridMaillage_I.h"
#include "ProviderGridMaillage1D.h"
#include "ProviderGridMaillage2D.h"
#include "Animable_I_GPU.h"
#include "Provider_I_GPU.h"
#include "Animateur_GPU.h"
#include "Progress.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {

    template<typename T>
    class BruteForce
	{
	    /*--------------------------------------*\
 |*		Constructor		*|
	     \*-------------------------------------*/

	public:

	    BruteForce(Provider_I<T>* ptrProvider, Grid* tabGrid, int n, int m, int nbIteration = 1000, bool verboseEnable = true, bool verboseAnimatorEnable =
		    true, bool isGridHeuristic = false) :
		    animateur(ptrProvider->createAnimable(), nbIteration, verboseAnimatorEnable), ptrGridMaillage(new GridMaillage(n, m, tabGrid)), verboseEnable(
			    verboseEnable)
		{
		// common
		animateur.getAnimable()->setGridHeuristic(isGridHeuristic);
		}

	    /**
	     * Create a ProviderGridMaillage1D
	     */
	    BruteForce(Provider_I<T>* ptrProvider, VariateurData variateurDg, VariateurData variateurDb, int nbIteration = 1000, bool verboseEnable = true,
		    bool verboseAnimatorEnable = true, bool isGridHeuristic = false) :
		    animateur(ptrProvider->createAnimable(), nbIteration, verboseAnimatorEnable), ptrGridMaillage(NULL), verboseEnable(verboseEnable)
		{
		ProviderGridMaillage1D provider(variateurDg, variateurDb);
		ptrGridMaillage = new GridMaillage(provider.create());

		// common
		animateur.getAnimable()->setGridHeuristic(isGridHeuristic);
		}

	    /**
	     * Create a ProviderGridMaillage2D
	     */
	    BruteForce(Provider_I<T>* ptrProvider, VariateurData variateurDgX, VariateurData variateurDgY, VariateurData variateurDbX,
		    VariateurData variateurDbY, int nbIteration = 1000, bool verboseEnable = true, bool verboseAnimatorEnable = true, bool isGridHeuristic =
			    false) :
		    animateur(ptrProvider->createAnimable(), nbIteration, verboseAnimatorEnable), ptrGridMaillage(NULL), verboseEnable(verboseEnable)
		{
		ProviderGridMaillage2D provider(variateurDgX, variateurDgY, variateurDbX, variateurDbY);
		ptrGridMaillage = new GridMaillage(provider.create());

		// common
		animateur.getAnimable()->setGridHeuristic(isGridHeuristic);
		}

	    BruteForce(Provider_I<T>* ptrProvider, ProviderGridMaillage_I* ptrProviderGridMaillage, int nbIteration = 1000, bool verboseEnable = true,
		    bool verboseAnimatorEnable = true, bool isGridHeuristic = false) :
		    animateur(ptrProvider->createAnimable(), nbIteration, verboseAnimatorEnable), ptrGridMaillage(
			    new GridMaillage(ptrProviderGridMaillage->create())), verboseEnable(verboseEnable)
		{
		// common
		animateur.getAnimable()->setGridHeuristic(isGridHeuristic);
		}

	    virtual ~BruteForce()
		{
		delete ptrGridMaillage;
		}

	    /*--------------------------------------*\
	     |*		Methodes		*|
	     \*-------------------------------------*/

	    ForceBrutOutput run()
		{
		Grid* tabGrid = ptrGridMaillage->getTabGrid();
		const int SIZE = ptrGridMaillage->size();
		Animable_I<T>* ptrAnimable = animateur.getAnimable();

		ForceBrutOutput output(*ptrGridMaillage);

		if (verboseEnable)
		    {
		    cout << endl << "[" << ptrAnimable->getTitle() << "] : BruteForce processing ..." << endl;
		    }

		Progress progress(SIZE, "Grid", verboseEnable);
		for (int s = 0; s < SIZE; s++)
		    {
		    Grid grid = tabGrid[s];
		    ptrAnimable->setGrid(grid);
		    int fps = animateur.run();
		    output.setFps(s, fps);

		    progress.incrementer();
		    }

		cout << std::endl;
		return output;
		}

	private:

	    /*--------------------------------------*\
	     |*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    // Inputs
	    GridMaillage* ptrGridMaillage;
	    Animateur<T> animateur;
	    bool verboseEnable;

	};
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
