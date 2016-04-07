#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

// TODO rename Indice2D -> Grid2D
class Indice2D
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*------------------*\
	|*	tid Global   *|
	 \*-----------------*/

	/**
	 * Best performance with entrelacement pattern! Minimize memory transaction!
	 * Warning: If 2d is not required, use grid1D cause process tid required less aritmetical operation
	 *
	 *  ----------------------------------
	 *  | 0  1  2 |  6  7  8 | 12 13 14 |
	 *  | 3  4  5 |  9 10 11 | 15 16 17 |
	 *  ----------------------------------
	 *  | 18 19 20 | 24 25 26 | 30 31 32 |
	 *  | 21 22 23 | 27 28 29 | 33 34 35 |
	 *  ----------------------------------
	 */
	__device__
	static int tid()
	    {
	    return (blockDim.x * blockDim.y) * ((gridDim.x * blockIdx.y) + blockIdx.x) + (blockDim.x * threadIdx.y) + threadIdx.x;
	    // Note (blockDimk.x*threadIdx.y)+threadIdx.x = tidLocal
	    }

	/**
	 * tidRawMajor : Usefull for tiling gm to sm !
	 *
	 *  ----------------------------------
	 *  | 0  1  2 |  3  4  5 |  6  7  8 |
	 *  | 9 10 11 | 12 13 14 | 15 16 17 |
	 *  ----------------------------------
	 *  | 18 19 20 | 21 22 23 | 24 25 26 |
	 *  | 27 28 29 | 30 31 32 | 33 34 35 |
	 *  ----------------------------------
	 */
	__device__
	static int tidRawMajor()
	    {
	    // idem tidColMajor x<-->y
	    return (threadIdx.x + (blockDim.x * blockIdx.x)) + ((threadIdx.y + (blockDim.y * blockIdx.y)) * (gridDim.x * blockDim.x));
	    }

	/**
	 *  tidColMajor : Usefull for tiling sm to gm ! (transpose algo)
	 *
	 *  ----------------------------------
	 *  | 0  4  8 | 12 16 20 | 24 28 32 |
	 *  | 1  5  9 | 13 17 21 | 25 29 33 |
	 *  ----------------------------------
	 *  | 2  6 10 | 14 18 22 | 26 30 34 |
	 *  | 3  7 11 | 15 19 23 | 27 31 35 |
	 *  ----------------------------------
	 */
	__device__
	static int tidColMajor()
	    {
	    // idem tidRawMajor x<-->y
	    return threadIdx.y + (blockDim.y * blockIdx.y) + ((threadIdx.x + (blockDim.x * blockIdx.x)) * (gridDim.y * blockDim.y));
	    }

	/*------------------*\
	|*	tid Local   *|
	 \*-----------------*/

	/**
	 * output in [0,nbThreadBlock()[
	 * return threadIdx.x+blockDim.x*threadIdx.y;
	 */
	__device__
	static int tidLocalBlock()
	    {
	    return threadIdx.x + blockDim.x * threadIdx.y;
	    }

	/**
	 * idem tidLocalBlock
	 */
	__device__
	static int tidBlock()
	    {
	    return threadIdx.x + blockDim.x * threadIdx.y;
	    }

	/**
	 * idem tidLocalBlock
	 */
	__device__
	static int tidLocal()
	    {
	    return threadIdx.x + blockDim.x * threadIdx.y;
	    }

	/*------------------*\
	|*	nbThread    *|
	 \*-------------------*/

	__device__
	static int nbThread()
	    {
	    return (gridDim.x * gridDim.y) * (blockDim.x * blockDim.y);
	    }

	__device__
	static int nbThreadX()
	    {
	    return gridDim.x * blockDim.x;
	    }

	__device__
	static int nbThreadY()
	    {
	    return gridDim.y * blockDim.y;
	    }

	/**
	 * idem nbThreadLocal
	 */
	__device__
	static int nbThreadBlock()
	    {
	    return blockDim.x * blockDim.y;
	    }

	/**
	 * idem nbThreadBlock
	 */
	__device__
	static int nbThreadLocal()
	    {
	    return blockDim.x * blockDim.y;
	    }

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
