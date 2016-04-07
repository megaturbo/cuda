#include "VagueGrayProvider.h"
#include "VagueGray.h"

#include "MathTools.h"
#include "Grid.h"

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
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar>* VagueGrayProvider::createAnimable()
    {
    // Animation;
    float dt = 2 * PI / 1000;

    // Dimension
    int dw = 16 * 60 * 2;
    int dh = 16 * 60;

    // Grid Cuda
    dim3 dg = dim3(32, 2, 1);  		// disons a optimiser, depend du gpu
    dim3 db = dim3(16, 16, 1);   	// disons a optimiser, depend du gpu
    Grid grid(dg,db);

    return new VagueGray(grid,dw, dh, dt);
    }

/**
 * Override
 */
Image_I* VagueGrayProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_GRAY_uchar(createAnimable(), colorTexte);

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
