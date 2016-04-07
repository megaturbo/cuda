#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
{
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

public:

	RipplingMath(uint w)
	{
		this->dim2 = w / 2;
	}

	// constructeur copie: pas besoin car pas attribut ptr

	virtual ~RipplingMath(void)
	{
		// rien
	}

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

public:

	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
	{
		uchar levelGris;

		f(i, j, t, &levelGris);

		ptrColorIJ->x = levelGris;
		ptrColorIJ->y = levelGris;
		ptrColorIJ->z = levelGris;

		ptrColorIJ->w = 255; //opaque
	}

private:

	void f(int i, int j, float t, uchar* ptrlevelGris)
	{
		float valDIJ;
		dij(i, j, &valDIJ);

		*ptrlevelGris = 128 + 127 * (cos((valDIJ / 10.0) - (t / 7.0)) / (valDIJ / 10.0 + 1));
	}

	void dij(int i, int j, float* ptrResult)
	{
		float fi = (float)i - dim2;
		float fj = (float)j - dim2;

		*ptrResult = sqrt(fi * fi + fj * fj);
	}

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

private:

// Tools
	double dim2;

};

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
