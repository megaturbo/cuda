//#include <iostream>
//#include <assert.h>
//
//#include "Device.h"
//#include "RayTracing.h"
//#include "Sphere.h"
//#include "cudaTools.h"
//
//#include <limits>
//
//using std::cout;
//using std::endl;
//
///* ========== DECLARATION ========== */
//
//extern __global__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t, uint nbSphere);
//
///* ---------- PUBLIC ---------- */
//
//RayTracing::RayTracing(const Grid &grid, uint width, uint height, float dt, uint nbSphere) :
//		Animable_I<uchar4>(grid, width, height, "RayTracing Roulin")
//{
//	// time
//	this->t = 0;
//	this->dt = dt;
//
//	// Inputs
//	this->nbSphere = nbSphere;
//	this->spheres = new Sphere[nbSphere];
//
//	// Init spheres
//	float margin = 200.f;
//	for(int i = 0; i < this->nbSphere; i++)
//	{
//		float3 center;
//		center.x = randomFloat(margin, width - margin);
//		center.y = randomFloat(margin, height - margin);
//		center.z  = randomFloat(10.f, 2.f * width);
//
//		float radius = randomFloat(20.f, w / 10.f);
//		float hue = randomFloat(0.f, 1.f);
//
//		this->spheres[i] = Sphere(center, radius, hue);
//	}
//}
//
//RayTracing::~RayTracing(void)
//{
//	delete[] spheres;
//}
//
///* ~~~~~~~~~~  METHODS  ~~~~~~~~~~ */
///**
// * Override
// * Call periodicly by the API
// *
// * Note : domaineMath pas use car pas zoomable
// */
//void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
//{
//	Device::lastCudaError("raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release
//
//	// start kernel
//	rayTracing<<<dg, db>>>(ptrDevPixels, w, h, t, nbSphere);
//
//	Device::lastCudaError("raytracing rgba uchar4 (after)"); // facultatif, for debug only, remove for release
//}
//
///* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */
//
//void RayTracing::animationStep()
//{
//	this->t += dt;
//}
//
//
//float RayTracing::randomFloat(float min, float max)
//{
//    float random = ((float) rand()) / (float) RAND_MAX;
//    float diff = max - min;
//    float r = random * diff;
//    return min + r;
//}
///**
// * Override (code naturel omp)
// */
