#include "Montecarlo.h"

#include <iostream>
#include <curand_kernel.h>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void montecarlo(curandState* ptrTabDevGeneratorGM,int* ptrDevN0, float a, float b, float M, int nbFlechettes);
extern __global__ void setup_kernel_rand(curandState* tabGeneratorThread, int deviceId);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(float a, float b, float M, int nbFlechettes) :
		a(a), b(b), M(M), nbFlechettes(nbFlechettes)
{

	// Grid
	{
		this->dg = dim3(16, 2, 1); // disons, a optimiser selon le gpu
		this->db = dim3(32, 4, 1); // Une puissance de 2 !

		Device::gridHeuristic(dg, db);
	}

	this->sizeOctetTabGenerator = dg.x * dg.y * dg.z * db.x * db.y * db.z * sizeof(curandState); // octet
	this->sizeOctetN0 = sizeof(int);
	this->sizeSM = db.x * db.y * db.z * sizeof(int);

	// MM
	{
		// MM (malloc Device)
		{
			HANDLE_ERROR(cudaMalloc(&ptrDevN0, sizeOctetN0));
			HANDLE_ERROR(cudaMalloc(&ptrTabDevGeneratorGM, sizeOctetTabGenerator));
		}

		// MM (memset Device)
		{
			// C'est là qu'il y a un résultat, on pourrait faire foirer des trucs
			HANDLE_ERROR(cudaMemset(ptrDevN0, 0, sizeOctetN0));
		}

		Device::lastCudaError("Montecarlo MM (end allocation)"); // temp debug
	}

	setup_kernel_rand<<<dg, db>>>(ptrTabDevGeneratorGM, Device::getDeviceId());
}

Montecarlo::~Montecarlo(void)
{
	//MM (device free)
	{
		HANDLE_ERROR(cudaFree(ptrDevN0));
		HANDLE_ERROR(cudaFree(ptrTabDevGeneratorGM));

		Device::lastCudaError("Montecarlo MM (end deallocation)"); // temp debug
	}
}

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

float Montecarlo::getPi()
{
	return this->pi;
}

void Montecarlo::run()
{
	Device::lastCudaError("Montecarlo (before)"); // temp debug
	montecarlo<<<dg,db, sizeSM>>>(ptrTabDevGeneratorGM, ptrDevN0, a, b, M, nbFlechettes); // assynchrone
	Device::lastCudaError("Montecarlo (after)"); // temp debug

	Device::synchronize(); // Temp, only for printf in  GPU

	// MM (Device -> Host)
	{
		HANDLE_ERROR(cudaMemcpy(&N0, ptrDevN0, sizeOctetN0, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
	}

	float delta = fabsf(b - a);
	float rektArea = M * delta;
	float ratioFlechette = N0 / (float)nbFlechettes;
	pi = 2 * rektArea * ratioFlechette;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
