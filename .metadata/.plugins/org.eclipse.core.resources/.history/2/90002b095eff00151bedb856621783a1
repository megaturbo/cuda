#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/* ========== DECLARATION ========== */

class RayTracingMath
{
	/* ---------- PUBLIC ---------- */

public:
	/* ---------- CONSTRUCTEUR ---------- */

	__device__ RayTracingMath()
	{
		// Nope
	}

	__device__
	 virtual ~RayTracingMath()
	{
		// Nope
	}

	/* ---------- METHODES ---------- */

	__device__
	void colorXY(uchar4 *ptrColor, float x, float y, float t)
	{
		ptrColor->w = 255;

		float min = FLT_MAX;
		float hueMin = -FLT_MAX;
		float brightnessMin = -FLT_MAX;

		float2 xySol;
		xySol.x = x;
		xySol.y = y;

		for (int i = 0; i < n; ++i)
		{
			Sphere sphere = spheres[i];
			float h2 = sphere.hSquare(xySol);

			if (sphere.isBelow(h2))
			{

				float dz = sphere.dz(h2);
				float dist = sphere.distance(dz);

				if (dist < min)
				{
					min = dist;
					hueMin = sphere.hueT(t);
					brightnessMin = sphere.brightness(dz);
				}
			}
		}

		if (hueMin >= 0 && brightnessMin >= 0)
			ColorTools::HSB_TO_RVB(hueMin, 1.0, brightnessMin, ptrColor);
		else
			ptrColor->x = ptrColor->y = ptrColor->z = 0;
	}

private:

	__device__
	void f(float x, float y, float t, uchar4* ptrColor)
	{
	}

	/* ---------- ATTRIBUTS ---------- */
};
