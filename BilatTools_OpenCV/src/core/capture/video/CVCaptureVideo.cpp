#include "CVCaptureVideo.h"

#include <iostream>

#include "OpencvTools.h"
#include "StringTools.h"

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

CVCaptureVideo::CVCaptureVideo(string nameFile) :
	nameFile(nameFile)
    {
    this->started = false;
    this->fpsSource = -1;
    }

CVCaptureVideo::~CVCaptureVideo(void)
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
Mat CVCaptureVideo::provideBGR()
    {
    Mat matBGR;
    bool isOk = videoCapture.read(matBGR);

    bool isFinVideo = !isOk;

    if (isFinVideo)
	{
	videoCapture.set(CV_CAP_PROP_POS_FRAMES, 0); // remise du lecteur à la position 0
	videoCapture.read(matBGR);
	}

    return matBGR;
    }

///**
// * Override
// */
//uchar4* CVCaptureVideo::toRGBAuchar4(Mat& matBGR)
//    {
//    return OpencvTools::toRGBA_uchar4(matBGR);
//	uchar* perdu car matr detruite
//    }

/**
 * Override
 */
Mat CVCaptureVideo::BGRToRGBA(Mat& matBGR)
    {
    return OpencvTools::BGRToRGBA(matBGR);
    }

/*----------------*\
 |*  capture	  *|
 \*--------------*/

void CVCaptureVideo::captureRGBA(unsigned char* ptrPixels)
    {
    Mat matBGR = provideBGR();
    // v1 BGR
    //unsigned char* ptrPixelMatBGR = OpencvTools::castToUchar(matBGR); // attention : lecture utiliser le type  Mat matRGBA(h, w, CV_8UC3, ptrPixels); ou la fonction toMat cidessous

    // v2 RGB
    //Mat matRGBA(h, w, CV_8UC4); // attention : lecture utiliser le type  Mat matRGBA(h, w, CV_8UC4, ptrPixels);
   // OpencvTools::switchRB(matRGBA, matBGR); // dest, src

    //v2 bis
    Mat matRGBA=OpencvTools::BGRToRGBA(matBGR);
   unsigned char* ptrPixelRGBA = OpencvTools::castToUchar(matRGBA);



    // copie
	{
	size_t size = w * h * sizeof(unsigned char) * 4;
	memcpy(ptrPixels, ptrPixelRGBA, size); // TODO ameliorer: comment donner a opencv l'adresse ptrPixels?
	}
    }

Mat CVCaptureVideo::toMat(unsigned char* ptrPixels)
    {
    // BGR
    //Mat mat(h, w, CV_8UC3, ptrPixels);

    //RGBA
    Mat mat(h, w, CV_8UC4, ptrPixels);

    return mat;
    }

/*----------------*\
 |*  common	  *|
 \*--------------*/



/**
 * Override
 */
bool CVCaptureVideo::start()
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
	cerr << "[CVCaptureVideo] : start: Warning : video already started : " << nameFile << " : (w,h)=" << this->w << "," << this->h << ")" << endl;
	return false;
	}

    }

/**
 * Override
 */
void CVCaptureVideo::stop()
    {
    if (started)
	{
	videoCapture.release();
	started = false;
	}
    else
	{
	cerr << "[CVCaptureVideo] : stop : Warning : video not started : " << nameFile << endl;
	}
    }

/**
 * Override
 */
int CVCaptureVideo::getW()
    {
    return w;
    }

/**
 * Override
 */
int CVCaptureVideo::getH()
    {
    return h;
    }

/**
 * Override
 */

bool CVCaptureVideo::isStarted()
    {
    return started;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void CVCaptureVideo::info()
    {
    cout << "[CVCaptureVideo] : nameFile   = " << nameFile << endl;
    cout << "[CVCaptureVideo] : (w,h)      = (" << this->w << "," << this->h << ")" << endl;
    cout << "[CVCaptureVideo] : fps source = " << fpsSource << endl;

    Mat mat;
    this->videoCapture >> mat;

    cout << "[CVCaptureVideo] : #channel   = " << mat.channels() << endl;
    cout << "[CVCaptureVideo] : type       = " << mat.type() << " : " << OpencvTools::imageType(mat) << endl;
    }

int CVCaptureVideo::getFpsSource()
    {
    return this->fpsSource;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool CVCaptureVideo::open()
    {
    try
	{
	this->videoCapture = VideoCapture();
	this->videoCapture.open(nameFile);

	if (!videoCapture.isOpened())
	    {
	    cerr << "[CVCaptureVideo] : open : error : " << "can't open video " + nameFile << endl;
	    return false;
	    }
	else
	    {
	    this->w = this->videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	    this->h = this->videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
	    this->fpsSource = this->videoCapture.get(CV_CAP_PROP_FPS);

	    info();
	    return true;
	    }
	}
    catch (cv::Exception& e)
	{
	const char* err_msg = e.what();

	cerr << "[CVCaptureVideo] : open : error : nameFile=" << nameFile << " : " << err_msg << endl;

	return false;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
