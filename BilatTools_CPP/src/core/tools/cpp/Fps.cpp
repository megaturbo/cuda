#include "Fps.h"
#include <iostream>
#include <math.h>



using std::cerr;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

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

Fps::Fps(string title, int delta_nb_frame) :
	title(title),chrono(title)
    {
    this->delta_nb_frame = delta_nb_frame;
    chrono.pause();
    etatFps = SUSPEND;
    nbFrame = 0;
    nbFramePrevious = 0;
    lastFps = -1;
    }

Fps::~Fps(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

void Fps::suspend()
    {
    if (etatFps == ACTIVATED)
	{
	etatFps = SUSPEND;
	acquire();
	chrono.pause();
	}
    else
	{
	cerr << "Fps-" << title << " : suspend : previous state should be : ACTIVATED" << endl;
	}
    }

void Fps::activate()
    {
    if (etatFps == SUSPEND)
	{
	etatFps = ACTIVATED;
	chrono.play();
	}
    else
	{
	cerr << "Fps-" << title << " : activate : previous state should be : SUSPEND" << endl;
	}
    }

void Fps::acquire()
    {
    nbFrame++;
    print(delta_nb_frame);
    }

void Fps::printNow()
    {
    print(0);
    }

/**
 * in seconds
 */
float Fps::fpsFloat()
    {
    int nbFrameNew = nbFrame - nbFramePrevious;
    double deltaTime = chrono.getDeltaTime();

    if (deltaTime > 0)
	{
	lastFps = ceil(10*nbFrame / deltaTime);
	lastFps=lastFps/10;
	nbFramePrevious = nbFrame;
	}

    return lastFps;
    }

/**
 * in seconds
 */
int Fps::fps()
    {
    return ceil(fpsFloat());
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Fps::print(int delta_nb_frame)
    {
    int nbFrameNew = nbFrame - nbFramePrevious;

    if (nbFrameNew >= delta_nb_frame)
	{
	cout << "[FPS-" << title << "] = " << fpsFloat() << " (s)" << endl;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
