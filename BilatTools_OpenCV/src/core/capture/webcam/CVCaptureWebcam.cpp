#include <stdlib.h>
#include <iostream>

#include "CVCaptureWebcam.h"
#include "OpencvTools.h"

using std::cout;
using std::endl;
using std::cerr;

using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

CVCaptureWebcam::CVCaptureWebcam(int wAsk, int hAsk, int deviceId) :
	deviceId(deviceId)
    {
    this->started = false;
    this->wAsk = wAsk;
    this->hAsk = hAsk;
    }

CVCaptureWebcam::~CVCaptureWebcam(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/*----------------*\
 |*  provide	  *|
 \*--------------*/

/**
 * Override
 */
Mat CVCaptureWebcam::provideBGR()
    {
    Mat matBGR;
    this->videocapture >> matBGR;

    return matBGR;
    }

///**
// * Override
// */
//uchar4* CVCaptureWebcam::toRGBAuchar4(Mat& matBGR)
//    {
//    return OpencvTools::toRGBA_uchar4(matBGR);
//	uchar* perdu car matr detruite
//    }

/**
 * Override
 */
Mat CVCaptureWebcam::BGRToRGBA(Mat& matBGR)
    {
    return OpencvTools::BGRToRGBA(matBGR);
    }

/*----------------*\
 |*  capture	  *|
 \*--------------*/

/**
 * Override
 *
 * output : RGBA
 *
 * Alternative : use provideBGR and OpencvTools to perform convertion of type, quicker?
 */
void CVCaptureWebcam::captureRGBA(unsigned char* ptrPixels)
    {
    Mat matBGR = provideBGR();
    // v1 BGR
    //unsigned char* ptrPixelMatBGR = OpencvTools::castToUchar(matBGR); // attention : lecture utiliser le type  Mat matRGBA(h, w, CV_8UC3, ptrPixels); ou la fonction toMat cidessous

    // v2 RGB
    // Mat matRGBA(h, w, CV_8UC4); // attention : lecture utiliser le type  Mat matRGBA(h, w, CV_8UC4, ptrPixels);
    // OpencvTools::switchRB(matRGBA, matBGR); // dest, src

    // v2 bis
    Mat matRGBA = OpencvTools::BGRToRGBA(matBGR);
    unsigned char* ptrPixelRGBA = OpencvTools::castToUchar(matRGBA);

    // copie
	{
	size_t size = w * h * sizeof(unsigned char) * 4;
	memcpy(ptrPixels, ptrPixelRGBA, size); // TODO ameliorer: comment donner a opencv l'adresse ptrPixels?
	}
    }

Mat CVCaptureWebcam::toMat(unsigned char* ptrPixels)
    {
    // BGR
    //Mat mat(h, w, CV_8UC3, ptrPixels);

    //RGBA
    Mat mat(h, w, CV_8UC4, ptrPixels);

    return mat;
    }

//// KO
//void CVCaptureWebcam::provideBGR(Mat& mat)
//    {
//    cout<<"provideBGR avant="<<(void*)(mat.data)<<endl; //
//    this->videocapture >> mat;
//    cout<<"provideBGR apres="<<(void*)mat.data<<endl; // differenet
//    }

/*----------------*\
 |*  common	  *|
 \*--------------*/

/**
 * Override
 */
bool CVCaptureWebcam::start()
    {
    if (!started)
	{
	bool isOk = open();
	if (isOk)
	    {
	    started = true;
	    }
	else
	    {
	    started = false;
	    }
	return isOk;
	}
    else
	{
	cerr << "[CVCaptureWebcam] : start: Warning : Device already started : " << deviceId << " : (w,h)=(" << this->w << "," << this->h << ")" << endl;
	return false;
	}
    }

/**
 * Override
 */
void CVCaptureWebcam::stop()
    {
    if (started)
	{
	videocapture.release();
	started = false;
	}
    else
	{
	cerr << "[CVCaptureWebcam] : stop : Warning : Device not started : " << deviceId << endl;
	}
    }

/*--------------*\
 |* get/set	*|
 \*------------*/

/**
 * Override
 */
int CVCaptureWebcam::getW()
    {
    return w;
    }

/**
 * Override
 */
int CVCaptureWebcam::getH()
    {
    return h;
    }

/**
 * Override
 */
int CVCaptureWebcam::getDeviceId()
    {
    return deviceId;
    }

/**
 * Override
 */
bool CVCaptureWebcam::isStarted()
    {
    return started;
    }

/*--------------------------------------*\
 |*		public			*|
 \*-------------------------------------*/

void CVCaptureWebcam::info()
    {
    cout << "[CVCaptureWebcam] : deviceId = " << deviceId << endl;
    cout << "[CVCaptureWebcam] : (w,h)    = (" << this->w << "," << this->h << ")" << endl;

    Mat mat;
    this->videocapture >> mat;

    cout << "[CVCaptureWebcam] : #channel  = " << mat.channels() << endl;
    cout << "[CVCaptureWebcam] : type      = " << mat.type() << " : " << OpencvTools::imageType(mat) << endl;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool CVCaptureWebcam::open()
    {
    try
	{
	this->videocapture = VideoCapture();
	this->videocapture.open(deviceId);

	if (!videocapture.isOpened())
	    {
	    cerr << "[CVCaptureWebcam] : open : error:  : Warning : cannot open device: " << deviceId << endl;
	    return false;
	    }
	else
	    {
	    configure();
	    return true;
	    }
	}
    catch (cv::Exception& e)
	{
	const char* err_msg = e.what();

	cerr << "[CVCaptureWebcam] : open : error: device = " << deviceId << " : " << err_msg << endl;

	return false;
	}
    }

/**
 * use wAsk hAsk ifg !=-1
 */
void CVCaptureWebcam::configure()
    {
    if (wAsk != -1)
	{
	this->videocapture.set(CV_CAP_PROP_FRAME_WIDTH, wAsk);
	}

    if (hAsk != -1)
	{
	this->videocapture.set(CV_CAP_PROP_FRAME_HEIGHT, hAsk);
	}

    this->w = this->videocapture.get(CV_CAP_PROP_FRAME_WIDTH);
    this->h = this->videocapture.get(CV_CAP_PROP_FRAME_HEIGHT);

    info();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
