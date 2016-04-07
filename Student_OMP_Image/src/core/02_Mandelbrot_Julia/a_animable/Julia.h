#pragma once

#include "JuliaMath.h"

#include "cudaType_CPU.h"
#include "Variateur_CPU.h"
#include "Animable_I_CPU.h"
using namespace cpu;

/* ========== DECLARATION =========== */

class Julia: public Animable_I<uchar4>
{
	/* ---------- PUBLIC ---------- */

	/* ~~~~~~~~~~ CONSTRUCTEUR ~~~~~~~~~~ */

public:

	Julia(uint width, uint height, float deltaTime, uint n,
			float c1, float c2,	const DomaineMath &domaineMath);

	virtual ~Julia(void);

	/* ~~~~~~~~~~ Methodes ~~~~~~~~~~ */

	/* ---------- OVERRIDE ANIMABLE_I ---------- */

	/**
	 * Called periodically by the api
	 */

	virtual void processEntrelacementOMP(uchar4* ptrTabPixels, uint width,
			uint height, const DomaineMath &domaineMath);

	/**
	 * Called periodically by the api
	 */

	virtual void processForAutoOMP(uchar4* ptrTabPixels, uint width,
			uint height, const DomaineMath &domaineMath);

	/**
	 * Called periodically by the api
	 */

	virtual void animationStep();

	/* ---------- PRIVATE ---------- */

private:

	void workPixel(uchar4* ptrColorIJ, int pixel_row, int pixel_column,
			const DomaineMath &domaineMath, JuliaMath* ptrJuliaMath);

	/* ---------- ATTRIBUTS ---------- */

	// Inputs
	uint n;
	float c1;
	float c2;

	// Tools
	Variateur<float> variateurAnimation;
};
