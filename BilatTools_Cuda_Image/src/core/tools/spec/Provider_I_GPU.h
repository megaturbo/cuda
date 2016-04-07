#pragma once

#include "Image_I.h"

#include "Animable_I_GPU.h"
#include "ImageAnimable_GPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    template<typename T>
    class Provider_I
	{
	public:

	    virtual ~Provider_I()
		{
		//Rien
		}


	    /*--------------------------------------*\
	     |*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    virtual Animable_I<T>* createAnimable(void)=0;

	    virtual Image_I* createImageGL(void)=0;
	};
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
