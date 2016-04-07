#pragma once

#include <iostream>
#include <math.h>

#include "Progress.h"
#include "Animable_I_GPU.h"
#include "Provider_I_GPU.h"
#include "Chrono.h"
#include "Runnable_I.h"
#include "MathTools.h"
#include "Device.h"
#include "cudaTools.h"

using std::string;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
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
	     * return fps
	     */
	    int run()
		{
		start();

		if (verboseEnable)
		    {
		    printStat();
		    }

		return fps;
		}

	    /*--------------*\
	     |*	get	*|
	     \*-------------*/

	    inline int getFps(void)
		{
		return fps;
		}

	    inline Animable_I<T>* getAnimable() const
		{
		return ptrAnimable;
		}

	private:

	    void printStat()
		{
		dim3 dg = ptrAnimable->getDg();
		dim3 db = ptrAnimable->getDb();
		cout << endl;
		cout << "[" << ptrAnimable->getTitle() << "]" << endl;
		cout << "#(w,h)      : (" << ptrAnimable->getW() << "," << ptrAnimable->getH() << ")" << endl;
		cout << "#Iteration  : " << nbIteration << endl;
		cout << "#dg         : (" << dg.x << "," << dg.y << "," << dg.z << ") " << endl;
		cout << "#db         : (" << db.x << "," << db.y << "," << db.z << ") " << endl;
		cout << "#secondes   : " << timeElapseS << " (s)" << endl;
		cout << "#fps        : " << fps << endl;
		}

	    /**
	     * return fps
	     */
	    int start()
		{
		const int W = ptrAnimable->getW();
		const int H = ptrAnimable->getH();
		string title = ptrAnimable->getTitle();
		DomaineMath domaineMath = ptrAnimable->getDomaineMathInit();

		if (verboseEnable)
		    {
		    cout << endl << "[Animateur] : " << title << " : fps : processing ..." << endl;
		    }

		Progress progress(nbIteration,"Iteration", verboseEnable);

		unsigned int count = W * H;
		T* ptrImage = NULL;
		size_t size = count * sizeof(T);
		HANDLE_ERROR(cudaMalloc(&ptrImage, size));
		HANDLE_ERROR(cudaMemset(ptrImage, 0, size));

		const char* messageError = title.c_str();

		ptrChrono->start();
		for (int i = 1; i <= nbIteration; i++)
		    {
		    ptrAnimable->process(ptrImage, W, H, domaineMath);

		    Device::lastCudaError(messageError);
		    Device::synchronize(); // Important!

		    ptrAnimable->animationStep();

		    progress.incrementer();
		    }
		ptrChrono->stop();

		fpsProcess();

		HANDLE_ERROR(cudaFree(ptrImage));

		return fps;
		}

	    void fpsProcess()
		{
		this->timeElapseS = ptrChrono->getDeltaTime();

		// cout<<timeElapseS<<endl;

		this->fps = ceil(nbIteration / timeElapseS);
		}

	private:

//	    void avancementIntro(int nbStarMax) // todo ameliorer
//		{
//		    cout << "#Iteration=" << nbIteration << endl;
//		    cout << "Advancement (to reach): ";
//		    for (int s = 0; s < nbIteration; s++)
//			{
//			if (nbIteration > nbStarMax && s % 300 == 0)
//			    {
//			    cout << "*";
//			    }
//			else if (nbIteration <= nbStarMax)
//			    {
//			    cout << "*";
//			    }
//			}
//		    cout << endl;
//		    cout << "Advancement (current) : ";
//		}
//
//	    void avancementCurrent(int nbStarMax, int s)
//		{
//		if (verboseEnable)
//		    {
//		    if (nbIteration > nbStarMax && s % 300 == 0)
//			{
//			std::cout << "*" << std::flush;
//			}
//		    else if (nbIteration <= nbStarMax)
//			{
//			std::cout << "*" << std::flush;
//			}
//		    }
//		}

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

