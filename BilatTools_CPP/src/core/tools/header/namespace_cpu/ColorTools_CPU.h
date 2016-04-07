#pragma once

#include "cudaType_CPU.h"

/**
 * The two methode HSB_TO_RGB and RGB_TO_HSB are from http://www.easyrgb.com/index.php?X=MATH&H=21#text21
 */
namespace cpu
    {
    class ColorTools
	{
	public:

	    /*--------------------------------------*\
	   |*		  HSB_TO_RVB     		*|
	     \*-------------------------------------*/

	    /*-----------------*\
	    |*	  uchar4	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGBA !
	     * H,S,B,A 	in [0,1]
	     * R,G,B,A 	in [0,255]
	     */
	    static void HSB_TO_RVB(const float4& hsba01, uchar4* ptrRVBA);

	    /**
	     * Convertir une couleur HSB en RGBA !
	     * H,S,B,A 	in [0,1]
	     * R,G,B,A 	in [0,255]
	     */
	    static void HSB_TO_RVB(const float3& hsb01, uchar4* ptrRVBA);

	    /**
	     * Convertir une couleur HSB en RGBA !
	     * H,S,B,A 	in [0,1]
	     * R,G,B,A 	in [0,255]
	     */
	    static void HSB_TO_RVB(float h01, uchar4* ptrRVBA);

	    /**
	     * Convertir une couleur HSB en RGBA !
	     * H,S,B,A 	in [0,1]
	     * R,G,B,A 	in [0,255]
	     */
	    static void HSB_TO_RVB(float H, float S, float V, uchar4* ptrRVB);

	    /*-----------------*\
	    |*	  uchar3	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B 	in [0,1]
	     * R,G,B 	in [0,255]
	     */
	    static void HSB_TO_RVB(const float3& hsb01, uchar3* ptrRVB);

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B 	in [0,1]
	     * R,G,B 	in [0,255]
	     */
	    static void HSB_TO_RVB(float h01, uchar3* ptrRVB);

	    /*-----------------*\
	     |*	  uchar	       *|
	     \*----------------*/

	    /**
	     * Conversion HSB => RVB
	     * Inputs :
	     * 	H,S,B in [0,1]
	     * Outputs :
	     * 	R,V,B in [0,255]
	     */
	    static void HSB_TO_RVB(const float H, const float S, const float V, unsigned char *ptrR, unsigned char *ptrG, unsigned char *ptrB);

	    /*-----------------*\
	    |*	  float4	*|
	     \*----------------*/
	    /**
	     * Convertir une couleur HSB en RVBA !
	     * H,S,B,A 	in [0,1]
	     * R,V,B,A 	in [0,1]
	     */
	    static void HSB_TO_RVB(const float4& hsba01, float4* ptrRVBA);

	    /**
	     * Convertir une couleur HSB en RVBA !
	     * H,S,B,A 	in [0,1]
	     * R,V,B,A 	in [0,1]
	     */
	    static void HSB_TO_RVB(const float3& hsb01, float4* ptrRVBA);

	    /**
	     * Convertir une couleur HSB en RVBA !
	     * H,S,B,A 	in [0,1]
	     * R,V,B,A 	in [0,1]
	     */
	    static void HSB_TO_RVB(float h01, float4* ptrRVBA);

	    /*-----------------*\
	    |*	  float3	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RVB !
	     * H,S,B,A 	in [0,1]
	     * R,V,B,A 	in [0,1]
	     */
	    static void HSB_TO_RVB(const float3& hsb01, float3* ptrRVB);

	    /**
	     * Convertir une couleur HSB en RVB !
	     * H,S,B,A 	in [0,1]
	     * R,V,B,A 	in [0,1]
	     */
	    static void HSB_TO_RVB(float h01, float3* ptrRVB);

	    /*-----------------*\
	    |*	  float	       *|
	     \*----------------*/

	    /**
	     * Conversion HSB => RVB
	     * Inputs :
	     * 	H,S,B in [0,1]
	     * Outputs :
	     * 	R,V,B in [0,1]
	     */
	    static void HSB_TO_RVB(const float H, const float S, const float V, float *ptrR, float *ptrG, float *ptrB);

	    /*--------------------------------------*\
	   |*		 RGB_TO_HSV  		*|
	     \*-------------------------------------*/

	    /**
	     * Conversion RGB => HSB
	     * Inputs :
	     * 	R,G,B in [0,255]
	     * Outpus :
	     * 	H,S,B in [0,1]
	     */
	    static void RGB_TO_HSB(const unsigned char R, const unsigned char G, const unsigned char B, float &H, float &S, float &V);

	    /*--------------------------------------*\
	  |*		 int 			   *|
	     \*-------------------------------------*/

	    /**
	     * Conversion HSB => RGBA + toIntRGBA
	     * Inputs :
	     * 	h01,b01,b01 in [0,1]
	     * Outpus :
	     * 	intRGBA cod� sur 32 bits, chaque composante (a,r,g,b) �tant cod�e sur 4 bits
	     * 	intRGBA cod�e :  0xAARRGGBB
	     */
	    static int HSB_TO_IntRGBA(float h01, float s01, float b01, float a01 = 0);

	    /**
	     * Conversion (r,g,b,a) => intRGBA
	     * Inputs :
	     * 	r,g,b,a in [0,255]
	     * Outputs :
	     * 	intRGBA cod� sur 32 bits, chaque composante (a,r,g,b) �tant cod�e sur 4 bits
	     * 	intRGBA cod�e :  0xAARRGGBB
	     */
	    static int toIntRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0);

	    /**
	     * see toIntRGBA(unsigned char r,  unsigned char g,  unsigned char b,  unsigned char a = 0)
	     */
	    static int toIntRGBA(float r01, float g01, float b01, float a01 = 0);

	    /**
	     * Inputs :
	     * 	intRGBA cod� sur 32 bits, chaque composante (a,r,g,b) �tant cod�e sur 4 bits
	     * 	intRGBA cod�e :  0xAARRGGBB
	     * Outputs :
	     * 	r,g,b,a in [0,255]
	     */
	    static void fromIntRGBA(const int rgb, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a);

	};
    }

