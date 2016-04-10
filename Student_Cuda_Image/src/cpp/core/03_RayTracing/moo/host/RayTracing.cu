#include <iostream>
#include <assert.h>

#include "Device.h"
#include "RayTracing.h"
#include "Sphere"

using std::cout;
using std::endl;

/* ========== DECLARATION ========== */

extern __global__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t);

/* ---------- PUBLIC ---------- */

RayTracing::RayTracing(const Grid &grid, uint width, uint height, float t, uint nbSphere) :
		Animable_I<uchar4>(grid, width, height, "RayTracing Roulin")
{
	this->t = t;
	this->nbSphere = nbSphere;
}

RayTracing::~RayTracing(void)
{
	// Rien
}

/* ~~~~~~~~~~  METHODS  ~~~~~~~~~~ */
/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
{
	Device::lastCudaError("raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release

	// start kernel
	rayTracing<<<dg, db>>>(ptrDevPixels, w, h, t);

	Device::lastCudaError("raytracing rgba uchar4 (after)"); // facultatif, for debug only, remove for release
}

/* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */

void RayTracing::animationStep()
{
	this->t += t;
}

/**
 * Override (code naturel omp)
 */