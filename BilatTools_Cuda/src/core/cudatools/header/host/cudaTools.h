#pragma once


//#include "cuda.h"
#include "builtin_types.h"
#include "cuda_runtime.h"
#include "curand.h"

// cublas
#include "cublas_v2.h" 	// Pour specifier la version qu'on veut! (definition CUBLASAPI)
//#include "cublas.h"  	// Pour specifier la version qu'on veut!(definition CUBLASAPI)
#include "cublas_api.h" // Après include "cublas_v2.h" ou "cublas.h"


#ifndef uchar
   typedef unsigned char uchar;
#endif

#ifndef uint
   typedef unsigned int uint;
#endif

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

#define HANDLE_ERROR( error ) (cudaHandleError( error, __FILE__, __LINE__ ))

void cudaHandleError(cudaError_t error, const char *file, int line); //cuda
void cudaHandleError(curandStatus_t statut, const char *file, int line); // curand
void cudaHandleError(cublasStatus_t cublasStatus,const char *file, int line); // cublas


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

