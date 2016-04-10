#include "Mandelbrot.h"
#include "MandelbrotMath.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/* ========== DECLARATION ========== */

__global__ void processMandelbrot(uchar4* ptrDevPixels, int w, int h, int n, const DomaineMath& domaineMath);

/* ---------- PUBLIC ---------- */

Mandelbrot::Mandelbrot(uint width, uint height, float deltaTime, uint n,
		const DomaineMath &domaineMath) :
		Animable_I<uchar4>(width, height, "Mandelbrot Roulin", domaineMath), variateurAnimation(
				Interval<float>(0, 2 * PI), deltaTime)
{
	// Inputs
	this->n = n;

	// Tools
	this->t = 0;
	this->parallelPatern = ParallelPatern::OMP_MIXTE;

	// OMP
	cout << "\n[Mandelbrot] : OMP : nbThread = " << this->nbThread << endl;
}

Mandelbrot::~Mandelbrot(void)
{
	// Rien
}

/* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */

void Mandelbrot::animationStep()
{
	this->t = variateurAnimation.varierAndGet();
}

/**
 * Override (code naturel omp)
 */