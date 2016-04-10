#pragma once
#include "cudaTools.h"

#include "Provider_I_GPU.h"

using namespace gpu;

/* ========== DECLARATION ========== */

// ========== PUBLIC
class JuliaProvider: public Provider_I<uchar4>
{
public:

	virtual ~JuliaProvider()
	{
		// Nope
	}

	/* ---------- OVERRIDE ---------- */

	virtual Animable_I<uchar4>* createAnimable(void);

	virtual Image_I* createImageGL(void);
};
