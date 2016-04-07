#include <iostream>
#include "SingletonStd.h"

using std::cout;
using std::endl;

#include <thread>
#include <chrono>

using std::thread;
using std::chrono::seconds;
using std::this_thread::sleep_for;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useStdSynchronization(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void runnable(void);
static bool useSimple(void);
static bool useStress1(void);
static bool useStress2(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useStdSynchronization(void)
    {
    cout << endl << "[Use Std Synchronization] : " << endl << endl;

    bool isOk = true;

    isOk &= useSimple();
    isOk &= useStress1();
    isOk &= useStress2();

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * http://www.cplusplus.com/reference/mutex/mutex/
 */
bool useSimple(void)
    {
    thread threadRunnable1(runnable);
    thread threadRunnable2(runnable);

    threadRunnable1.join();
    threadRunnable2.join();

    return true;
    }

bool useStress1(void)
    {
    cout << endl << "[Use Std Synchronization stress1] : " << endl << endl;

    const int n = 100;

#pragma omp parallel for
    for (int i = 0; i <= n; i++)
	{
	thread threadi = thread(runnable);
	threadi.join(); // pas necessaire
	} // barriere de synchronisation explicite

    return true;
    }

bool useStress2(void)
    {
    cout << endl << "[Use Boost Synchronization stress2] : " << endl << endl;

    const int n = 100;
    thread tabThread[n];

    // launch
	{
	for (int i = 0; i <= n; i++)
	    {
	    tabThread[i] = thread(runnable);
	    }
	}

    // join
	{
	for (int i = 0; i <= n; i++)
	    {
	    tabThread[i].join();
	    }
	}

    return true;
    }

/*----------------*\
 |*	common   *|
 \*---------------*/

void runnable(void)
    {
    //seconds workTime(1);
    //sleep_for(workTime);

    cout << "[SingletonStd] : getInstance : from thread : id  : ";

    SingletonStd::getInstance()->print_tid();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

