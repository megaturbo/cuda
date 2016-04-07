#pragma once

#include <iostream>

#include "OmpTools.h"

#include "cudaType_CPU.h"
#include "DomaineMath_CPU.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    template<typename T>
    class Animable_I
	{

	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/
	public:

	    Animable_I(unsigned int w, unsigned int h, string title, const DomaineMath& domaineInit) :
		    w(w), h(h), title(title), domaineInit(domaineInit), t(0.0f)
		{
		this->nbThread = OmpTools::setAndGetNaturalGranularity();
		}

	    Animable_I(unsigned int w, unsigned int h, string title) :
		    w(w), h(h), title(title), domaineInit(0, w, 0, h), t(0.0f)
		{
		this->nbThread = OmpTools::setAndGetNaturalGranularity();
		}

	    virtual ~Animable_I()
		{
		// Nothing here
		}

	    /*--------------------------------------*\
	     |*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    virtual void animationStep(void)=0;

	protected:

	    // Balayage image
	    virtual void processEntrelacementOMP(T* ptrTabPixels, unsigned int w, unsigned int h, const DomaineMath& domaineMath)=0;

	    virtual void processForAutoOMP(T* ptrTabPixels, unsigned int w, unsigned int h, const DomaineMath& domaineMath)=0;

	public:

	    void process(T* ptrTabPixels, unsigned int w, unsigned int h, const DomaineMath& domaineMath)
		{
		switch (parallelPatern)
		    {

		    case OMP_ENTRELACEMENT: // Plus lent sur CPU
			{
			processEntrelacementOMP(ptrTabPixels, w, h, domaineMath);
			break;
			}

		    case OMP_FORAUTO: // Plus rapide sur CPU
			{
			processForAutoOMP(ptrTabPixels, w, h, domaineMath);
			break;
			}

		    case OMP_MIXTE: // Pour tester que les deux implementations fonctionnent
			{
			// Note : Des saccades peuvent apparaitre à cause de la grande difference de fps entre la version entrelacer et auto
			static bool isEntrelacement = true;
			if (isEntrelacement)
			    {
			    processEntrelacementOMP(ptrTabPixels, w, h, domaineMath);
			    }
			else
			    {
			    processForAutoOMP(ptrTabPixels, w, h, domaineMath);
			    }
			isEntrelacement = !isEntrelacement; // Pour swithcer a chaque iteration
			break;
			}
		    }
		}

	    /*--------------------------------------*\
	 |*		Get			*|
	     \*-------------------------------------*/

	public:

	    inline float getAnimationPara() const
		{
		return t;
		}

	    inline string getTitle() const
		{
		return title;
		}

	    inline int getW() const
		{
		return w;
		}

	    inline int getH() const
		{
		return h;
		}

	    inline ParallelPatern getParallelPatern() const
		{
		return parallelPatern;
		}

	    inline DomaineMath getDomaineMathInit() const
		{
		return domaineInit;
		}

	    /*--------------------------------------*\
	 |*		Set			*|
	     \*-------------------------------------*/

	    void setParallelPatern(ParallelPatern parallelPatern)
		{
		this->parallelPatern = parallelPatern;
		}

	    void setTitle(string title)
		{
		this->title = title;
		}

	    /*--------------------------------------*\
	 |*		Attributs		*|
	     \*-------------------------------------*/

	public:

	    // Inputs
	    const unsigned int w;
	    const unsigned int h;

	protected:

	    // Inputs
	    int nbThread;
	    ParallelPatern parallelPatern;
	    DomaineMath domaineInit;
	     string title;

	    //Tools
	    double t;

	};

    typedef Animable_I<cpu::uchar4> Animable_I_uchar4;
    typedef Animable_I<cpu::uchar3> Animable_I_uchar3;
    typedef Animable_I<unsigned char> Animable_I_uchar;

    typedef Animable_I<cpu::float4> Animable_I_float4;
    typedef Animable_I<cpu::float3> Animable_I_float3;
    typedef Animable_I<float> Animable_I_float;

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

