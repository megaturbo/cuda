#pragma once

#include "Interval_CPU.h"

namespace cpu
    {
    template<typename T>
    class Calibreur
	{
	public:

	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/

	    Calibreur(const Interval<T>& input, const Interval<T>& output)
		{
		this->pente = (output.b - output.a) / (input.b - input.a);
		this->translation = output.a - pente * input.a;
		}

	    // constructeur copie automatique car pas pointeur dans
	    //	CalibreurF
	    //	IntervalF

	    virtual ~Calibreur()
		{
		// rien
		}

	    /*--------------------------------------*\
	|*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    void calibrer(T& value)
		{
		value = (T) (value * pente + translation);
		}

	    float getPente()
		{
		return this->pente;
		}

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
