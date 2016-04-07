#include "Progress.h"

#include <iostream>
#include <assert.h>

#define NB_STAR_MAX 50

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

Progress::Progress(int n, string title,bool isVerbosityEnable):title(title)
    {
    assert(n >= 1);

    // Inputs
    this->n = n;
    this->isVerbosityEnable = isVerbosityEnable;

    // Tools
    this->nbStar = 0;
    this->i=0;

    printIntro();

    ptrChrono=new Chrono();
   // ptrChrono->start();
    }

Progress::~Progress()
    {
    delete ptrChrono;
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Progress::incrementer()
    {
    i++;
    avancement100 = (int) (i / (double) n * 100); // in [0,100]

    printProgress();

    if (i == n)
	{
	ptrChrono->stop();
	if (isVerbosityEnable)
	    {
	    cout<<endl;
	    cout <<"#"<<title<<"\t= " << n << endl;
	    cout <<"time      (total) = "<< *ptrChrono;
	    cout <<"time mean (1-"<<title<<") = "<< ptrChrono->getDeltaTime()/n*1000<<" (ms)"<<endl;
	    }
	};
    }

/*------------------*\
 |*	get	    *|
 \*-----------------*/

int Progress::get()
    {
    return avancement100;
    }

int Progress::getIteration()
    {
    return i;
    }

Chrono Progress::getChrono()
    {
    return *ptrChrono;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Progress::printIntro()
    {
    if (isVerbosityEnable)
	{
	cout << "Progress [";
	for (int i = 1; i <= NB_STAR_MAX; i++)
	    {
	    cout << " ";
	    }
	cout << "]100%\n";
	cout << "Progress  ";
	}
    }

void Progress::printProgress()
    {
    if (isVerbosityEnable)
	{
	int m = nbStarToAdd();

	for (int i = 1; i <= m; i++)
	    {
	    cout << "*"<<std::flush;
	    nbStar++;
	    }
	}
    }

int Progress::nbStarToAdd()
    {
    int dizaine = avancement100 / 10; // in [0,9]
    int unit = avancement100 % 10; // in [0,9]

    int nDizaine = dizaine * 10 / 2;
    int nUnit = 0;

    if (unit == 0)
	{
	nUnit = 0;
	}
    else
	{
	if (unit % 2 != 0)
	    {
	    unit--;
	    }
	// unit in [2 4 6 8  ]
	nUnit = unit / 2;
	}

    int nTotal = nDizaine + nUnit;
    int delta = nTotal - nbStar;

    // check
//	{
//	assert(i >= 1 && i <= n);
//	assert(avancement100 >= 0 && avancement100 <= 100);
//	assert(dizaine >= 0 && dizaine <= 10);// 10 pour cent
//	assert(unit >= 0 && unit <= 9);
//	assert(nTotal >= 0 && nTotal <= NB_STAR_MAX);
//	assert(delta >= 0 && delta <= NB_STAR_MAX);
//	}

    return delta;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

