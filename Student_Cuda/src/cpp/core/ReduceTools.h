#pragma once

#include "Indice1D.h"
#include "cudaTools.h"

template<typename T>
class ReduceTools
{
public:
	__device__
	ReduceTools(int n)
	{
		this->n = n;
	}

	__device__
	virtual ~ReduceTools()
	{
	}

	__device__
	void reduceIntraBlock(T* tabSM)
	{
		int half = n / 2;
		while (n > 1)
		{
			crush(tabSM, half);
			half /= 2;
			__syncthreads();
		}
	}

	__device__
	void reduceInterBlock(T* tabSM, T* ptrDevResult)
	{
		if (Indice1D::tidLocal() ==  0)
		{
			atomicAdd(ptrDevResult, tabSM[0]);
		}
	}


private:
	__device__
	void crush(T* tabSM, int half)
	{
		const int TID = Indice1D::tidBlock();
		const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
		int s = TID;
		while (s < half)
		{
			tabSM[s] += tabSM[s + half];
			s += NB_THREAD_BLOCK;
			__syncthreads();
		}
	}

// Input
	int n;
};
