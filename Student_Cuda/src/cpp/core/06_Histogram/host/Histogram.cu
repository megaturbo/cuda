#include <iostream>

#include "Device.h"
#include "Histogram.h"

using std::cout;
using std::endl;

const int SIZE_TAB_SM = 256;

extern __global__ void histogram(int* ptrTabData, int tabSize, int *ptrDevResult);

Histogram::Histogram(int tabSize) :
		tabSize(tabSize)
{
	this->ptrTabResult = new int[SIZE_TAB_SM];
	this->ptrTabData = new int[tabSize];

	// Create data array
	for (int i = 0; i < tabSize; i++)
		ptrTabData[i] = i % SIZE_TAB_SM;

	// Shuffle tab
	for (int i = 0; i < tabSize; i++)
	{
		int a = rand() % tabSize;
		int b = rand() % tabSize;

		// Le meilleur swap du monde
		ptrTabData[a] = ptrTabData[a] ^ ptrTabData[b];
		ptrTabData[b] = ptrTabData[b] ^ ptrTabData[a];
		ptrTabData[a] = ptrTabData[a] ^ ptrTabData[b];
	}

	this->sizeOctetResult = sizeof(int) * SIZE_TAB_SM; // octet
	this->sizeOctetData = sizeof(int) * tabSize;

	// Allocation-party
	HANDLE_ERROR(cudaMalloc(&ptrTabOut, sizeOctetResult));
	HANDLE_ERROR(cudaMalloc(&ptrTabIn, sizeOctetData));

	// Memory set party
	HANDLE_ERROR(cudaMemset(ptrTabOut, 0, sizeOctetResult));
	HANDLE_ERROR(
			cudaMemcpy(ptrTabIn, ptrTabData, sizeOctetData,
					cudaMemcpyHostToDevice));

	Device::lastCudaError("histogramme.cu constructor"); // temp debug

	// Grid

	this->dg = dim3(16, 2, 1);
	this->db = dim3(256, 1, 1); 	// Produit doit être ^2

	Device::gridHeuristic(dg, db); // optionnel

}

Histogram::~Histogram(void)
{
	Device::lastCudaError("histogram.cu destructor begin"); // temp debug
	HANDLE_ERROR(cudaFree(ptrTabOut));
	Device::lastCudaError("histogram.cu destructor end"); // temp debug
}

int* Histogram::run()
{
	Device::lastCudaError("histogram run begin");
	histogram<<<dg,db,sizeOctetResult>>>(ptrTabIn, tabSize, ptrTabOut); // asynchrone
	Device::lastCudaError("histogram run end");

	HANDLE_ERROR(cudaMemcpy(ptrTabResult, ptrTabOut, sizeOctetResult ,cudaMemcpyDeviceToHost));

	return ptrTabResult;
}
