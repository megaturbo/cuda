#pragma once

#include <iostream>

#include "ImageOption.h"
#include "GLUTImageViewers_CPU.h"
#include "Provider_I_CPU.h"

using std::cout;
using std::endl;
using std::string;

// astuce: permet de travailler avec une méthode static sans classe derivant interface
// meme code pour cpu gpu :

// TProvider doit fournir
//    Image_I*
// see Image_CPU or Image_GPU
namespace cpu
    {
    template<class TProvider>
    class Viewer
	{

	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/

	public:

	    Viewer(ImageOption imageOption, int pxFrame = 0, int pyFrame = 0) :
		    ptrImage(TProvider().createImageGL()), glutViewer(ptrImage, imageOption, pxFrame, pyFrame)
		{
		// Rien
		}

	    ~Viewer()
		{
		delete ptrImage; // car TProvider::createImageGL() fournit un pointeur d'un objet dynamique
		}
	    
	    /*--------------------------------------*\
	|*		Methodes		*|
	     \*-------------------------------------*/

	    /*--------------------------------------*\
	|*		Attributs		*|
	     \*-------------------------------------*/

	private:
	    
	    // Input
	    Image_I* ptrImage;

	    // Tools
	    cpu::GLUTImageViewers glutViewer;
	    
	};
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
