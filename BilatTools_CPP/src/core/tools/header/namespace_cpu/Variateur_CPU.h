#pragma once

#include <assert.h>

#include "Interval_CPU.h"

//using namespace cpu; //surtout pas de using namespace!! Si use dans partie gpu, il va y avoir conflit!
namespace cpu
    {
    template<typename T>
    class Variateur
	{
	public:

	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/

	    Variateur(const Interval<T>& range, T dt)
		{
		// Input
		this->dt = dt;
		this->tMin = range.a;
		this->tMax = range.b;

		// Tools
		this->isCroisssantPhase = true;
		this->t = range.a;

		assert(tMin < tMax);
		}


	    virtual ~Variateur()
		{
		// rien
		}

	    /*--------------------------------------*\
	|*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    T varierAndGet()
		{
		if (isCroisssantPhase)
		    {
		    if (t >= tMax)
			{
			isCroisssantPhase = false;
			t -= dt;
			}
		    else
			{
			t += dt;
			}
		    }
		else
		    {
		    if (t <= tMin)
			{
			isCroisssantPhase = true;
			t += dt;
			}
		    else
			{
			t -= dt;
			}
		    }

		return t;
		}

	    T get()
		{
		return t;
		}

	    /*--------------------------------------*\
	    |*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    // Input
	    T tMin;
	    T tMax;
	    T dt;

	    // tools
	    T t;
	    bool isCroisssantPhase;

	};
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
