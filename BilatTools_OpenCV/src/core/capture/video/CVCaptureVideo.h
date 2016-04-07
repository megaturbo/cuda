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

class CVCaptureVideo: public CaptureMat_I
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	CVCaptureVideo(string nameFile);
	virtual ~CVCaptureVideo(void);

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
	 * 	CVCaptureVideo capture(1280,1024);
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

	virtual void captureRGBA(unsigned char* ptrPixels);

	Mat toMat(unsigned char* ptrPixels);

	/*----------------*\
	 |*  common	  *|
	 \*--------------*/

	/**
	 * Override
	 */
	virtual int getW();

	/**
	 * Override
	 */
	virtual int getH();

	/**
	 * Override
	 */
	virtual bool start();

	/**
	 * Override
	 */
	virtual void stop();

	/**
	 * Override
	 */
	virtual bool isStarted();

    public:

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

	void info();

	int getFpsSource();

    private:

	bool open();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	string nameFile;

	// output
	int w;
	int h;
	int fpsSource;

	// Tools
	VideoCapture videoCapture;
	bool started;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
