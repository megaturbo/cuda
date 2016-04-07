#pragma once

#include <iostream>
#include <math.h>

#include "Chrono.h"
#include "Runnable_I.h"
#include "MathTools.h"

#include "Animable_I_CPU.h"
#include "Provider_I_CPU.h"


using std::string;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    template<typename T>
    class Animateur: public Runnable_I
	{
	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/

	public:

	    /**
	     * Hyp:
	     * 	(H1) nbIteration suffisamment grand pour que timeElapse soit significatif
	     */
	    Animateur(Provider_I<T>* ptrProvider, int nbIteration = 1000, bool verboseEnable = true) :
		    ptrAnimable(ptrProvider->createAnimable()), nbIteration(nbIteration), isAnimableManaged(true), verboseEnable(verboseEnable)
		{
		// Outputs
		this->fps = -1;
		this->timeElapseS = -1;

		// tools
		this->ptrChrono = new Chrono();
		}

	    /**
	     * Hyp:
	     * 	(H1) nbIteration suffisamment grand pour que timeElapse soit significatif
	     */
	    Animateur(Animable_I<T>* ptrAnimable, int nbIteration = 1000, bool verboseEnable = true) :
		    ptrAnimable(ptrAnimable), nbIteration(nbIteration), isAnimableManaged(false), verboseEnable(verboseEnable)
		{
		// Outputs
		this->fps = -1;
		this->timeElapseS = -1;

		// tools
		this->ptrChrono = new Chrono();
		}

	    virtual ~Animateur(void)
		{
		if (isAnimableManaged)
		    {
		    delete ptrAnimable;
		    }
		delete ptrChrono;
		}

	    /*--------------------------------------*\
	 |*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    /**
	     * return fps_forauto
	     */
	    int run()
		{
		int fps_Entrelacement = run(OMP_ENTRELACEMENT); // sensiblement plus lent
		int fps_forauto = run(OMP_FORAUTO); // sensiblment plus rapide

		return fps_forauto;
		}

	    /**
	     * return fps_forauto
	     */
	    inline int getFps(void)
		{
		return fps;
		}

	private:

	    void printStat(ParallelPatern parallelPatern)
		{
		cout << endl;
		cout << "[" << ptrAnimable->getTitle() << "]" << endl;
		cout << "#(w,h)          : (" << ptrAnimable->getW() << "," << ptrAnimable->getH() << ")" << endl;
		cout << "#Iteration      : " << nbIteration << endl;
		cout << "#secondes       : " << timeElapseS << " (s)" << endl;
		cout << "#ParallelPatern : " << OmpTools::toString(parallelPatern) << endl;
		cout << "#fps            : " << fps << endl;
		}

	    int run(ParallelPatern parallelPatern)
		{
		ptrAnimable->setParallelPatern(parallelPatern);

		start(parallelPatern);
		if (verboseEnable)
		    {
		    printStat(parallelPatern);
		    }

		return fps;
		}

	    /**
	     * return fps
	     */
	    int start(ParallelPatern parallelPatern)
		{
		const int W = ptrAnimable->getW();
		const int H = ptrAnimable->getH();
		string title = ptrAnimable->getTitle();
		DomaineMath domaineMath = ptrAnimable->getDomaineMathInit();

		if (verboseEnable)
		    {
		    cout << endl << "[" << title << "] : " << OmpTools::toString(parallelPatern) << " : fps : processing ..." << endl;
		    }

		unsigned int count = W * H;
		T* ptrImage = new T[count];

		ptrChrono->start();
		for (int i = 1; i <= nbIteration; i++)
		    {
		    ptrAnimable->process(ptrImage, W, H, domaineMath);
		    ptrAnimable->animationStep();
		    }
		ptrChrono->stop();

		fpsProcess();

		delete[] ptrImage;

		return fps;
		}

	    void fpsProcess()
		{
		this->timeElapseS = ptrChrono->getDeltaTime();

		// cout<<timeElapseS<<endl;

		this->fps = ceil(nbIteration / timeElapseS);
		}

	    /*--------------------------------------*\
	 |*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    // Inputs
	    int nbIteration;
	    Animable_I<T>* ptrAnimable;
	    bool verboseEnable;

	    // Tools
	    Chrono* ptrChrono;
	    bool isAnimableManaged;

	    // Output
	    int fps;
	    float timeElapseS;

	};

    typedef Animateur<uchar4> Animateur_uchar4;
    typedef Animateur<uchar3> Animateur_uchar3;
    typedef Animateur<unsigned char> Animateur_uchar;

    typedef Animateur<float4> Animateur_float4;
    typedef Animateur<float3> Animateur_float3;
    typedef Animateur<float> Animateur_float;
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

