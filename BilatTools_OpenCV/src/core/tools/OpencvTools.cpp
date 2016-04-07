#include <iostream>
#include <stdlib.h>
#include "OpencvTools.h"

using std::cout;
using std::cerr;
using std::endl;

using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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
 |*		Constructor		*|
 \*-------------------------------------*/

OpencvTools::OpencvTools()
    {
    // nothing
    }

OpencvTools::~OpencvTools()
    {
    // nothing
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

string OpencvTools::imageType(Mat& mat)
    {
    return imageType(mat.type());
    }

/**
 * http://stackoverflow.com/questions/12335663/getting-enum-names-e-g-cv-32fc1-of-opencv-image-types
 *
 * http://siggiorn.com/wp-content/uploads/libraries/opencv-java/docs/sj/opencv/Constants.ColorConversion.html
 */
string OpencvTools::imageType(int imageType)
    {
    int numImgTypes = 35; // 7 base types, with five channel options each (none or C1, ..., C4)

    int enum_ints[] =
		{
		CV_8U, CV_8UC1, CV_8UC2, CV_8UC3, CV_8UC4, CV_8S, CV_8SC1, CV_8SC2, CV_8SC3, CV_8SC4, CV_16U, CV_16UC1, CV_16UC2, CV_16UC3, CV_16UC4, CV_16S, CV_16SC1, CV_16SC2, CV_16SC3, CV_16SC4, CV_32S, CV_32SC1, CV_32SC2, CV_32SC3, CV_32SC4, CV_32F, CV_32FC1, CV_32FC2, CV_32FC3, CV_32FC4, CV_64F, CV_64FC1, CV_64FC2, CV_64FC3, CV_64FC4
		};

    string enum_strings[] =
		{
		"CV_8U", "CV_8UC1", "CV_8UC2", "CV_8UC3", "CV_8UC4", "CV_8S", "CV_8SC1", "CV_8SC2", "CV_8SC3", "CV_8SC4", "CV_16U", "CV_16UC1", "CV_16UC2", "CV_16UC3", "CV_16UC4", "CV_16S", "CV_16SC1", "CV_16SC2", "CV_16SC3", "CV_16SC4", "CV_32S", "CV_32SC1", "CV_32SC2", "CV_32SC3", "CV_32SC4", "CV_32F", "CV_32FC1", "CV_32FC2", "CV_32FC3", "CV_32FC4", "CV_64F", "CV_64FC1", "CV_64FC2", "CV_64FC3", "CV_64FC4"
		};

    for (int i = 0; i < numImgTypes; i++)
	{
	if (imageType == enum_ints[i])
	    return enum_strings[i];
	}

    return "unknown image type";
    }

/*------------------------*\
 |*	io                 *|
 \*-----------------------*/

Mat OpencvTools::loadBGR(string fileName)
    {
    Mat image = imread(fileName);

    if (!image.data)
	{
	cerr << "[OpenCVTools] : Can't load : " << fileName << std::endl;
	exit (EXIT_FAILURE);
	}
    else
	{
	cout << "[OpenCVTools] : loaded : " << fileName << std::endl;
	}

    return image;
    }

void OpencvTools::write(string fileName, Mat& mat)
    {
    cout << "[OpenCVTools] : writing :" << fileName << endl;
    imwrite(fileName, mat);
    }

/**
 * return true if quit ask
 */
bool OpencvTools::showBGR(Mat& matBGR, string idFrameAndTitle, long delayMS)
    {
    imshow(idFrameAndTitle + " [q to quit]", matBGR);
    //cv::waitKey();

    if (waitKey(delayMS) == 'q') // bloquant pendant delayMs, sinon image s'affiche pas
	{
	cout << endl << "[OpenCVTools] : q to quit" << endl;
	return true;
	}
    else
	{
	return false;
	}
    }

void OpencvTools::destroyFrame(string idFrameAndTitle)
    {
    destroyWindow(idFrameAndTitle);
    }

/*------------------------*\
 |*	Convertion Type    *|
 \*-----------------------*/

/*-------------*\
|* Mat-->uchar   *|
 \*--------------*/

//uchar4* OpencvTools::toRGBA_uchar4(Mat& matBGR)
//    {
//    Mat matRGBA = BGRToRGBA(matBGR);
//    return castToUchar4(matRGBA);
//
//    // TODO le mat est detruit, la zone memoire uchar detruite!
//    }

/*-------------*\
|* Mat-->Mat   *|
 \*--------------*/

Mat OpencvTools::BGRToRGBA(Mat& matBGR)
    {
    int w = matBGR.cols;
    int h = matBGR.rows;

    Mat matRGBA(h, w, CV_8UC4);  // attention : lecture utiliser le type  Mat matRGBA(h, w, CV_8UC4, ptrPixels);
    OpencvTools::switchRB(matRGBA, matBGR); // dest, src

    // showBGR(matRGBA,"id debug");//debug

    return matRGBA;
    }

/**
 * switch R<-->B
 *
 * input/ output : 4 channels RGBA ou BGRA
 */
void OpencvTools::switchRB(Mat& dest4, Mat& src4)
    {
    //Conversion RGBA  to BGRA (croisement R <-->B)

    // cvtColor(in, out,..)
    // cvtColor(src4, dest4, CV_BGR2RGBA, 4);
    cvtColor(src4, dest4, CV_BGR2RGBA);
    }

/**
 * input : 4 channel RGBA OU BGRA
 * ouput : 4 channel identique
 */
void OpencvTools::toGRAY(Mat& destGray, Mat& src4)
    {
    // cvtColor(in, out,..)
    cvtColor(src4, destGray, CV_BGR2GRAY);
    }

/*-------------*\
|* uchar-->Mat   *|
 \*--------------*/

/**
 * switch R<-->B
 *
 * input  :  4 uchar par pixel : RGBA ou BGRA
 * output :  4 channle RGBA ou BGRA
 */
Mat OpencvTools::switchRB(unsigned char* ptrPixel, int w, int h)
    {
    // in
    Mat matSRC(h, w, CV_8UC4, ptrPixel);

    // out
    Mat matDEST(h, w, CV_8UC4, ptrPixel);

    // cvtColor(in, out,..)
    cvtColor(matSRC, matDEST, CV_BGR2RGBA, 4);    //  switch R<-->B

    return matDEST;
    }

/**
 * input : 4 channel RGBA OU BGRA
 * ouput : 4 channel identique
 */
Mat OpencvTools::toGRAY(unsigned char* ptrPixel, int w, int h)
    {
    // out
    Mat matGrayscale(h, w, CV_8UC1, ptrPixel);

    return matGrayscale;
    }

/*-------------*\
|* cast       *|
 \*--------------*/


/**
 * uchar = unsigned char
 */
uchar* OpencvTools::castToUchar(Mat& mat)
    {
    return (uchar*) (mat.data);
    }

void* OpencvTools::castToVoid(Mat& mat)
    {
    return (void*) (mat.data);
    }

/**
 * see
 * 	GPU:	OpencvTools_GPU
 * or
 * 	CPU	OpencvTools_CPU
 * cause:
 * 	type uchar4 not know here
 */
//uchar4* OpencvTools::castToUchar4(Mat& mat)
//    {
//    return (uchar4*) (mat.data);
//    }

/*-------------*\
|* special       *|
 \*--------------*/

Mat OpencvTools::fromUchar3ToDouble(Mat& mat)
    {
    Mat imF;
    mat.convertTo(imF, CV_32FC3);

    return imF;
    }

Mat OpencvTools::fromDoubleToUchar(Mat& mat)
    {
    Mat mat_255;
    Mat mat_uc;

    normalize(mat, mat_255, 0, 255, NORM_MINMAX);
    mat_255.convertTo(mat_uc, CV_8UC1);

    return mat_uc;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

