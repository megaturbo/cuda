#pragma once

#include "both_define.h"
#include "builtin_types.h" // pour float3, float4, uchar4, ...

// TODO cuda ameliorer

namespace gpu
    {

    /**
     *   hsb(*,*,0) donne noir
     *   hsb(*,0,1) donne blanc
     */
    class ColorTools
	{
	    /*--------------------------------------*\
	   |*		  HSB_TO_RVB     	*|
	     \*-------------------------------------*/

	    /*--------------------------------------*\
	   |*		public			    *|
	     \*-------------------------------------*/

	public:

	    /*-----------------*\
	    |*	  uchar4	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGBA !
	     * H,S,B,A 	in [0,1]
	     * R,G,B,A 	in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(const float4& hsb01, uchar4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(hsb01.x, hsb01.y, hsb01.z, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = hsb01.w * 255;
		}

	    /**
	     * Convertir une couleur HSB en RGBA !
	     * H,S,B,A 	in [0,1]
	     * R,G,B,A 	in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(const float3& hsb01, uchar4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(hsb01.x, hsb01.y, hsb01.z, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = 255;  //opaque;
		}

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float h01, uchar4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(h01, 1.0f, 1.0f, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = 255;  //opaque;
		}

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float H, float S, float V, uchar4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(H, S, V, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = 255; //opaque;
		}

	    /*-----------------*\
	    |*	  uchar3	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(const float3& hsb01, uchar3* ptrRVB)
		{
		ColorTools::HSB_TO_RVB(hsb01.x, hsb01.y, hsb01.z, &ptrRVB->x, &ptrRVB->y, &ptrRVB->z);
		}

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float h01, uchar3* ptrRVB)
		{
		ColorTools::HSB_TO_RVB(h01, 1.0f, 1.0f, &ptrRVB->x, &ptrRVB->y, &ptrRVB->z);
		}

	    /*-----------------*\
	     |*	 Unsigned char *|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B in [0,255]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float H, float S, float V, unsigned char *ptrR, unsigned char *ptrG, unsigned char *ptrB)
		{
		//float H = profondeur / 255.0;
		//float S = 1;
		//float V = 1;
		if (S == 0) //HSV from 0 to 1
		    {
		    *ptrR = V * 255;
		    *ptrG = V * 255;
		    *ptrB = V * 255;
		    }
		else
		    {
		    float var_h = H * 6;
		    if (var_h == 6)
			{
			var_h = 0;
			} //H must be < 1

		    unsigned char var_i = (unsigned char) var_h; //Or ... var_i = floor( var_h )

		    float var_1 = V * (1 - S);
		    float var_2 = V * (1 - S * (var_h - var_i));
		    float var_3 = V * (1 - S * (1 - (var_h - var_i)));

		    float var_r, var_g, var_b;
		    if (var_i == 0)
			{
			var_r = V;
			var_g = var_3;
			var_b = var_1;
			}
		    else if (var_i == 1)
			{
			var_r = var_2;
			var_g = V;
			var_b = var_1;
			}
		    else if (var_i == 2)
			{
			var_r = var_1;
			var_g = V;
			var_b = var_3;
			}
		    else if (var_i == 3)
			{
			var_r = var_1;
			var_g = var_2;
			var_b = V;
			}
		    else if (var_i == 4)
			{
			var_r = var_3;
			var_g = var_1;
			var_b = V;
			}
		    else
			{
			var_r = V;
			var_g = var_1;
			var_b = var_2;
			}

		    //RGB results from 0 to 255
		    *ptrR = (unsigned char) (var_r * 255);
		    *ptrG = (unsigned char) (var_g * 255);
		    *ptrB = (unsigned char) (var_b * 255);
		    }
		}

	    /*-----------------*\
	    |*	  float4	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B,A in [0,1]
	     * R,G,B,A in [0,1]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(const float4& hsba01, float4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(hsba01.x, hsba01.y, hsba01.z, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = hsba01.w;
		}

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B,A in [0,1]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(const float3& hsb01, float4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(hsb01.x, hsb01.y, hsb01.z, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = 1.0f; // opaque
		}

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H in [0,1]
	     * R,G,B in [0,1]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float h01, float4* ptrRVBA)
		{
		ColorTools::HSB_TO_RVB(h01, 1.0f, 1.0f, &ptrRVBA->x, &ptrRVBA->y, &ptrRVBA->z);
		ptrRVBA->w = 1.0f; // opaque
		}

	    /*-----------------*\
	    |*	  float3	*|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H,S,B in [0,1]
	     * R,G,B in [0,1]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(const float3& hsb01, float3* ptrRVB)
		{
		ColorTools::HSB_TO_RVB(hsb01.x, hsb01.y, hsb01.z, &ptrRVB->x, &ptrRVB->y, &ptrRVB->z);
		}

	    /**
	     * Convertir une couleur HSB en RGB !
	     * H in [0,1]
	     * R,G,B in [0,1]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float h01, float3* ptrRVB)
		{
		ColorTools::HSB_TO_RVB(h01, 1.0f, 1.0f, &ptrRVB->x, &ptrRVB->y, &ptrRVB->z);
		}

	    /*-----------------*\
	    |*	  float	       *|
	     \*----------------*/

	    /**
	     * Convertir une couleur HSB en RGB en float!
	     * H,S,B in [0,1]
	     * R,G,B in [0,1]
	     */
	    __BOTH__
	    static void HSB_TO_RVB(float H, float S, float V, float *ptrR, float *ptrG, float *ptrB)
		{
		//float H = profondeur / 255.0;
		//float S = 1;
		//float V = 1;
		if (S == 0) //HSV from 0 to 1
		    {
		    *ptrR = V;
		    *ptrG = V;
		    *ptrB = V;
		    }
		else
		    {
		    float var_h = H * 6;
		    if (var_h == 6)
			{
			var_h = 0;
			} //H must be < 1

		    unsigned char var_i = (unsigned char) var_h; //Or ... var_i = floor( var_h )

		    float var_1 = V * (1 - S);
		    float var_2 = V * (1 - S * (var_h - var_i));
		    float var_3 = V * (1 - S * (1 - (var_h - var_i)));

		    float var_r, var_g, var_b;
		    if (var_i == 0)
			{
			var_r = V;
			var_g = var_3;
			var_b = var_1;
			}
		    else if (var_i == 1)
			{
			var_r = var_2;
			var_g = V;
			var_b = var_1;
			}
		    else if (var_i == 2)
			{
			var_r = var_1;
			var_g = V;
			var_b = var_3;
			}
		    else if (var_i == 3)
			{
			var_r = var_1;
			var_g = var_2;
			var_b = V;
			}
		    else if (var_i == 4)
			{
			var_r = var_3;
			var_g = var_1;
			var_b = V;
			}
		    else
			{
			var_r = V;
			var_g = var_1;
			var_b = var_2;
			}

		    //RGB results from 0 to 1
		    *ptrR = var_r;
		    *ptrG = var_g;
		    *ptrB = var_b;
		    }
		}

	    /*--------------------------------------*\
	    |*		private			    *|
	     \*-------------------------------------*/

	};
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
