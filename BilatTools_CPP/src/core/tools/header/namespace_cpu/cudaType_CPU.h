#ifndef CUDA_TYPE_CPU_H_
#define CUDA_TYPE_CPU_H_


//pragma once marche pas ici!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

// Attention 	: code duplicated : aussi dans shared_lib api image
// Contrainte 	: Les deux versions doivent etre identique

//Define outsite namespace cpu due to conflict with OpenCV defines and using namespace cpu;

//coloration synthaxique ok
#ifndef uchar
typedef unsigned char uchar;
#endif

#ifndef uint
typedef unsigned int uint;
#endif

#ifndef ulong
typedef unsigned long ulong;
#endif


namespace cpu
    {
    struct float2
	{
	float x;
	float y;
	};

    struct float3
	{
	    float x;
	    float y;
	    float z;
	};

    struct float4
	{
	    float x;
	    float y;
	    float z;
	    float w;
	};

    struct uchar3
	{
	    unsigned char x;
	    unsigned char y;
	    unsigned char z;
	};

    struct uchar4
	{
	    unsigned char x;
	    unsigned char y;
	    unsigned char z;
	    unsigned char w;
	};

    /*----------------------------------------------------------------------*\
     |*			Procedures 					    *|
     \*---------------------------------------------------------------------*/

    static uchar4 make_uchar4( unsigned char x=0, unsigned char y=0, unsigned char z=0, unsigned char w=0)
	{
	uchar4 pixel;
	pixel.x=x;
	pixel.y=y;
	pixel.z=z;
	pixel.w=w;
	return pixel;
	}

    static uchar3 make_uchar3( unsigned char x=0, unsigned char y=0, unsigned char z=0)
	{
	uchar3 pixel;
	pixel.x=x;
	pixel.y=y;
	pixel.z=z;
	return pixel;
	}

    static float4 make_float4( float x=0, float y=0, float z=0, float w=0)
	{
	float4 pixel;
	pixel.x=x;
	pixel.y=y;
	pixel.z=z;
	pixel.w=w;
	return pixel;
	}

    static float3 make_float3( float x=0, float y=0, float z=0)
	{
	float3 pixel;
	pixel.x=x;
	pixel.y=y;
	pixel.z=z;
	return pixel;
	}

    static float2 make_float2( float x=0, float y=0)
	{
	float2 pixel;
	pixel.x=x;
	pixel.y=y;
	return pixel;
	}
    }

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
