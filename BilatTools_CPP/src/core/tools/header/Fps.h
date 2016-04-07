#pragma once

#include "Chrono.h"

#include <string>

using std::string;

typedef enum
    {
    ACTIVATED,
    SUSPEND
    } EtatFps;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fps
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Fps(string title, int delta_nb_frame = 60 * 5);
	virtual ~Fps(void);

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * call acquire
	 */
	void activate();
	void suspend();

	/**
	 * call print
	 */
	void acquire();

	void printNow();

	/**
	 * in seconds
	 */
	float fpsFloat();

	/**
	 * in seconds
	 */
	int fps();

    private:

	void print(int delta_nb_frame);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	string title;
	int delta_nb_frame;

	// Tools
	Chrono chrono;
	int nbFrame;
	EtatFps etatFps;
	int nbFramePrevious;

	float lastFps;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
