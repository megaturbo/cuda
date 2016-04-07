#pragma once

#include <iostream>

#include "StringTools.h"
#include "ColorRGB_01.h"

#include "Image_GPU.h"
#include "Animable_I_GPU.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    template<typename T, ColorModel ColorModel, int PixelFormat>
    class ImageAnimable: public Image_A<T, ColorModel, PixelFormat, DomaineMath>
	{
	    /*--------------------------------------*\
	|*		Constructeur		*|
	     \*-------------------------------------*/

	public:

	    ImageAnimable(Animable_I<T>* ptrAnimable, ColorRGB_01 colorTitreRGB = ColorRGB_01(1.0f, 0.0f, 0.0f)) :
		    Image_A<T, ColorModel, PixelFormat, DomaineMath>(ptrAnimable->getW(), ptrAnimable->getH(), ptrAnimable->getDomaineMathInit()), ptrAnimable(
			    ptrAnimable), colorTitreRGB(colorTitreRGB)
		{
	    	// rien
		}

	    virtual ~ImageAnimable(void)
		{
		delete ptrAnimable; // TODO discutable, not that problem with shared_ptr
		}

	    /*--------------------------------------*\
	|*		Methode			*|
	     \*-------------------------------------*/

	public:

	    Animable_I<T>* getAnimable()
		{
		return ptrAnimable;
		}

	    /*----------------*\
	    |*  Override	*|
	     \*---------------*/

	    /**
	     * Override, call periodicly by the api
	     */
	    virtual void fillImage(T* ptrPixel, int w, int h, const DomaineMath& domaineMath)
		{
		ptrAnimable->process(ptrPixel, w, h, domaineMath);
		}

	    /**
	     * Override, call periodicly by the api
	     */
	    virtual void animationStep(bool& isNeedUpdateView)
		{
		ptrAnimable->animationStep();
		isNeedUpdateView = true;
		}

	    /**
	     * Override, call periodicly by the api
	     */
	    virtual void paintPrimitives(Graphic2D& graphic2D)
		{
		graphic2D.setFont(TIMES_ROMAN_24);

		float r = colorTitreRGB.r;
		float g = colorTitreRGB.g;
		float b = colorTitreRGB.b;

		graphic2D.setColorRGB(r, g, b);

		// Top : Para Animation
		    {
		    float t = ptrAnimable->getAnimationPara();

		    string message = "t = " + StringTools::toString(t);

		    graphic2D.drawTitleTop(message);
		    }

		// Bottom : Title
		    {
		    string title = ptrAnimable->getTitle();

		    graphic2D.drawTitleBottom(title);
		    }
		}

	    /*--------------------------------------*\
	|*		Attribut		*|
	     \*-------------------------------------*/

	private:

	    // Inputs
	    Animable_I<T>* ptrAnimable;
	    ColorRGB_01 colorTitreRGB;

	};

    typedef ImageAnimable<uchar4, RGBA, GL_UNSIGNED_BYTE> ImageAnimable_RGBA_uchar4;
    typedef ImageAnimable<uchar3, RGB, GL_UNSIGNED_BYTE> ImageAnimable_RGB_uchar3;
    typedef ImageAnimable<uchar, GRAY, GL_UNSIGNED_BYTE> ImageAnimable_GRAY_uchar;

    typedef ImageAnimable<uchar4, HSBA, GL_UNSIGNED_BYTE> ImageAnimable_HSBA_uchar4;
    typedef ImageAnimable<uchar3, HSB, GL_UNSIGNED_BYTE> ImageAnimable_HSB_uchar3;
    typedef ImageAnimable<unsigned char, HUE, GL_UNSIGNED_BYTE> ImageAnimable_HUE_uchar;

    typedef ImageAnimable<float4, RGBA, GL_FLOAT> ImageAnimable_RGBA_float4;
    typedef ImageAnimable<float3, RGB, GL_FLOAT> ImageAnimable_RGB_float3;
    typedef ImageAnimable<float, GRAY, GL_FLOAT> ImageAnimable_GRAY_float;

    typedef ImageAnimable<float4, HSBA, GL_FLOAT> ImageAnimable_HSBA_float4;
    typedef ImageAnimable<float3, HSB, GL_FLOAT> ImageAnimable_HSB_float3;
    typedef ImageAnimable<float, HUE, GL_FLOAT> ImageAnimable_HUE_float;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
