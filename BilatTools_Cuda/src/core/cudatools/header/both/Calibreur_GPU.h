#pragma once

#include "both_define.h"
#include "Interval_GPU.h"

namespace gpu
    {
    template<typename T>
    class Calibreur
	{
	public:

	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/

	    __BOTH__
	    Calibreur(const Interval<T>& input, const Interval<T>& output)
		{
		this->pente = (output.b - output.a) / (input.b - input.a);
		this->translation = output.a - pente * input.a;
		}

	    // constructeur copie automatique car pas pointeur dans
	    //	CalibreurF
	    //	IntervalF

	    __BOTH__
	    virtual ~Calibreur()
		{
		// rien
		}

	    /*--------------------------------------*\
	|*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    __BOTH__
	    void calibrer(T& value)
		{
		value = (T) (value * pente + translation);
		}

	    __BOTH__
	    float getPente()
		{
		return this->pente;
		}

	    __BOTH__
	    float getTranslation()
		{
		return this->translation;
		}

	    /*--------------------------------------*\
	|*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    // Output
	    float pente;
	    float translation;

	};

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
