#include "SingletonBoost.h"
#include <iostream>

using std::cout;
using std::endl;

#include <boost/thread.hpp>
#include <boost/date_time.hpp>

using boost::thread;
using boost::posix_time::seconds;
using boost::this_thread::sleep;
using boost::this_thread::get_id;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSynchronization(void);

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

bool useSynchronization(void)
    {
    cout << endl << "[Use Boost Synchronization] : " << endl << endl;

    bool isOk = true;

    isOk &= useSimple();
    isOk &= useStress1();
    isOk &= useStress2();

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

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
    cout << endl << "[Use Boost Synchronization stress1] : " << endl << endl;

    const int n = 100;
    // thread tabThread[n];

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
    // seconds workTime(1);
    // sleep(workTime);

    cout << "[SingletonBoost] ::getInstance from thread : id  : ";

    SingletonBoost::getInstance()->print_tid();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

