#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Capture_I contient pas de trace opencv! Peut etre utilise dans implementation v4l sans opencv
 * CaptureMat_I contient l'objet cv::Mat
 */
class Capture_I
    {

	/*--------------------------------------*\
	|*		Destructor		*|
	 \*-------------------------------------*/

    public:

	virtual ~Capture_I(){}

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:


	/**
	 * v4l natural
	 */
	virtual void captureRGBA(unsigned char* ptrPixels)=0;

	/*----------------*\
	|*  common	  *|
	 \*--------------*/

	virtual bool start()=0;

	virtual void stop()=0;

	virtual int getW()=0;

	virtual int getH()=0;

	virtual bool isStarted()=0;

    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
