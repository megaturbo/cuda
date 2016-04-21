#include "Indice1D.h"
#include "cudaTools.h"
#include "ReduceTools.h"

#include <stdio.h>

__global__ void slice(float *ptrDevPi, int nbSlice);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reduceIntraThread(float* tabSM, int nbSlice);
static __device__ float f(int x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void slice(float* ptrDevPi, int nbSlice)
{
	extern __shared__ float tabSM[];
	reduceIntraThread(tabSM, nbSlice);
	__syncthreads();

	const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();

	ReduceTools<float> reduceTools(NB_THREAD_BLOCK);
	reduceTools.reduceIntraBlock(tabSM);
	reduceTools.reduceInterBlock(tabSM, ptrDevPi);
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__
void reduceIntraThread(float *tabSM, int nbSlice)
{
	float sumThread = 0;

	const int TID_LOCAL = Indice1D::tidLocal();
	const int TID = Indice1D::tid();
	const int NB_THREAD = Indice1D::nbThread();

	int s = TID;
	while (s < nbSlice)
	{
		sumThread += f(s);
		s += NB_THREAD;
	}
	tabSM[TID_LOCAL] = sumThread;
}

__device__
float f(int x)
{
//	return 1.f / (1.f + (float) x * (float) x);
	return 1.f;
}
