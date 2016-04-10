#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/* ========== DECLARATION ========== */

class JuliaMath
{
	/* ---------- PUBLIC ---------- */

public:
	/* ---------- CONSTRUCTEUR ---------- */

	__device__ JuliaMath(uint n, float c1, float c2) :
			calibreur(Interval<float>(0.f, (float)n), Interval<float>(0.f, 1.f))
	{
		this->n = n;
		this->c1 = c1;
		this->c2 = c2;
	}

	__device__
	virtual ~JuliaMath()
	{
		// rien
	}

	/* ---------- METHODES ---------- */

	__device__
	void colorXY(uchar4 *ptrColor, float x, float y, float t)
	{
		float k = getK(x, y);

		if(k > n)
		{
			ptrColor->x = 0;
			ptrColor->y = 0;
			ptrColor->z = 0;
		}else
		{
			float hue = k;
			calibreur.calibrer(hue);
			ColorTools::HSB_TO_RVB(hue, ptrColor);
		}

		ptrColor->w = 255;
	}

private:

	__device__
	bool isDivergent(float z)
	{
		return z > 2.0 ? true : false;
	}

	__device__
	int getK(float x, float y)
	{
		float zr = x;
		float zi = y;
		float old_zr;

		int k = 0;
		while(k <= this->n)
		{
			if(isDivergent(norm(zr, zi)))
				return k;

			old_zr = zr;
			zr = pow(zr, 2) - pow(zi, 2) + this->c1;
			zi = 2 * old_zr * zi + this->c2;

			k++;
		}

		return k;
	}

	__device__
	float norm(float a, float b)
	{
		return sqrt(pow(a, 2) + pow(b, 2));
	}

	/* ---------- ATTRIBUTS ---------- */

	// Input
	uint n;
	float c1;
	float c2;

	// Tools
	Calibreur<float> calibreur;
};
