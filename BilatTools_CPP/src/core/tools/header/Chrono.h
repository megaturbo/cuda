#pragma once

#include <string>

using std::string;
using std::ostream;

typedef  enum {RUNNING, PAUSE, STOPPED} EtatChrono;

class Chrono
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	Chrono(string title);

	Chrono();

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~Chrono();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	void start();
	double stop();

	double pause();
	void play();

	double getDeltaTime() const;

	void print(const string& titre) const;
	void print() const;
	void print(ostream& stream, const string& titre = "") const;

	/*--------------------------------------*\
	 |*		Friend			*|
	 \*-------------------------------------*/

	friend ostream& operator <<(ostream& stream, const Chrono& chrono);

    private:

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

	static double time();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

	// Inputs
	string title;

	// Tools
	double timeStart;
	double timeStop;
	double timePause;
	double deltaTime;
	double sumTimeElapsePause;

	EtatChrono etatChrono;
    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

