#include "JuliaProvider.h"
#include "Julia.h"

#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"
using namespace cpu;

/* ========== DECLARATION =========== */

/* ---------- IMPORTED ---------- */

/* ---------- PUBLIC ---------- */

/* ---------- PRIVATE ---------- */

/* ========== IMPLEMENTATION ========== */

/* ---------- PUBLIC ---------- */

/* ---------- OVERLOADS ---------- */

/**
 * Override
 */
Animable_I<uchar4>* JuliaProvider::createAnimable(void)
{
//	uint n = 52;
//	float c1 = -0.12;
//	float c2 = 0.85;
//	DomaineMath domaineMath = DomaineMath(-1.3, -1.4, 1.3, 1.4);
//	DomaineMath domaineMath = DomaineMath(-0.327167, -0.2156, -0.086667, 0.0434);	// uses same n and c

	uint n = 300;
	float c1 = -0.745;
	float c2 = 0.1;
	DomaineMath domaineMath = DomaineMath(-1.7, -1.0, 1.7, 1.0);


	float dt = 0.0f;

	// Dims
	int dw = 16 * 80;
	int dh = 16 * 60;

	return new Julia(dw, dh, dt, n, c1, c2, domaineMath);
}

/**
 * Override
 */
Image_I* JuliaProvider::createImageGL(void)
{
	ColorRGB_01 textColor(0, 0, 0); // black
	return new ImageAnimable_RGBA_uchar4(createAnimable(), textColor);
}

/* ---------- PRIVATE ---------- */
