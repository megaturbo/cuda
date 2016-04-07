#pragma once

#include "cudaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*-----------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Sackoverflow.com/questions/17399119/cant-we-use-atomic-operations-for-floating-point-variables-in-cuda
 *
 * http://stackoverflow.com/questions/17399119/cant-we-use-atomic-operations-for-floating-point-variables-in-cuda
 */
__device__ __forceinline__ int floatToOrderedInt(float floatVal)
    {
    int intVal = __float_as_int(floatVal);
    return (intVal >= 0) ? intVal : intVal ^ 0x7FFFFFFF;
    }

__device__ __forceinline__ float orderedIntToFloat(int intVal)
    {
    return __int_as_float((intVal >= 0) ? intVal : intVal ^ 0x7FFFFFFF);
    }

/**
 * Implementing an atomicMin for float using atomicCAS
 * You need to map float to orderedIntFloat
 * source : http://stackoverflow.com/questions/17399119/cant-we-use-atomic-operations-for-floating-point-variables-in-cuda
 */
__device__ static float atomicMin(float* address, float val)
    {
    int* address_as_i = (int*) address;
    int old = *address_as_i, assumed;
    do
	{
	assumed = old;
	old = atomicCAS(address_as_i, assumed, floatToOrderedInt(fminf(val, orderedIntToFloat(assumed))));
	}
    while (assumed != old);
    return orderedIntToFloat(old);
    }

/**
 * Implementing an atomicMax for float using atomicCAS
 *
 * You need to map float to orderedIntFloat
 * source : http://stackoverflow.com/questions/17399119/cant-we-use-atomic-operations-for-floating-point-variables-in-cuda
 */
__device__ static float atomicMax(float* address, float val)
    {
    int* address_as_i = (int*) address;
    int old = *address_as_i, assumed;
    do
	{
	assumed = old;
	old = atomicCAS(address_as_i, assumed, floatToOrderedInt(fmaxf(val, orderedIntToFloat(assumed))));
	}
    while (assumed != old);
    return orderedIntToFloat(old);
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
