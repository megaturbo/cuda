#pragma once

#include <opencv.hpp>
#include <highgui.hpp>

#include "CaptureMat_I.h"

using cv::Mat;
using cv::VideoCapture;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class CVCaptureWebcam: public CaptureMat_I
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * wAsk not necessary respect
	 * hAsk not necessary respect
	 */
	CVCaptureWebcam(int wAsk = 720, int hAsk = 540, int deviceId = 0);
	virtual ~CVCaptureWebcam(void);

	/*--------------------------------------*\
	 |*		Override		*|
	 \*-------------------------------------*/

    public:

	/*----------------*\
	 |*  provide	  *|
	 \*--------------*/

	/**
	 * Attention:
	 *
	 *      OpenCV travaille en BGR!
	 *
	 * Tip:
	 *
	 * 	Utiliser la classe OpencvTools pour des convertions de type!
	 *
	 * Exemple Cuda:
	 *
	 * 	CVCaptureWebcam capture(1280,1024);
	 * 	bool isOk=capture.start();
	 * 	if (!isOk){exit(EXIT_FAILURE);}
	 *
	 * 	Mat matRGBA(h,w,CV_8UC1);
	 * 	bool isFini=false;
	 * 	while(!isFini)
	 * 		{
	 * 		Mat matBGR=capture.provideBGR();
	 * 		OpencvTools::switchRB(matRGBA,matBGR ); // la convertion BGR to RGB (croisement R <--> B) pourrait se faire avantageusement sur le GPU!
	 * 		uchar4 ptrImage=OpencvTools::castToUchar4(matRGBA);
	 * 		...
	 * 		}
	 * 	capture.stop();
	 */
	virtual Mat provideBGR();

	/**
	 * Override
	 */
	virtual Mat BGRToRGBA(Mat& matBGR);

	/*----------------*\
	 |*  capture	  *|
	 \*--------------*/

	/**
	 * override, use if necessary toMat ci-dessous
	 */
	virtual void captureRGBA(unsigned char* ptrPixels);

	/**
	 * a utiliser after capture
	 */
	Mat toMat(unsigned char* ptrPixels);

	/*----------------*\
	 |*  common	  *|
	 \*--------------*/



	/**
	 * override
	 */
	virtual int getW();

	/**
	 * override
	 */
	virtual int getH();

	/**
	 * override
	 */
	virtual int getDeviceId();

	/**
	 * override
	 */
	virtual bool start();

	/**
	 * override
	 */
	virtual void stop();

	/**
	 * override
	 */
	bool isStarted();

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void info();

    private:

	bool open();
	void configure();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int deviceId;
	int wAsk;
	int hAsk;

	// Output
	int w;
	int h;

	// Tools
	VideoCapture videocapture;

	bool started;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
