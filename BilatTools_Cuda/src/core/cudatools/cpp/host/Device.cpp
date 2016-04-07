#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <helper_cuda.h> //pris dans sample/common/inc. A changer avec chaque nouvelle version de cuda

#include "Device.h"
#include "cudaTools.h"
#include "Chrono.h"
#include "omp.h"
#include "StringTools.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void cout01(int isTrue);
static void coutBool(bool isFlag);
static int dim(const dim3& dim);
static string toString(Family family);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------*\
|* wrapper      *|
 \*-------------*/

void Device::synchronize(void)
    {
    cudaDeviceSynchronize();
    }

/*--------------*\
|* Tools      *|
 \*-------------*/

void Device::lastCudaError(const char *message)
    {
    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess)
	{
	if (message != NULL)
	    {
	    fprintf(stderr, "\n[CUDA ERROR] : %s: %s\n\n", message, cudaGetErrorString(error));
	    }
	else
	    {
	    fprintf(stderr, "\n[CUDA ERROR] : %s\n\n", cudaGetErrorString(error));
	    }
	exit(EXIT_FAILURE);
	}
    }

void Device::gridHeuristic(const dim3& dg, const dim3& db)
    {
    gridAssert(dg, db);

    int mpCount = Device::getMPCount();
    int warpSize = Device::getWarpSize();
    int nbCoreMP = Device::getCoreCountMP();

    int nbBlock = dim(dg);
    int nbThreadBlock = dim(db);

    // grid
	{
	if (nbBlock < mpCount || nbBlock % mpCount != 0)
	    {
	    cout << endl;
	    cout << "[Device] : Warning : dg : heuristic for best performance is not satisfied !" << endl;
	    cout << "[Device] : grid : ";
	    print(dg, "dg");
	    cout << "[Device] : nbBlock (current)= " + StringTools::toString(nbBlock) << endl;
	    cout << "[Device] : Heuristic : To improve performance, try with a multiple of #MP=" + StringTools::toString(mpCount) << endl;
	    }
	}

    // warp
	{
	if (nbThreadBlock < warpSize || nbThreadBlock % warpSize != 0)
	    {
	    cout << endl;
	    cout << "[Device] : Warning : db : heuristic for best performance is not satisfied !" << endl;
	    cout << "[Device] : grid : ";
	    print(db, "db");
	    cout << "[Device] : nbThreadBlock (current) = " + StringTools::toString(nbThreadBlock) << endl;
	    cout << "[Device] : Heuristic : To improve performance, try with a multiple of |warp|=" + StringTools::toString(warpSize) << endl;
	    }
	else // erreur plus fine que celle ci-dessus, d'abor resouder celle-ci dessus
	    {
	    // block
		{
		// todo a creuser
		int nbBlockByMP = nbBlock / mpCount;
		int nbThreadMP = nbBlockByMP * nbThreadBlock;
		if (nbThreadMP % nbCoreMP != 0)
		    {
		    cout << endl;
		    cout << "[Device] : Warning : heuristic for best performance is not satisfied !" << endl;
		    cout << "[Device] : grid : ";
		    print(dg, db);
		    cout << "[Device] : All core of MP seemed to be not use! " << endl;
		    cout << "[Device] : #core/MP             = " << Device::getCoreCountMP() << endl;
		    cout << "[Device] : #thread/MP (current) = " << nbThreadMP << endl;
		    cout << "[Device] : " << nbThreadMP << " is not un multiple of " << Device::getCoreCountMP() << endl;
		    }
		}
	    }

	// threadTotal
	    {
	    int nbThreadTotal = nbThread(dg, db);

	    if (nbThreadTotal < Device::getCoreCount())
		{
		cout << endl;
		cout << "[Device] : Warning : You don't use all the core of GPU !" << endl;
		cout << "[Device] : grid : ";
		print(dg, db);
		cout << "[Device] : #core Total             = " << Device::getCoreCount() << endl;
		cout << "[Device] : #thread total (current) = " << nbThreadTotal << endl;
		}
	    }
	}
    }

void Device::gridHeuristic(const Grid& grid)
    {
    gridHeuristic(grid.dg, grid.db);
    }

void Device::gridAssert(const dim3& dg, const dim3& db)
    {
// grid
	{
	dim3 dimGridMax = Device::getMaxGridDim();

	assert(dg.x <= dimGridMax.x && dg.x >= 1);
	assert(dg.y <= dimGridMax.y && dg.y >= 1);
	assert(dg.z <= dimGridMax.z && dg.z >= 1);
	}

// block
	{
	dim3 dimBlockMax = Device::getMaxBlockDim();

	assert(db.x <= dimBlockMax.x && db.x >= 1);
	assert(db.y <= dimBlockMax.y && db.y >= 1);
	assert(db.z <= dimBlockMax.z && db.z >= 1);
	}

// Thread per block
	{
	int nbThreadBlock = dim(db);
	assert(nbThreadBlock <= getMaxThreadPerBlock() && nbThreadBlock >= 1);
	}
    }

void Device::gridAssert(const Grid& grid)
    {
    gridAssert(grid.dg, grid.db);
    }

void Device::print(const dim3& dg, const dim3& db)
    {
    cout << endl;
    print(dg, "dg");
    print(db, "db");
    }

void Device::print(const dim3& dim, string titre)
    {
    cout << titre << "(" << dim.x << "," << dim.y << "," << dim.z << ") " << endl;
    }

void Device::print(const Grid& grid)
    {
    print(grid.dg, grid.db);
    }

int Device::nbThread(const dim3& dg, const dim3& db)
    {
    return dim(dg) * dim(db);
    }

int Device::nbThread(const Grid& grid)
    {
    return nbThread(grid.dg, grid.db);
    }

int Device::dim(const dim3& dim)
    {
    return dim.x * dim.y * dim.z;
    }

/*--------------*\
|* 	get      *|
 \*-------------*/

int Device::getDeviceId(void)
    {
    int deviceId;
    HANDLE_ERROR(cudaGetDevice(&deviceId));

    return deviceId;
    }

int Device::getDeviceCount(void)
    {
    int nbDevice;
    HANDLE_ERROR(cudaGetDeviceCount(&nbDevice));

    return nbDevice;
    }

cudaDeviceProp Device::getDeviceProp(int idDevice)
    {
    cudaDeviceProp prop;
    HANDLE_ERROR(cudaGetDeviceProperties(&prop, idDevice));
    return prop;
    }

cudaDeviceProp Device::getDeviceProp(void)
    {
    return getDeviceProp(getDeviceId());
    }

/*--------------------------------------*\
 |*		Secondaire		*|
 \*-------------------------------------*/

/*--------------*\
|* 	get      *|
 \*-------------*/

string Device::getNameSimple(int idDevice)
    {
    return getDeviceProp(idDevice).name;
    }

string Device::getNameSimple()
    {
    return getNameSimple(getDeviceId());
    }

string Device::getName(int idDevice)
    {
    string id = StringTools::toString(idDevice);
    string a = StringTools::toString(getCapacityMajor(idDevice));
    string b = StringTools::toString(getCapacityMinor(idDevice));

    return "[" + getNameSimple(idDevice) + "] id=" + id + " sm=" + a + "" + b;
    }

string Device::getName()
    {
    return getName(getDeviceId());
    }

dim3 Device::getMaxGridDim(int idDevice)
    {
    cudaDeviceProp prop = getDeviceProp(idDevice);

    return dim3(prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    }

dim3 Device::getMaxGridDim()
    {
    return getMaxGridDim(getDeviceId());
    }

dim3 Device::getMaxBlockDim(int idDevice)
    {
    cudaDeviceProp prop = getDeviceProp(idDevice);

    return dim3(prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
    }

dim3 Device::getMaxBlockDim()
    {
    return getMaxBlockDim(getDeviceId());
    }

int Device::getMaxThreadPerBlock(int idDevice)
    {
    return getDeviceProp(idDevice).maxThreadsPerBlock;
    }

int Device::getMaxThreadPerBlock()
    {
    return getMaxThreadPerBlock(getDeviceId());
    }

int Device::getWarpSize(int idDevice)
    {
    return getDeviceProp(idDevice).warpSize;
    }

int Device::getWarpSize(void)
    {
    return getWarpSize(getDeviceId());
    }

int Device::getMPCount(int idDevice)
    {
    return getDeviceProp(idDevice).multiProcessorCount;
    }

int Device::getMPCount(void)
    {
    return getMPCount(getDeviceId());
    }

/**
 * total
 */
int Device::getCoreCount(int idDevice)
    {
    return getCoreCountMP(idDevice) * getMPCount(idDevice);
    }

/**
 * total
 */
int Device::getCoreCount(void)
    {
    return getCoreCount(getDeviceId());
    }

/**
 * by MP
 */
int Device::getCoreCountMP(int idDevice)
    {
    int major = getCapacityMajor(idDevice);
    int minor = getCapacityMinor(idDevice);

    return _ConvertSMVer2Cores(major, minor);
    }

/**
 * by MP
 */
int Device::getCoreCountMP(void)
    {
    return getCoreCountMP(getDeviceId());
    }

int Device::getCapacityMajor(int idDevice)
    {
    return getDeviceProp(idDevice).major;
    }

int Device::getCapacityMajor()
    {
    return getCapacityMajor(getDeviceId());
    }

int Device::getCapacityMinor(int idDevice)
    {
    return getDeviceProp(idDevice).minor;
    }

int Device::getCapacityMinor()
    {
    return getCapacityMinor(getDeviceId());
    }

int Device::getRuntimeVersion()
    {
    int version = -1;
    cudaRuntimeGetVersion(&version);
    return version;

//  return CUDART_VERSION;
    }

int Device::getDriverVersion(void)
    {
    int version = -1;
    cudaDriverGetVersion(&version);
    return version;
    }

int Device::getAsyncEngineCount(int idDevice)
    {
    return getDeviceProp(idDevice).asyncEngineCount;
    }

int Device::getAsyncEngineCount()
    {
    return getAsyncEngineCount(getDeviceId());
    }

/*--------------*\
|* 	is      *|
 \*-------------*/

/**
 * 64 bits only
 */
bool Device::isUVAEnable(int idDevice)
    {
    return getCapacityMajor() >= 2.0 && getRuntimeVersion() >= 4000;
    }

/**
 * 64 bits only
 */
bool Device::isUVAEnable()
    {
    return isUVAEnable(getDeviceId());
    }

bool Device::isAtomicShareMemoryEnable(int idDevice)
    {
    return (getCapacityMajor(idDevice) == 1 && Device::getCapacityMinor(idDevice) >= 2) || getCapacityMajor(idDevice) >= 2;
    }

bool Device::isAtomicShareMemoryEnable()
    {
    return isAtomicShareMemoryEnable(getDeviceId());
    }

bool Device::isHostMapMemoryEnable(int idDevice)
    {
    return getDeviceProp(idDevice).canMapHostMemory;
    }

bool Device::isHostMapMemoryEnable()
    {
    return isHostMapMemoryEnable(getDeviceId());
    }

bool Device::isECCEnable(int idDevice)
    {
    return getDeviceProp(idDevice).ECCEnabled;
    }

bool Device::isECCEnable(void)
    {
    return isECCEnable(getDeviceId());
    }

bool Device::isAsyncEngine(int idDevice)
    {
    return getDeviceProp(idDevice).deviceOverlap;
    }

bool Device::isAsyncEngine(void)
    {
    return isAsyncEngine(getDeviceId());
    }

/*--------------------------------------*\
 |*		Architecture		*|
 \*-------------------------------------*/

bool Device::isCuda(void)
    {
    return getDeviceCount() >= 1;
    }

bool Device::isFermi(int idDevice)
    {
    int c = getCapacityMajor(idDevice);

    return c >= 2 && c < 3;
    }

bool Device::isFermi()
    {
    return isFermi(getDeviceId());
    }

bool Device::isKepler(int idDevice)
    {
    int c = getCapacityMajor(idDevice);

    return c >= 3 && c < 4;
    }

bool Device::isKepler()
    {
    return isKepler(getDeviceId());
    }

bool Device::isMaxwell(int idDevice)
    {
    int c = getCapacityMajor(idDevice);

    return c >= 5 && c < 6;
    }

bool Device::isMaxwell(void)
    {
    return isMaxwell(getDeviceId());
    }

Family Device::getFamily(int idDevice)
    {
    if (isFermi(idDevice))
	{
	return Family::FERMI;
	}
    else if (isKepler(idDevice))
	{
	return Family::KEPPLER;
	}
    else if (isMaxwell(idDevice))
	{
	return Family::MAXWELL;
	}
    else
	{
	return Family::UNKNOWN;
	}
    }

Family Device::getFamily()
    {
    return getFamily(getDeviceId());
    }

/*--------------------------------------*\
 |*		Print			*|
 \*-------------------------------------*/

void Device::print(int idDevice)
    {
    cudaDeviceProp prop = getDeviceProp(idDevice);

    cout << endl;
    cout << "===========================================" << endl;
    cout << " " << prop.name << "  :  id=" << idDevice << "  :  sm=" << prop.major << "" << prop.minor << "       :" << endl;
    cout << "===========================================" << endl;

    cout << endl;
    cout << "Device                   : " << endl;
    cout << "Device id                : " << idDevice << endl;
    cout << "Name                     : " << prop.name << endl;
    cout << "GPU capability           : " << prop.major << "." << prop.minor << "" << endl;
    cout << "Family                   : " << toString(getFamily(idDevice)) << endl;
    cout << "Clock rate               : " << prop.clockRate / 1000 << " MHZ" << endl;
    cout << "GPU integrated on MB     : ";
    cout01(prop.integrated);
    cout << "Limit execution (timeout): ";
    cout01(prop.kernelExecTimeoutEnabled);
// cout << "ComputeMode              : " << prop.computeMode << endl;

    cout << endl;
    cout << "Performance              : " << endl;
    cout << "MP count                 : " << prop.multiProcessorCount << endl;
    cout << "Core count (Total)       : " << getCoreCount(idDevice) << endl;
    cout << "Core/MP                  : " << getCoreCountMP(idDevice) << endl;
    cout << "Threads in warp          : " << prop.warpSize << endl;

    cout << endl;
    cout << "Grid                     : " << endl;
    cout << "Max threads per block    : " << prop.maxThreadsPerBlock << endl;
    cout << "Max block dim            : (" << prop.maxThreadsDim[0] << "," << prop.maxThreadsDim[1] << "," << prop.maxThreadsDim[2] << ")" << endl;
    cout << "Max grid dim             : (" << prop.maxGridSize[0] << "," << prop.maxGridSize[1] << "," << prop.maxGridSize[2] << ")" << endl;

    cout << endl;
    cout << "Memory                   : " << endl;
    cout << "Global Memory            : " << prop.totalGlobalMem / 1024 / 1024 << " MB" << endl;
    cout << "Constant Memory          : " << prop.totalConstMem / 1024 << " KB" << endl;
    cout << "Shared memory per block  : " << prop.sharedMemPerBlock / 1024 << " KB " << endl;
    cout << "#Register      per block : " << prop.regsPerBlock << " (32-bit by register)" << endl;

    cout << endl;
    cout << "Texture                  : " << endl;
    cout << "Texture1D max size       : (" << prop.maxTexture1D << ")" << endl;
    cout << "Texture2D max size       : (" << prop.maxTexture2D[0] << "," << prop.maxTexture2D[1] << ")" << endl;
    cout << "Texture3D max size       : (" << prop.maxTexture3D[0] << "," << prop.maxTexture3D[1] << "," << prop.maxTexture3D[2] << ")" << endl;
//cout << "Texture2D Array max Size : (" << ptrProp.maxTexture2DArray[0] << "," << ptrProp.maxTexture2DArray[1] << "," << ptrProp.maxTexture2DArray[2] << ")"<< endl;
    cout << "Texture Alignment        : " << prop.textureAlignment << " B" << endl;
    cout << "Max mem pitch            : " << prop.memPitch << endl;

    cout << endl;
    cout << "GPU Capacity : " << endl;
    cout << "MapHostMemory                                                        : ";
    cout01(isHostMapMemoryEnable());
    cout << "AtomicOperation sharedMemory                                         : ";
    cout01(isAtomicShareMemoryEnable());

    cout << "UVA (Unified Virtual Addressing)                                     : ";
    cout01(isUVAEnable());

    cout << "ECCEnabled				                             : ";
    cout01(prop.ECCEnabled);

    cout << "Concurrent bidirectional copy  (DMA only!)                           : ";
    cout01(prop.deviceOverlap);
    if (prop.deviceOverlap)
	{
	cout << "Concurrent bidirectional copy  : host->device // device->host        : " << getAsyncEngineCount(idDevice) << endl;
	}

    cout << "Concurrent Kernels (fermi 16x)  				     : ";
    cout01(prop.concurrentKernels);
    cout << endl;
    if (Device::getDeviceCount() >= 2)
	{
	printP2PmatrixCompatibility();
	}

    cout << "Cuda Runtime version     :  " << getRuntimeVersion() << endl;
    cout << "Cuda Driver  version     :  " << getDriverVersion() << endl;
    cout << endl;
//  cout << "=================== end ========================" << endl;

//    cout << endl;
//    cout << "===========================================" << endl;
//    cout << "Cuda Runtime version     :  " << getRuntimeVersion() << endl;
//    cout << "===========================================" << endl;
//    cout << endl;
    }

void Device::print()
    {
    print(getDeviceId());
    }

void Device::printAll()
    {
    cout << "\nList of all GPU available :" << endl;
    printAllSimple();

    cout << endl << "Details :" << endl;
    int deviceCount = getDeviceCount();

    for (int id = 0; id < deviceCount; id++)
	{
	print(id);
	}

    printCurrent();
    }

void Device::printAllSimple()
    {
    cout << endl;
    cout << "==============================================================" << endl;
    cout << "[CUDA] : List GPU Available : cuda version = " << getRuntimeVersion() << endl;
    cout << "==============================================================" << endl;
    cout << endl;

    int current = getDeviceId();
    for (int id = 0; id < getDeviceCount(); id++)
	{
	cout << getName(id);
	cout << " #MP="<<getMPCount(id);
	cout << " #core/MP="<<getCoreCountMP(id);
	if (id == current)
	    {
	    cout << " : [CURRENT]";
	    }
	cout << endl;
	}

    cout << endl;
    }

void Device::printCurrent()
    {
    cout << "==============================================================" << endl;
    cout << "[Cuda] : current device : " << getName() << endl;
    cout << "==============================================================" << endl;
    }

/*--------------*\
|* 	load      *|
 \*-------------*/

/**
 * Linux : nvidia-smi -pm 1 utile? TODO
 * marche pas pour opengl
 */
void Device::loadCudaDriver(int deviceID, bool isMapMemoryAsk)
    {
    Chrono chrono("loadCudaDriver_" + deviceID);
    cout << "\nDevice(" << deviceID << ") : Load Driver ";

    int* ptrBidon;

    HANDLE_ERROR(cudaSetDevice(deviceID));

    if (isHostMapMemoryEnable() && isMapMemoryAsk)
	{
	HANDLE_ERROR(cudaSetDeviceFlags(cudaDeviceMapHost));
	cout << "(HostMapMemory activate) : " << flush;
	}
    else if (!isHostMapMemoryEnable() && isMapMemoryAsk)
	{
	cerr << "(HostMapMemory not enable) : " << flush;
	}

    HANDLE_ERROR(cudaMalloc((void** ) &ptrBidon, sizeof(int)));
    HANDLE_ERROR(cudaFree(ptrBidon));

    chrono.stop();
    cout << chrono.getDeltaTime() << " (s)" << endl << endl;
    }

void Device::loadCudaDriver(bool isMapMemoryEnable)
    {
    loadCudaDriver(getDeviceId(), isMapMemoryEnable);
    }

void Device::loadCudaDriverAll(bool isMapMemoryEnable)
    {
    cout << "\nLoad Cuda Driver : start ..." << endl;
    Chrono chrono("loadCudaDriver_ALL");

    int k = Device::getDeviceCount();
//omp_set_num_threads(k);
//#pragma omp parallel for
    for (int i = 0; i < k; i++)
	{
	loadCudaDriver(i, isMapMemoryEnable);
	}

    chrono.stop();
    cout << "Load Cuda Driver : end  : " << chrono.getDeltaTime() << " (s)\n" << endl;
    }

/*--------------*\
|* 	p2p      *|
 \*-------------*/

void Device::printP2PmatrixCompatibility()
    {
    int* matrixP2PCompatibility = p2pMatrixCompatibility();
    int* ptrMatrixP2PCompatibility = matrixP2PCompatibility;

    int n = Device::getDeviceCount();
    cout << "P2P compatibility : symetric matrix (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++)
	{
	for (int j = 0; j < n; j++)
	    {
	    if (i != j)
		{
		cout << *ptrMatrixP2PCompatibility << " ";
		}
	    else
		{
		cout << "  ";
		}

	    ptrMatrixP2PCompatibility++;
	    }
	cout << endl;
	}
    cout << endl;

    delete[] matrixP2PCompatibility;
    }

void Device::p2pEnableALL()
    {
    int n = Device::getDeviceCount();

    int* matrixP2PCompatibility = p2pMatrixCompatibility();
    int* ptrMatrixP2PCompatibility = matrixP2PCompatibility;

    if (n >= 2)
	{
	cout << "P2P enable : symetric matrix (" << n << "x" << n << "):" << endl;
	}

    for (int i = 0; i < n; i++)
	{
	for (int j = 0; j < n; j++)
	    {
	    if (i != j)
		{
		cout << *ptrMatrixP2PCompatibility << " ";
		}
	    else
		{
		cout << "  ";
		}

	    if (*ptrMatrixP2PCompatibility)
		{
		int flaginutile = 0;
		HANDLE_ERROR(cudaSetDevice(i));
		HANDLE_ERROR(cudaDeviceEnablePeerAccess(j, flaginutile));
		}
	    ptrMatrixP2PCompatibility++;
	    }
	}

    delete[] matrixP2PCompatibility;
    }

int* Device::p2pMatrixCompatibility()
    {
    int n = Device::getDeviceCount();

    int* matrixP2PCompatibility = new int[n * n];
    int* ptrMatrixP2PCompatibility = matrixP2PCompatibility;

    for (int i = 0; i < n; i++)
	{
	for (int j = 0; j < n; j++)
	    {
	    int isP2PAutorized01;
	    HANDLE_ERROR(cudaDeviceCanAccessPeer(&isP2PAutorized01, i, j));

	    *ptrMatrixP2PCompatibility++ = isP2PAutorized01;
	    }
	}

    return matrixP2PCompatibility;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void cout01(int isTrue)
    {
    if (isTrue)
	cout << "True" << endl;
    else
	cout << "False" << endl;
    }

void coutBool(bool isFlag)
    {
    if (isFlag)
	cout << "True" << endl;
    else
	cout << "False" << endl;
    }

string toString(Family family)
    {
    switch (family)
	{
	case FERMI:
	    return "FERMI";
	case KEPPLER:
	    return "KEPPLER";
	case MAXWELL:
	    return "MAXWELL";
	case UNKNOWN:
	    return "UNKNOWN";
	default:
	    return "UNKNOWN";
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

