#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

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
Animable_I<uchar4>* MandelbrotProvider::createAnimable(void)
{
	int n = 12;
	DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);

//	int n = 102;
//	DomaineMath domaineMath = DomaineMath(-1.3968, -0.03362, -1.3578, 0.0013973);

	float dt = 0.0f;

	//Dims
	int dw = 16 * 80;
	int dh = 16 * 60;

	return new Mandelbrot(dw, dh, dt, n, domaineMath);
}

/**
 * Override
 */
Image_I* MandelbrotProvider::createImageGL(void)
{
	ColorRGB_01 textColor(0, 0, 0); // black
	return new ImageAnimable_RGBA_uchar4(createAnimable(), textColor);
}

/* ---------- PRIVATE ---------- */
