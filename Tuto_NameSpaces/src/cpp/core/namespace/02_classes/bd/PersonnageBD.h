#pragma once

#include "Invention.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace bd
    {
    /**
     * Note : bd::Personnage peut deriver de Cartoon qui lui n'est pas dans un namespace
     */
    class Personnage: public Invention
	{

	    /*-------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    Personnage(string name,string inventeur);

	    virtual ~Personnage();

	    /*-------------------------------------*\
	     |*		Methode			    *|
	     \*-------------------------------------*/

	public:

	    string getName() const;

	    /*-------------------------------------*\
	     |*		Attributs		    *|
	     \*-------------------------------------*/

	private:

	    //Input
	    string name;
	};
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
