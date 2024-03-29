#include <iostream>
#include <assert.h>

#include "Device.h"
#include "Julia.h"
#include "DomaineMath_GPU.h"

using std::cout;
using std::endl;

/* ========== DECLARATION ========== */

extern __global__ void julia(uchar4* ptrDevPixels, uint w, uint h, float t, uint n, float c1, float c2, DomaineMath domaineMath);

/* ---------- PUBLIC ---------- */

Julia::Julia(const Grid &grid, uint width, uint height, float t,
		uint n, float c1, float c2, const DomaineMath &domaineMath) :
		Animable_I<uchar4>(grid, width, height, "Julia Roulin",
				domaineMath)
{
	// Inputs
	this->n = n;
	this->c1 = c1;
	this->c2 = c2;

	// Tools
	this->t = t;
}

Julia::~Julia(void)
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
void Julia::process(uchar4* ptrDevPixels, uint w, uint h,
		const DomaineMath& domaineMath)
{
	Device::lastCudaError("julia rgba uchar4 (before)"); // facultatif, for debug only, remove for release

	// start kernel
	julia<<<dg, db>>>(ptrDevPixels, w, h, t, n, c1, c2, domaineMath);

	Device::lastCudaError("julia rgba uchar4 (after)"); // facultatif, for debug only, remove for release
}

/* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */

void Julia::animationStep()
{
	this->t += t;
}

/**
 * Override (code naturel omp)
 */
