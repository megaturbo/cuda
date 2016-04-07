#pragma once

#include <opencv.hpp>
#include <string>

using std::string;
using cv::Mat;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 *  Attention:
 * 		 Opencv travaille en BGR.
 * 		 Par rapport a RGBA,le R et B sont croiser
 *
 * Convertin possible:
 *
 *		 http://siggiorn.com/wp-content/uploads/libraries/opencv-java/docs/sj/opencv/Constants.ColorConversion.html
 */
class OpencvTools
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	OpencvTools();

	virtual ~OpencvTools();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	static string imageType(Mat& mat);
	static string imageType(int imageType);

	/*------------------------*\
	 |*	io                 *|
	 \*-----------------------*/

	static Mat loadBGR(string fileName);

	/**
	 * return true if quit ask
	 *
	 * Note : jetson need at least delayMS=10 to run correctly
	 */
	static bool showBGR(Mat& matBGR, string idFrameAndTitle, long delayMS = 10);

	static void destroyFrame(string idFrameAndTitle);

	static void write(string fileName, Mat& mat);

	/*------------------------*\
	 |*	Convertion Type    *|
	 \*-----------------------*/

	/*-------------*\
	|* Mat-->Mat   *|
	 \*--------------*/

	static Mat BGRToRGBA(Mat& matBGR);

	/**
	 * switch R<-->B
	 *
	 * input  : 3 or 4 channel RGB ou BGR
	 * output : 4 channels RGBA ou BGRA
	 */
	static void switchRB(Mat& dest4, Mat& src4);

	/**
	 * input : 4 channel RGBA OU BGRA
	 * ouput : 4 channel identique
	 */
	static void toGRAY(Mat& destGray, Mat& src4);

	/*-------------*\
	|* uchar-->Mat   *|
	 \*--------------*/

	/**
	 * switch R<-->B
	 *
	 * input  :  4 uchar par pixel : RGBA ou BGRA
	 * output :  4 channle RGBA ou BGRA
	 */
	static Mat switchRB(unsigned char* ptrPixel, int w, int h);

	/**
	 * input :  4 uchar par pixel : RGBA OU BGRA
	 * ouput :  4 channel identique
	 */
	static Mat toGRAY(unsigned char* ptrPixel, int w, int h);

	/*-------------*\
	|* cast       *|
	 \*--------------*/

	static uchar* castToUchar(Mat& mat);

	/**
	 * Cuda :
	 *
	 * 	//V1
	 * 		uchar4* ptr=(uchar4*)castToVoid(mat);
	 *
	 * 	or simplier:
	 *
	 * 		#include "OpencvTools_GPU.h"
	 * 		uchar4* ptr=OpencvTools_GPU.castToUchar4(mat);
	 * NoCuda:
	 *
	 * 	//v1
	 * 		#include "cudaType_CPU.h"
	 * 		cpu::uchar4* ptr=(uchar4*)castToVoid(mat);
	 * 	//v2
	 * 		#include "cudaType_CPU.h"
	 * 		using cpu::uchar4;
	 * 		uchar4* ptr=(uchar4*)castToVoid(mat);
	 * 	//v3
	 * 		#include "cudaType_CPU.h"
	 * 		using namespace cpu;
	 * 		uchar4* ptr=(uchar4*)castToVoid(mat);
	 *
	 * 	or simplier
	 *
	 * 		#include "OpencvTools_CPU.h"
	 * 		uchar4* ptr=OpencvTools_CPU.castToUchar4(mat);
	 *  Note:
	 *
	 *  	OpencvTools_CPU extends OpencvTools
	 *  	OpencvTools_GPU extends OpencvTools
	 */
	static void* castToVoid(Mat& mat);

	/**
	 * see
	 * 	GPU:	OpencvTools_GPU
	 * or
	 * 	CPU	OpencvTools_CPU
	 * cause:
	 * 	type uchar4 not know here
	 */
	//static uchar4* castToUchar4(Mat& mat);


	/*-------------*\
	|* special       *|
	 \*--------------*/

	static Mat fromUchar3ToDouble(Mat& mat);

	static Mat fromDoubleToUchar(Mat& mat);

    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
