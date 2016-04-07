#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <string>

#include "StringTools.h"

#include "Chrono.h"

using std::cout;
using std::cerr;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

Chrono::Chrono(string title):title(title)
    {
    start();
    }

Chrono::Chrono():title("")
    {
    start();
    }

Chrono::~Chrono()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methodes		*|
 \*-------------------------------------*/

void Chrono::start()
    {
    etatChrono = RUNNING;

    sumTimeElapsePause = 0;
    deltaTime = -1;
    timePause = -1;

    timeStart = time();
    }

double Chrono::stop()
    {
    if (etatChrono == RUNNING || etatChrono == PAUSE)
	{
	etatChrono = STOPPED;

	timeStop = time();
	deltaTime = timeStop - timeStart - sumTimeElapsePause;

	return deltaTime;
	}
    else
	{
	cerr << "[Chrono] : stop : Previous state should be RUNNING or PAUSE" << endl;
	return -1;
	}
    }

double Chrono::pause()
    {
    if (etatChrono == RUNNING)
	{
	etatChrono = PAUSE;

	timePause = time();
	deltaTime = timePause - timeStart - sumTimeElapsePause;

	return deltaTime;
	}
    else
	{
	cerr << "[Chrono] : pause : Previous state should be RUNNING" << endl;
	return -1;
	}
    }

void Chrono::play()
    {
    if (etatChrono == PAUSE)
	{
	double timeElapsePause = time() - timePause;
	sumTimeElapsePause += timeElapsePause;

	etatChrono = RUNNING;
	}
    else
	{
	cerr << "[Chrono] : play : Previous state should be PAUSE" << endl;
	}
    }

double Chrono::getDeltaTime() const
    {
    switch (etatChrono)
	{

	case STOPPED:
	    {
	    return deltaTime;
	    }

	case RUNNING:
	    {
	    return time() - timeStart - sumTimeElapsePause;
	    }

	case PAUSE:
	    {
	    return timePause - timeStart - sumTimeElapsePause;
	    }

	default:
	    {
	    cerr << "Chrono : getDeltaTime : state unknow!" <<endl;
	    return -1;
	    }
	}
    }

void Chrono::print() const
    {
    print(cout, title);
    }

void Chrono::print(const string& titre) const
    {
    print(cout, title+" "+titre);
    }


void Chrono::print(ostream& stream, const string& titre) const
    {
    stream << titre << " " << getDeltaTime() << " (s)" << endl;
    }

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

double Chrono::time()
    {
    // return time(NULL); //  #include <time.h> time(NULL) est time_t
    // Problem : Sous linux : compte en seconde!

    // STL version
       //time_point<high_resolution_clock,milliseconds> now=time_point_cast<milliseconds>(high_resolution_clock::now());
       //return now.time_since_epoch().count() / 1000.0;

    return omp_get_wtime(); //#include <omp.h>
    }

/*--------------------------------------*\
 |*		Friend			*|
 \*-------------------------------------*/

/**
 * friend
 */
ostream& operator <<(ostream& stream, const Chrono& chrono) // friend
    {
    chrono.print(stream);
    return stream;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

