//#pragma once
//
//#include <math.h>
//#include "MathTools.h"
//
//#include "Calibreur_GPU.h"
//#include "ColorTools_GPU.h"
//using namespace gpu;
//
///* ========== DECLARATION ========== */
//
//class RayTracingMath
//{
//	/* ---------- PUBLIC ---------- */
//
//public:
//	/* ---------- CONSTRUCTEUR ---------- */
//
//	__device__ RayTracingMath(Sphere* spheres, int nbSphere)
//	{
//		 this->nbSphere = nbSphere;
//		 this->spheres = spheres;
//	}
//
//	__device__
//	 virtual ~RayTracingMath()
//	{
//		 Nope
//	}
//
//	/* ---------- METHODES ---------- */
//
//	__device__
//	void colorXY(uchar4* ptrColor, float x, float y, float t)
//	{
//		float min = 100000.f;
//		float hueMin = -10000.f;
//		float brightnessMin = -100000.f;
//
//		float2 sol;
//		sol.x = x;
//		sol.y = y;
//
//		for(int i = 0; i < n; i++)
//		{
//			Sphere sphere = spheres[i];
//			float h2 = sphere.hCarre(sol);
//
//			if(sphere.isEnDessous(h2))
//			{
//				float dz = sphere.dz(h2);
//				float dist = sphere.distance(dz);
//
//				if(dist < min)
//				{
//					min = dist;
//					hueMin = sphere.hue(t);
//					brightnessMin = sphere.brightness(dz);
//				}
//			}
//		}
//		if(hueMin >= 0 && brightnessMin >= 0)
//			ColorTools::HSB_TO_RVB(hueMin, 1.f, brightnessMin, ptrColor);
//		else
//		{
//			ptrColor->x = 0;
//			ptrColor->y = 0;
//			ptrColor->z = 0;
//		}
//
//		ptrColor->w = 255;  opaque
//	}
//
//	/* ---------- ATTRIBUTS ---------- */
//
//private:
//	int nbSphere;
//	Sphere* spheres;
//};
