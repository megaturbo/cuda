#include "DamierHueFloatProvider.h"
#include "DamierHueFloat.h"

#include "MathTools.h"
#include "Grid.h"

#include "DomaineMath_GPU.h"
using namespace gpu;

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
Animable_I<float>* DamierHueFloatProvider::createAnimable()
    {
    DomaineMath domaineMath=DomaineMath(0,0,2*PI,2*PI);

    // Animation;
    float dt =  2 * PI / 8000;
    int n=2;

    // Dimension
    int dw = 16 * 60 * 2;
    int dh = 16 * 60;

    // Grid Cuda
    dim3 dg = dim3(8, 8, 1);  		// disons a optimiser, depend du gpu
    dim3 db = dim3(16, 16, 1);   	// disons a optimiser, depend du gpu
    Grid grid(dg,db);

    return new DamierHueFloat(grid,dw, dh, dt,n,domaineMath);
    }

/**
 * Override
 */
Image_I* DamierHueFloatProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_HUE_float(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
