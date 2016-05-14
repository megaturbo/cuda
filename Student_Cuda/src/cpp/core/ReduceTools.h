#pragma once

#include "Indice2D.h"

template<typename T>
__device__
void crush(T* tabSM, int half)
{
	const int TID_LOCAL = Indice2D::tidLocal();
	const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();
	int s = TID_LOCAL;
	while (s < half)
	{
		tabSM[s] += tabSM[s + half];
		s += NB_THREAD_LOCAL;
	}
}

template<typename T>
__device__
void reduceIntraBlock(T* tabSM)
{
	const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();
	int half = NB_THREAD_LOCAL / 2;
	while (half >= 1)
	{
		crush(tabSM, half);
		half /= 2;
		__syncthreads();
	}
}

template<typename T>
__device__
void reduceInterBlock(T* tabSM, T* ptrDevResult)
{
	if (Indice2D::tidLocal() == 0)
	{
		atomicAdd(ptrDevResult, tabSM[0]);
	}
}
